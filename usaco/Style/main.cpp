#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;
int style(const vector<vector<int>>& matrix, const int N, const int x_, const int y_, const int size) {
	int A = 0;
	int B = 0;
	//cout << "N -> " << N << ", X -> " << x_ << ", Y -> " << y_ << ", size -> " << size << "\n";
	int y = y_;
	for (int x = x_; x < x_ + size; x++) {
		//cout << x << " aadding " << matrix[x][y] << "\n";
		A += matrix[x][y];
		y++;
	}
	int x = x_ + size - 1;
	for (int y = y_; y < y_ + size; y++) {
		//cout << y << " badding " << matrix[x][y] << "\n";
		B += matrix[x][y];
		x--;
	}
	//cout << "A -> " << A << ", B -> " << B << "\n";
	return A - B;
}

int main() {
	int N;
	cin >> N;
	vector<vector<int>> matrix(N, vector<int>(N, 0));
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> matrix[x][y];
		}
	}
	int max_style = -1000000;
	for (int size = 1; size <= N; size++) {
		for (int x = 0; x <= N - size; x++) {
			for (int y = 0; y <= N - size; y++) {
				//calc style
				int sty = style(matrix, N, x, y, size);
				max_style = std::max(max_style, sty);
			}
		}
	}
	cout << max_style << "\n";
}

/*
2             4              5
7  4          1  2  3  4     -2 1  7   8 -4
-5 6          5  6  7  8     6  7  -5  2  9
			  9  10 11 12    13 6  -7 -8  1
			  13 14 15 16    10 -9 12 -4  3
							 -1 -8 6   7  4
*/

/*
2
7 4
-5 6

4
1 2 3 4
5 6 7 8
9 10 11 12
13 14 15 16
*/