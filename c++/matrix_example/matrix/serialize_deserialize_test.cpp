#include <glog/logging.h>
#include <gtest/gtest.h>
#include <iostream>

#include "matrix.h"

TEST(matrixTest, serializeIn) {
	Matrix<int> mat(2, 3);
	std::stringstream("1 2 3 4 5 6") >> mat;
	EXPECT_EQ(mat(0, 0), 1);
	EXPECT_EQ(mat(0, 1), 2);
	EXPECT_EQ(mat(0, 2), 3);
	EXPECT_EQ(mat(1, 0), 4);
	EXPECT_EQ(mat(1, 1), 5);
	EXPECT_EQ(mat(1, 2), 6);
	std::cout << mat << "\n";
}

TEST(matrixTest, serializeOut) {
	Matrix<float> mat1(3, 3);
	mat1(0, 0) = 1.1f;
	mat1(0, 1) = 2.1f;
	mat1(0, 2) = 3.1f;
	mat1(1, 0) = 4.1f;
	mat1(1, 1) = 5.1f;
	mat1(1, 2) = 6.1f;
	mat1(2, 0) = 7.1f;
	mat1(2, 1) = 8.1f;
	mat1(2, 2) = 9.1f;
	std::stringstream str;
	str << mat1;
	EXPECT_EQ(str.str(), "1.1 2.1 3.1\n4.1 5.1 6.1\n7.1 8.1 9.1\n");
}
