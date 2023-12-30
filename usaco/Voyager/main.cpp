#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <algorithm>
#include <iostream>

using namespace std;

char new_dir(const char p, const char d) {
	if(p == '\\'){
		if (d == 'U') {
			return 'L';
		}
		else if (d == 'R') {
			return 'D';
		}
		else if (d == 'D') {
			return 'R';
		}
		else if (d == 'L') {
			return 'U';
		}
	}
	else if (p == '/') {
		if (d == 'U') {
			return 'R';
		}
		else if (d == 'R') {
			return 'U';
		}
		else if (d == 'D') {
			return 'L';
		}
		else if (d == 'L') {
			return 'D';
		}
	}
	return 'X';
}

int main() {
	int N, M, PR, PC;
	cin >> N >> M;
	vector<string> matrix(N);
	for (int i = 0; i < N; i++) {
		cin >> matrix[i];
	}
	cin >> PR >> PC;
	PR -= 1;
	PC -= 1;
	std::vector<pair<char, int>> times(4);
	for (int x = 0; x < 4; x++) {
		int t = 0;
		int R = PR;
		int C = PC;
		char direction = "URDL"[x];
		auto access = [&matrix, N, M](const int r, const int c) {
			if (r > matrix.size() - 1 || c > matrix[0].size() - 1) {
				return 'C';
			}
			return matrix[r][c];
		};
		while (access(R, C) != 'C') {//while signal hasn't disappeared
			//check if direction changes by planetary collision
			//std::cout << "R, C -> " << R << ", " << C << "\n";
			//std::cout << "direction -> " << direction << "\n";
			//check for planetary collision
			if (access(R, C) == '/' || access(R, C) == '\\') {
				direction = new_dir(access(R, C), direction);
			}
			if(direction == 'U'){
				R--;
			}
			else if (direction == 'D') {
				R++;
			}
			else if(direction == 'L') {
				C--;
			}
			else if (direction == 'R') {
				C++;
			}
			t++;
			if (t > 90000) {
				t = -1;
				break;
			}
		}
		times.push_back(pair<char, int>("URDL"[x], t));
	}
	auto f = [](const pair<char, int>& a, const pair<char, int>& b) {
		if (a.second < b.second) {
			return true;
		}
		else if (a.second == b.second) {
			int a_pr = 0;
			int b_pr = 0;
			switch (a.first) {
			case 'U':
				a_pr = 4;
			case 'R':
				a_pr = 3;
			case 'D':
				a_pr = 2;
			case 'L':
				a_pr = 1;
			}
			switch (b.first) {
			case 'U':
				b_pr = 4;
			case 'R':
				b_pr = 3;
			case 'D':
				b_pr = 2;
			case 'L':
				b_pr = 1;
			}
			return a_pr < b_pr;
		}
		return false;
	};
	for (auto i : times) {
		if (i.second == -1) {
			cout << i.first << "\n";
			cout << "Voyager";
			return 0;
		}
	}
	sort(times.begin(), times.end(), f);
	cout << times.back().first << "\n";
	cout << times.back().second << "\n";
}