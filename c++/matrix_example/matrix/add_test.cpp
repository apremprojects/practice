#include <glog/logging.h>
#include <gtest/gtest.h>
#include <iostream>

#include "matrix.h"

TEST(matrixTest, add_2x2) {
	Matrix<int> m1(2, 2);
	Matrix<int> m2(2, 2);
	std::stringstream("1 2 3 4") >> m1;
	std::stringstream("5 6 7 8") >> m2;
	const auto m3 = m1 + m2;
	EXPECT_EQ(m3(0, 0), 6);
	EXPECT_EQ(m3(0, 1), 8);
	EXPECT_EQ(m3(1, 0), 10);
	EXPECT_EQ(m3(1, 1), 12);
}

TEST(matrixTest, add_2x3) {
	Matrix<int> m1(2, 3);
	Matrix<int> m2(2, 3);
	std::stringstream("1 2 3 4 5 6") >> m1;
	std::stringstream("7 8 9 10 11 12") >> m2;
	const auto m3 = m1 + m2;
	EXPECT_EQ(m3(0, 0), 8);
	EXPECT_EQ(m3(0, 1), 10);
	EXPECT_EQ(m3(0, 2), 12);
	EXPECT_EQ(m3(1, 0), 14);
	EXPECT_EQ(m3(1, 1), 16);
	EXPECT_EQ(m3(1, 2), 18);
}

TEST(matrixTest, add_2x2_with_2x3) {
	Matrix<int> m1(2, 2);
	Matrix<int> m2(2, 3);
	std::stringstream("1 2 3 4") >> m1;
	std::stringstream("7 8 9 10 11 12") >> m2;
	EXPECT_DEATH(m1 + m2, "Column size mismatch 2, 3");
}
