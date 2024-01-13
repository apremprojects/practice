#include <vector>
#include <cstdio>
#include <iostream>

#include <Eigen/Core>
#include <Eigen/EigenValues>

using namespace Eigen;

std::vector<Vector3f> load(const char* file_path) {
	std::vector<Vector3f> data;
	std::FILE* file = std::fopen(file_path, "r");
	while (!std::feof(file)) {
		Vector3f d;
		std::fscanf(file, "%f, %f, %f\n", &d.x(), &d.y(), &d.z());
		data.push_back(d);
	}
	std::fclose(file);
	return data;
}

// A = M^T * M, finds M
Matrix3d generateMatrixSqrt(const Matrix3d& A) {
	const EigenSolver<Matrix<double, 3, 3>> solver(A, true);
	const Matrix3d P = solver.eigenvectors().real();
	const Matrix3d D = solver.eigenvalues().real().cwiseSqrt().asDiagonal();
	std::cout << "DIAG -> " << D << "\n";
	std::cout << solver.eigenvalues().real() << "\n";
	return P * D * P.transpose();
}

void ellipsoidFit(const std::vector<Vector3f>& mag_data, Matrix3d& M, Vector3d& origin) {
	// Implementation based on this paper: https://www.researchgate.net/publication/4070857_Least_squares_ellipsoid_specific_fitting

	// Creates D matrix
	MatrixXd D(mag_data.size(), 10);
	for (int row = 0; row < mag_data.size(); row++) {
		const auto& v = mag_data[row];
		D(row, 0) = v.x() * v.x();
		D(row, 1) = v.y() * v.y();
		D(row, 2) = v.z() * v.z();
		D(row, 3) = 2.0 * v.y() * v.z();
		D(row, 4) = 2.0 * v.x() * v.z();
		D(row, 5) = 2.0 * v.x() * v.y();
		D(row, 6) = 2.0 * v.x();
		D(row, 7) = 2.0 * v.y();
		D(row, 8) = 2.0 * v.z();
		D(row, 9) = 1.0;
	}
	const Matrix<double, 10, 10> DTD = D.transpose() * D;

	// Creates C and S11...S22 matrix
	const double k = 4;
	Matrix<double, 6, 6> C;
	C << -1, k / 2 - 1, k / 2 - 1, 0, 0, 0,
		k / 2 - 1, -1, k / 2 - 1, 0, 0, 0,
		k / 2 - 1, k / 2 - 1, -1, 0, 0, 0,
		0, 0, 0, -k, 0, 0,
		0, 0, 0, 0, -k, 0,
		0, 0, 0, 0, 0, -k;
	const auto S11 = DTD.block<6, 6>(0, 0);
	const auto S12 = DTD.block<6, 4>(0, 6);
	const auto S22 = DTD.block<4,4>(6, 6);

	// Creates V1 & V2 vectors
	const Matrix<double, 6, 6> E = C.inverse() * (S11 - S12 * S22.inverse() * S12.transpose());
	EigenSolver<Matrix<double, 6, 6>> solver(E);
	Index i;
	solver.eigenvalues().real().maxCoeff(&i);
	Matrix<double,6,1> V1 = solver.eigenvectors().real().col(i);
	if (V1[0] < 0.0) {
		V1 *= -1;
	}
	const Matrix<double, 4, 1> V2 = -S22.inverse() * S12.transpose() * V1;

	// Creates A, M, and origin matrices/vectors
	Matrix3d A;
	A << V1(0), V1(5), V1(4),
		V1(5), V1(1), V1(3),
		V1(4), V1(3), V1(2);
	origin = -A.inverse() * Vector3d(V2(0), V2(1), V2(2));
	const double r = std::sqrt(origin.transpose() * A * origin - V2(3)); // Scales M to r to be
	M = generateMatrixSqrt(A) / r;
	std::cout << "A -> " << A << "\n";
	std::cout << "R -> " << r << "\n";
}

int main(int argc, char** argv) {
	if (argc < 2) {
		std::cout << "Raw magnetic data file missing" << std::endl;
		return 0;
	}

	const auto mag_data = load(argv[1]);

	Vector3d origin;
	Matrix3d M;
	ellipsoidFit(mag_data, M, origin);

	std::cout << "M:\n" << M << "\n\n";
	std::cout << "origin:\n" << origin.transpose() << "\n";

	return 0;
}
