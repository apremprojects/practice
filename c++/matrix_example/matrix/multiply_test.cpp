#include <glog/logging.h>
#include <gtest/gtest.h>
#include <iostream>

#include "matrix.h"

TEST(matrixTest, scalarMult) {
	Matrix<int> m(2, 2);
	std::stringstream("1 2 3 4") >> m;
	const Matrix<int> mat = m * 10;
	EXPECT_EQ(mat(0, 0), 10);
	EXPECT_EQ(mat(0, 1), 20);
	EXPECT_EQ(mat(1, 0), 30);
	EXPECT_EQ(mat(1, 1), 40);
}

TEST(matrixTest, scalarMultAndAdd) {
	Matrix<int> m1(2, 2);
	Matrix<int> m2(2, 2);
	std::stringstream("1 2 3 4") >> m1;
	std::stringstream("5 6 7 8") >> m2;
	const Matrix<int> mat = (m1*4) + m2;
	EXPECT_EQ(mat(0, 0), 9);
	EXPECT_EQ(mat(0, 1), 14);
	EXPECT_EQ(mat(1, 0), 19);
	EXPECT_EQ(mat(1, 1), 24);
}

TEST(matrixTest, mult_2x3_3x2) {
	Matrix<int> m1(2, 3);
	Matrix<int> m2(3, 2);
	std::stringstream("1 2 3 4 5 6") >> m1;
	std::stringstream("7 8 9 10 11 12") >> m2;
	const Matrix<int> m3 = m1 * m2;
	EXPECT_EQ(m3(0, 0), 1*7+2*9+3*11);
	EXPECT_EQ(m3(0, 1), 1*8+2*10+3*12);
	EXPECT_EQ(m3(1, 0), 4*7+5*9+6*11);
	EXPECT_EQ(m3(1, 1), 4*8+5*10+6*12);
}

TEST(matrixTest, invalidMultiplication) {
	Matrix<int> m1(2, 3);
	Matrix<int> m2(2, 3);
	std::stringstream("1 2 3 4 5 6") >> m1;
	std::stringstream("7 8 9 10 11 12") >> m2;
	EXPECT_DEATH(m1 * m2, "");
}
