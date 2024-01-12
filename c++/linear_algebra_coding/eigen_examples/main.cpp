#include <iostream>

#include <Eigen/Core>
#include <Eigen/Eigenvalues>

void basicMatrixExample() {
  std::cout << "----------Basic matrix examples----------------\n";
  Eigen::Matrix<float, 2, 2> a;
  a << 1.0f, 0.5f, 
       2.0f, 3.0f;
  Eigen::Matrix2f b;
  b << 0.5f, 0.3f,
       0.25f, 0.125f;

  Eigen::Matrix2f c = a+b;
  std::cout << "c = a+b\n";
  std::cout << c << "\n";
  Eigen::Matrix2f d = a*b;
  std::cout << "d = a*b\n";
  std::cout << d << "\n";
  std::cout << "----------Basic matrix examples----------------\n";
}

void dynamicMatrixExample() {
  std::cout << "----------Dynamic matrix examples----------------\n";
  Eigen::MatrixXf mat(5, 5);
  for (size_t i = 0; i < 5; i++) {
    for (size_t j = 0; j < 5; j++) {
      mat(i, j) = 1.0f/(1.0f+rand()%10);
    }
  }
  std::cout << "Dynamic Matrix\n" << mat << "\n";
  std::cout << "----------Dynamic matrix examples----------------\n";
}

void computeEigenValues() {
  std::cout << "----------Eigen values, vectors example----------------\n";
  Eigen::Matrix<float, 2, 2> mat;
  mat << 1.0f, 0.5f,
         2.0f, 3.0f;
  Eigen::EigenSolver<Eigen::Matrix<float, 2, 2>> solver(mat);
  std::cout << "Eigen values:\n" << solver.eigenvalues() << "\n";
  std::cout << "Eigen values(real):\n" << solver.eigenvalues().real() << "\n";
  std::cout << "Eigen values(imag):\n" << solver.eigenvalues().imag() << "\n";
  std::cout << "Eigen vectors:\n" << solver.eigenvectors() << "\n";
  std::cout << "Eigen vectors(real):\n" << solver.eigenvectors().real() << "\n";
  std::cout << "Eigen vectors(imag):\n" << solver.eigenvectors().imag() << "\n";
  std::cout << "----------Eigen values, vectors example----------------\n";
}

int main(void) {
  basicMatrixExample();
  dynamicMatrixExample();
  computeEigenValues();
  return 0;
}
