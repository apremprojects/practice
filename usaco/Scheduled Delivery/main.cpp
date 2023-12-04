#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <algorithm>
#include <iostream>

using namespace std;

vector<int> gen_chain(const int start, const int end, const int inc) {
	vector<int> res;
	res.reserve((end - start) / inc + 1);
	int ct = start;
	while (ct <= end) {
		res.push_back(ct);
		ct += inc;
	}
	return res;
}


bool isIn(const int item, const vector<int>& v) {
	for (auto i : v) {
		if (i == item) {
			return true;
		}
	}
	return false;
}

bool isIn(const int item, const vector<vector<int>>& v) {
	for (auto i : v) {
		if (isIn(item, i)) {
			return true;
		}
	}
	return false;
}

vector<vector<int>> merge(vector<vector<int>> &intake) {
	vector<vector<int>> output;
	output.push_back(intake[0]);
	for (int i = 1; i < intake.size(); i++) {
		vector<int> temp_arr;
		for (int item : intake[i]) {
			if (!isIn(item, output) && !isIn(item, temp_arr)) {
				temp_arr.push_back(item);
			}
		}
		if (!temp_arr.empty()) {
			output.push_back(temp_arr);
		}
	}
	return output;
}

int main() {
	int N;
	cin >> N;
	vector<int> nums(N);
	for (int i = 0; i < N; i++) {
		cin >> nums[i];
	}
	vector<vector<int>> chains(N - 1);
	int end = nums[N - 1];
	for (int i = 1; i < N; i++) {
		chains[i - 1] = gen_chain(1, end, nums[i] - 1);
	}
	/*cout << "Raw\n";
	for (auto v : chains) {
		for (auto i : v) {
			cout << i << "-";
		}
		cout << "\n";
	}
	cout << "Merge\n";*/
	vector<vector<int>> chains_merged = merge(chains);
	/*for (auto v : chains_merged) {
		for (auto i : v) {
			cout << i << " ";
		}
		cout << "\n";
	}*/
	cout << chains_merged.size() << "\n";
}