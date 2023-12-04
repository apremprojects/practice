#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <algorithm>
#include <iostream>

using namespace std;

void fill(vector<int>& record, const int start, const int end, const int val) {
	for (int i = start; i < end; i++) {
		record[i] = val;
	}
}

int main() {
	int N, M;
	cin >> N >> M;
	vector<pair<int, int>> ri(N);
	vector<pair<int, int>> bi(M);
	for (int i = 0; i < N; i++) {
		cin >> ri[i].first >> ri[i].second;
	}
	for (int i = 0; i < M; i++) {
		cin >> bi[i].first >> bi[i].second;
	}
	vector<int> record(100);
	vector<int> bessie(100);
	int start = 0;
	for (pair<int, int> i : ri) {
		fill(record, start, start + i.first, i.second);
		start += i.first;
	}
	start = 0;
	for (pair<int, int> i : bi) {
		fill(bessie, start, start + i.first, i.second);
		start += i.first;
	}
	int max = 0;
	for (int i = 0; i < 100; i++) {
		max = std::max(max, bessie[i] - record[i]);
	}
	if (max >= 0) {
		cout << max << "\n";
		return 0;
	}
	cout << 0 << "\n";
}