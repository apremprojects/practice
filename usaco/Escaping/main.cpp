#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <algorithm>
#include <iostream>

using namespace std;

struct fence_t {
	int size;
	int pos;
};

bool operator<(const fence_t& a, const fence_t& b) {
	return a.pos < b.pos;
}

bool operator!=(const fence_t& a, const fence_t& b) {
	return a.pos != b.pos;
}

bool runSimulation(const vector<fence_t>& fences, const int lfence, const int rfence) {
	int bessie_lfence = lfence;
	int bessie_rfence = rfence;
	while (bessie_lfence >= 0 && bessie_rfence < fences.size()) { //while bessie hasn't escaped
		int interval_size = fences[bessie_rfence].pos - fences[bessie_lfence].pos;
		//cout << "Interval_size -> " << interval_size << "\n";
		bool fenceBroken = false;
		//check if bessie can break the right fence
		if (interval_size > fences[bessie_rfence].size) {
			//break the right fence
			//cout << "Bessie broke rightfence\n";
			bessie_rfence++;
			fenceBroken = true;
			//interval_size = fences[bessie_rfence].pos - fences[bessie_lfence].pos;
		}
		//check if bessie can break the left fence
		if (interval_size > fences[bessie_lfence].size) {
			//cout << "Bessie broke leftfence\n";
			bessie_lfence--;
			fenceBroken = true;
			//interval_size = fences[bessie_rfence].pos - fences[bessie_lfence].pos;
		}
		
		//if bessie can't break any of the fences, then she is stuck. Return true.
		if (!fenceBroken) {
			return true;
		}
	}
	//bessie broke out
	return false;
}

int main() {
	int N;
	cin >> N;
	vector<fence_t> fences(N);
	for (int i = 0; i < N; i++) {
		cin >> fences[i].size >> fences[i].pos;
	}
	sort(fences.begin(), fences.end());
	int total = 0;
	//run simulation of bessie for each interval. If Bessie doesn't escape (by breaking leftmost or rightmost fence), add area of interval to total
	for(int i = 1; i < N; i++){
		//cout << "Checking interval " << fences[i - 1].pos << " to " << fences[i].pos << "\n";
		if (runSimulation(fences, i - 1, i)) {
			total += fences[i].pos - fences[i - 1].pos;
		}
	}
	cout << total << "\n";
}