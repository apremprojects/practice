#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <algorithm>
#include <iostream>

using namespace std;

struct pulley_t {
	int start;
	int end;
	int type;
};

void special_sort(vector<pulley_t>& pulleys) {
	auto csort = [](const pulley_t &a, const pulley_t &b) {
		return a.end <= b.start;
	};
	sort(pulleys.begin(), pulleys.end(), csort);
}

bool flip(const bool a) {
	if (a) {
		return false;
	}
	return true;
}

int main() {
	int N;
	cin >> N;
	vector<pulley_t> pulleys(N - 1);
	for (int i = 0; i < N - 1; i++) {
		cin >> pulleys[i].start >> pulleys[i].end >> pulleys[i].type;
	}
	special_sort(pulleys);
	bool rotation = false;
	//true = clockwise
	//false = counterclockwise
	for (pulley_t i : pulleys) {
		if (i.type == 1) {
			rotation = flip(rotation);
		}
		else {}
	}
	cout << rotation << "\n";
}