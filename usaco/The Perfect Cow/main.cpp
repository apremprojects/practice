#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <algorithm>
#include <iostream>

using namespace std;

int getMedian(vector<int> &data, const int row, const int N) {
	vector<int> vrow;
	vrow.reserve(N);
	int start = row * N;
	int end = start + N - 1;
	for (int i = start; i <= end; i++) {
		vrow.push_back(data[i]);
	}
	sort(vrow.begin(), vrow.end());
	if (N % 2 == 1) {
		int med_ind = N / 2;
		return vrow[med_ind];
	}
	else {
		int med_ind = N / 2;
		return (vrow[med_ind] + vrow[med_ind + 1]) / 2;
	}
}

int main() {
	int N;
	cin >> N;
	vector<int> data(N * N);
	for (int row = 0; row < N; row++) {
		for (int column = 0; column < N; column++) {
			cin >> data[row * N + column];
		}
	}
	vector<int> med(N);
	for (int row = 0; row < N; row++) {
		med[row] = getMedian(data, row, N);
	}
	cout << getMedian(med, 0, N) << "\n";
}