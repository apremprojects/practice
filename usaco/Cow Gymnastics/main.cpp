#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <array>
#include <set>
#include <fstream>
using namespace std;

int main() {
	int K;
	int N;
	cin >> K >> N;
	vector<vector<int>> practice_sessions(K, vector<int>(N));
	for (int i = 0; i < K; i++) {
		for (int m = 0; m < N; m++) {
			cin >> practice_sessions[i][m];
		}
	}
	int ct = 0;
	bool prev_state = false;
	for (int cow_one = 1; cow_one <= N; cow_one++) {
		for (int cow_two = cow_one; cow_two <= N; cow_two++) {
			if (cow_one != cow_two) {
				bool c = true;
				int match = 0;
				int pos_one = std::find(practice_sessions[match].begin(), practice_sessions[match].end(), cow_one) - practice_sessions[match].begin();
				//get pos of cow_two
				int pos_two = std::find(practice_sessions[match].begin(), practice_sessions[match].end(), cow_two) - practice_sessions[match].begin();
				prev_state = pos_one > pos_two;
				for (match = 1; match < K; match++) {
					//get pos of cow_one
					pos_one = std::find(practice_sessions[match].begin(), practice_sessions[match].end(), cow_one) - practice_sessions[match].begin();
					//get pos of cow_two
					pos_two = std::find(practice_sessions[match].begin(), practice_sessions[match].end(), cow_two) - practice_sessions[match].begin();
					if (pos_one > pos_two != prev_state) {
						c = false;
					}
				}
				if (c) {
					//cout << "Pair between cow #" << cow_one << " and cow #" << cow_two << "\n";
					ct++;
				}
			}
		}
	}
	cout << ct << "\n";
}