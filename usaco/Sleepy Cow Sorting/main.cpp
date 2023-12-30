#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <list>
#include <thread>
#include <cmath>

using namespace std;

bool is_unsorted(const list<int>& l) {
	int prev_val = 0;
	for (const int i : l) {
		if (i < prev_val) {
			return true;
		}
		prev_val = i;
	}
	return false;
}

int main() {
	int N;
	cin >> N;
	list<int> l;
	for (int i = 0; i < N; i++) {
		int tmp;
		cin >> tmp;
		l.emplace_back(tmp);
	}
	//check if l was already sorted, if so, return 0
	if (!is_unsorted(l)) {
		cout << "0\n";
		return 0;
	}
	int timestep = 0;
	bool m = true;
	while (m) {
		if (l.front() == 1) {//nothing in list exists that is lesser
			//send to back.
			l.insert(l.end(), l.front());
			l.pop_front();
			//return -1;
		}
		else {
			//find places with gaps OR if better, push to the end
			bool b = true;
			int prev_val = l.front();
			for (auto it = l.begin(); it != l.end(); it++) {
				if (*it - prev_val > 1) {
					//gap between prev_val and it, check if l.front() can plug the gap
					if (prev_val < l.front() && l.front() < *it) {
						b = false;
						l.insert(it, l.front());
						l.pop_front();
						break;
					}
				}
				prev_val = *it;
			}
			if (b) {
				l.insert(l.end(), l.front());
				l.pop_front();
			}
		}
		m = is_unsorted(l);
		timestep++;
		for (auto i : l) {
			cout << i << " ";
		}
		cout << "\n";
		if (!m) {
			if (timestep > 1) {
				cout << timestep - 1 << "\n";
				return 0;
			}
			cout << timestep << "\n";
			return 0;
			
		}
	}
}

/*
4
1 2 4 3
*/
/*
55
44 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 45 46 47 48 49 50 51 52 53 54 55
*/
/*
60
35 50 4 39 54 32 20 53 29 18 55 28 40 44 48 25 21 5 9 14 33 3 16 38 31 23 15 60 27 49 11 51 46 52 30 45 1 6 36 43 24 7 58 56 42 2 8 10 12 13 17 19 22 26 34 37 41 47 57 59
*/