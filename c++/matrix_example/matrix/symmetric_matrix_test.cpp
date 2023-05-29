#include <glog/logging.h>
#include <gtest/gtest.h>
#include <iostream>

#include "matrix.h"
template <typename T>
bool isSymmetric(const Matrix<T> &matrix) {
	std::cout << "Checking if symmetric...\n";
	if (matrix.rowSize() != matrix.colSize()) {
		return false;
	}
	for (int r = 0; r < matrix.rowSize(); r++) {
		for (int c = r; c < matrix.colSize(); c++) {
			if (r != c) {
				std::cout << "Comparing (" << r << "," << c << ") -> (" << c << ", " << r << ")\n";
				std::cout << "(" << r << "," << c << ") = " << matrix(r, c) << "\n";
				std::cout << "(" << c << "," << r << ") = " << matrix(c, r) << "\n";
				if (matrix(r, c) != matrix(c, r)) {
					return false;
				}
			}
		}
	}
	return true;
}

TEST(matrixTest, symmetricMatrixTest) {
	Matrix<int> m(2, 2);
	std::stringstream("1 2 3 4") >> m;
	EXPECT_EQ(isSymmetric(m), false);
}

TEST(matrixTest, symmetricMatrixTest2) {
	Matrix<int> m(2, 2);
	std::stringstream("1 2 2 1") >> m;
	EXPECT_EQ(isSymmetric(m), true);
}

TEST(matrixTest, symmetricMatrixTest3) {
	Matrix<int> m(1, 4);
	std::stringstream("1 2 2 1") >> m;
	EXPECT_EQ(isSymmetric(m), false);
}

TEST(matrixTest, symmetricMatrixTest4) {
	Matrix<int> m(3, 3);
	std::stringstream("1 2 3 2 3 4 3 4 5") >> m;
	EXPECT_EQ(isSymmetric(m), true);
}

TEST(matrixTest, symmetricMatrixTest5) {
	Matrix<int> m(3, 3);
	std::stringstream("1 2 3 2 3 4 3 4 4") >> m;
	EXPECT_EQ(isSymmetric(m), true);
}