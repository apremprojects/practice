#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <algorithm>
#include <iostream>

using namespace std;

int sim(const vector<pair<int, int>>& shifts, const int fired) {
	vector<bool> ts(1000, false);
	for (int i = 0; i < shifts.size(); i++) {
		if (i != fired) {
			for (int m = shifts[i].first; m < shifts[i].second; m++) {
				ts[m] = true;
			}
		}
	}
	int ct = 0;
	for (bool b : ts) {
		if (b) {
			ct++;
		}
	}
	return ct;
}

int main() {
	int N;
	cin >> N;
	vector<pair<int, int>> shifts(N);
	for(int i = 0; i < N; i++){
		cin >> shifts[i].first >> shifts[i].second;
	}
	int ans = 0;
	for (int i = 0; i < N; i++) {
		ans = std::max(ans, sim(shifts, i));
	}
	cout << ans << "\n";
}