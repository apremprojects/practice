#include <glog/logging.h>
#include <gtest/gtest.h>
#include <iostream>

#include "matrix.h"

TEST(matrixTest, set_2x3) {
	Matrix<int> mat(2, 3);

	mat(0, 0) = 1;
	mat(0, 1) = 2;
	mat(0, 2) = 3;
	mat(1, 0) = 4;
	mat(1, 1) = 5;
	mat(1, 2) = 6;

	EXPECT_EQ(mat(0, 0), 1);
	EXPECT_EQ(mat(0, 1), 2);
	EXPECT_EQ(mat(0, 2), 3);
	EXPECT_EQ(mat(1, 0), 4);
	EXPECT_EQ(mat(1, 1), 5);
	EXPECT_EQ(mat(1, 2), 6);
}

TEST(matrixTest, set_3x3) {
	Matrix<double> m(3, 3);

	m(0, 0) = 0.0;
	m(0, 1) = 0.1;
	m(0, 2) = 0.2;
	m(1, 0) = 1.0;
	m(1, 1) = 1.1;
	m(1, 2) = 1.2;
	m(2, 0) = 2.0;
	m(2, 1) = 2.1;
	m(2, 2) = 2.2;

	EXPECT_EQ(m(0, 0), 0.0);
	EXPECT_EQ(m(0, 1), 0.1);
	EXPECT_EQ(m(0, 2), 0.2);
	EXPECT_EQ(m(1, 0), 1.0);
	EXPECT_EQ(m(1, 1), 1.1);
	EXPECT_EQ(m(1, 2), 1.2);
	EXPECT_EQ(m(2, 0), 2.0);
	EXPECT_EQ(m(2, 1), 2.1);
	EXPECT_EQ(m(2, 2), 2.2);
}
