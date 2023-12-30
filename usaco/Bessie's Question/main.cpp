#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <algorithm>
#include <iostream>

using namespace std;

pair<int, int> operator+(const pair<int, int>& a, const pair<int, int>& b) {
	return {a.first + b.first, a.second + b.second};
}

pair<int, int> to_pair(const char d, const int m) {
	if (d == 'N') {
		return pair<int, int>(0, m);
	}
	else if (d == 'S') {
		return pair<int, int>(0, -m);
	}
	else if (d == 'E') {
		return pair<int, int>(m, 0);
	}
	else if (d == 'W') {
		return pair<int, int>(-m, 0);
	}
	return pair<int, int>(-1, -1);
}

int main() {
	int N;
	cin >> N;
	vector<pair<char, int>> commands(N);
	for (int i = 0; i < N; i++) {
		cin >> commands[i].first >> commands[i].second;
	}
	vector<pair<int, int>> coords(N + 1);
	coords[0] = { 0,0 };
	int max_x = 0;
	int min_x = -100000;
	int max_y = 0;
	int min_y = -100000;
	for (int i = 1; i < N + 1; i++) {
		coords[i] = coords[i-1] + to_pair(commands[i - 1].first, commands[i - 1].second);
		max_x = std::max(coords[i].first, max_x);
		min_x = std::min(coords[i].first, min_x);
		max_y = std::max(coords[i].second, max_y);
		min_y = std::min(coords[i].second, min_y);
	}
	int matrix_col = max_x - min_x;
	int matrix_row = max_y - min_y;
	int last_int_time = 0; //time between start and last_intersection;
	int t = 0; //time
	int max_time = 0;//result
	vector<bool> city(matrix_col * matrix_row, false);
	for (int i = 1; i < N + 1; i++) {
		//find if line coords[i-1] to coords[i] is horz or vertical
		if (coords[i - 1].first == coords[i].first && coords[i - 1].first == coords[i].first) {//single point
		}
		else if (coords[i - 1].first == coords[i].first) {//vertical
			cout << "Vertical\n";
			int x = coords[i].first;
			for (int y = coords[i - 1].second; y <= coords[i].second; y++) {
				if (!city[((y-min_y) * matrix_col) + (x-min_x)]) {
					city[((y - min_y) * matrix_col) + (x - min_x)] = true;
				}
				else if(y!= coords[i - 1].second && y != coords[i].second){
					last_int_time = t;
				}
				t++;
				max_time = std::max(max_time, t - last_int_time);
			}
		}
		else if (coords[i - 1].second == coords[i].second) {//horizontal
			cout << "Horizontal\n";
			int y = coords[i].second;
			for (int x = coords[i - 1].first; x <= coords[i].first; x++) {
				if (!city[((y - min_y) * matrix_col) + (x - min_x)]) {
					city[((y - min_y) * matrix_col) + (x - min_x)] = true;
				}
				else if (x != coords[i - 1].first && x != coords[i].first) {
					last_int_time = t;
				}
				t++;
				max_time = std::max(max_time, t - last_int_time);
			}
		}
	}
	cout << last_int_time << "\n";
}

/*
4
N 8
E 3
S 6
W 4
*/