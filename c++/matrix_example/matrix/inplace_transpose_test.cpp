#include <glog/logging.h>
#include <gtest/gtest.h>
#include <iostream>

#include "matrix.h"
template<typename T>
void transpose(Matrix<T>& matrix) {
	CHECK_EQ(matrix.rowSize(), matrix.colSize());
	for (int r = 0; r < matrix.rowSize(); r++) {
		for (int c = r; c < matrix.colSize(); c++) {
			if (r != c) {
				std::cout << "Setting (" << r << "," << c << ") = (" << c << "," << r << ")\n";
				std::swap(matrix(r, c), matrix(c, r));
			}
		}
	}
}
TEST(matrixTest, inplace_transpose) {
	Matrix<int> m(3, 3);
	std::stringstream("1 2 3 4 5 6 7 8 9") >> m;
	std::cout << m;
	transpose(m);
	std::cout << m;
	EXPECT_EQ(m.rowSize(), 3);
	EXPECT_EQ(m.colSize(), 3);
}
