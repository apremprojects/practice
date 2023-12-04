#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <set>
using namespace std;

int main() {
	vector<int> rs(10, 10);
	vector<int> cs(10, 10);
	vector<int> re(10, -1);
	vector<int> ce(10, -1);
	vector<bool> visible(10, false);
	vector<bool> firstPainted(10, false);
	int N;
	cin >> N;
	string field;
	for (int row = 0; row < N; row++) {
		string tmp;
		cin >> tmp;
		for (int column = 0; column < N; column++) {
			int num = tmp[column] - '0';
			visible[num] = true;
			firstPainted[num] = true;
			rs[num] = std::min(row, rs[num]);
			cs[num] = std::min(column, cs[num]);
			re[num] = std::max(row, re[num]);
			ce[num] = std::max(column, ce[num]);
		}
		field += tmp;
	}
	for (int i = 1; i < 10; i++) {
		if (!visible[i]) {
			continue;
		}
		for (int r = rs[i]; r <= re[i]; r++) {
			for (int c = cs[i]; c <= ce[i]; c++) {
				int numTemp = field[r * N + c] - '0';
				if (numTemp != i) {
					firstPainted[numTemp] = false;
				}
			}
		}
	}
	int ct = 0;
	for (int i = 1; i < 10; i++) {
		if (firstPainted[i]) {
			ct++;
		}
	}
	cout << ct << "\n";
}