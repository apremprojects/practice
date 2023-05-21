#include <glog/logging.h>
#include <gtest/gtest.h>
#include <iostream>

#include "matrix.h"

TEST(matrixTest, transpose) {
	Matrix<int> m(2, 3);
	std::stringstream("1 2 3 4 5 6") >> m;
	const Matrix<int> mt = m.transpose();
	EXPECT_EQ(mt.rowSize(), 3);
	EXPECT_EQ(mt.colSize(), 2);
	EXPECT_EQ(mt(0, 0), 1);
	EXPECT_EQ(mt(1, 0), 2);
	EXPECT_EQ(mt(2, 0), 3);
	EXPECT_EQ(mt(0, 1), 4);
	EXPECT_EQ(mt(1, 1), 5);
	EXPECT_EQ(mt(2, 1), 6);
}
