#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

char access(const string& s, int row, int column) {
	return s[(row * 3) + column];
}

bool check_left_diagonal_for_win(const string &s, const string &v, const char c) {
	for (int i = 0; i < 3; i++) {
		if (access(s, i, i) != c || access(v, i, i) == '1') {
			return false;
		}
	}
	return true;
}

bool check_left_diagonal_for_win(const string& s, const string &v, const char c, const char d) {
	int cct = 0;
	int dct = 0;
	for (int i = 0; i < 3; i++) {
		if (access(s, i, i) == c && access(v, i, i) == '0') {
			cct++;
		}
		else if (access(s, i, i) == d && access(v, i, i) == '0') {
			dct++;
		}
		else {
			return false;
		}
	}
	if (cct + dct == 3 && cct != 0 && dct!=0) {
		return true;
	}
	return false;
}

bool check_right_diagonal_for_win(const string& s, const string &v, const char c) {
	for (int i = 0; i < 3; i++) {
		if (access(s, i, 2 - i) != c || access(v, i, 2-i) == '1') {
			return false;
		}
	}
	return true;
}

bool check_right_diagonal_for_win(const string& s, const string &v, const char c, const char d) {
	int cct = 0;
	int dct = 0;
	for (int i = 0; i < 3; i++) {
		if (access(s, i, 2-i) == c && access(v, i, i) == '0') {
			cct++;
		}
		else if (access(s, i, 2-i) == d && access(v, i, i) == '0') {
			dct++;
		}
		else {
			return false;
		}
	}
	if (cct + dct == 3) {
		if (cct == 0 || dct == 0) {
			return false;
		}
		return true;
	}
	return false;
}

bool check_row(const string& s, const string &v, int row, const char c) {
	if (access(s, row, 0) == c && access(v, row, 0) == '0') {
		if (access(s, row, 1) == c && access(v, row, 1) == '0') {
			if (access(s, row, 2) == c && access(v, row, 2) == '0') {
				return true;
			}
		}
	}
	return false;
}

bool check_column(const string& s, const string &v, const int column, const char c) {
	if (access(s, 0, column) == c && access(v, 0, column) == '0') {
		if (access(s, 1, column) == c && access(v, 1, column) == '0') {
			if (access(s, 2, column) == c && access(v, 2, column) == '0') {
				return true;
			}
		}
	}
	return false;
}

bool check_row(const string& s, const string &v, int row, const char c, const char d) {
	int cct = 0;
	int dct = 0;
	if (access(s, row, 0) == c && access(v, row, 0) == '0') {
		cct++;
		
	}
	if (access(s, row, 1) == c && access(v, row, 1) == '0') {
		cct++;
		
	}
	if (access(s, row, 2) == c && access(v, row, 2) == '0') {
		cct++;
	}
	if (access(s, row, 0) == d && access(v, row, 0) == '0') {
		dct++;
		
	}
	if (access(s, row, 1) == d && access(v, row, 1) == '0') {
		dct++;
		
	}
	if (access(s, row, 2) == d && access(v, row, 2) == '0') {
		dct++;
	}
	if (cct + dct == 3) {
		if (cct == 0 || dct == 0) {
			return false;
		}
		return true;
	}
	return false;
}

bool check_column(const string& s, const string &v, const int column, const char c, const char d) {
	int cct = 0;
	int dct = 0;
	if (access(s, 0, column) == c && access(v, 0, column) == '0') {
		cct++;
	}
	if (access(s, 1, column) == c && access(v, 1, column) == '0') {
		cct++;
	}
	if (access(s, 2, column) == c && access(v, 2, column) == '0') {
		cct++;
	}
	if (access(s, 0, column) == d && access(v, 0, column) == '0') {
		dct++;
	}
	if (access(s, 1, column) == d && access(v, 1, column) == '0') {
		dct++;
	}
	if (access(s, 2, column) == d && access(v, 2, column) == '0') {
		dct++;
	}
	if (cct + dct == 3) {
		if (cct == 0 || dct == 0) {
			return false;
		}
		return true;
	}
	return false;
}

bool isIn(const string& s, const char c) {
	for (char i : s) {
		if (i == c) {
			return true;
		}
	}
	return false;
}

int main() {
	//cout << isIn("TSLWTLOST", 'U') << "\n";
	//exit(1);
	//count one_squirrel wins
	string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string matrix;
	for (int i = 0; i < 3; i++) {
		string tmp;
		cin >> tmp;
		matrix += tmp;
	}
	//cout << matrix.size() << "\n";
	string v = "000000000";
	int solo_squirrel_wins = 0;
	for (auto c : letters) {
		bool b = false;
		if (check_left_diagonal_for_win(matrix, v, c)) {
			/*v[0] = '1';
			v[4] = '1';
			v[8] = '1';*/
			//solo_squirrel_wins++;
			b = true;
		}
		if (check_right_diagonal_for_win(matrix, v, c)) {
			/*v[2] = '1';
			v[4] = '1';
			v[6] = '1';*/
			//solo_squirrel_wins++;
			b = true;
		}
		for (int row = 0; row < 3; row++) {
			if (check_row(matrix, v, row, c)) {
				/*v[(row * 3)] = '1';
				v[(row * 3) + 1] = '1';
				v[(row * 3) + 2] = '1';*/
				//solo_squirrel_wins++;
				b = true;
			}
		}
		for (int column = 0; column < 3; column++) {
			if (check_column(matrix, v, column, c)) {
				/*v[column] = '1';
				v[column + 3] = '1';
				v[column + 6] = '1';*/
				//solo_squirrel_wins++;
				b = true;
			}
		}
		if (b) {
			solo_squirrel_wins++;
		}
	}
	v = "000000000";
	int team_squirrel_wins = 0;
	for (int i = 0; i < 26; i++) {
		for (int m = i; m < 26; m++) {
			char c = letters[i];
			char d = letters[m];
			if (isIn(matrix, c) && isIn(matrix, d) && c!=d) {
				//cout << c << " " << d << "\n";
				bool b = false;
				if (check_left_diagonal_for_win(matrix, v, c, d)) {
					//team_squirrel_wins++;
					b = true;
					/*v[0] = '1';
					v[4] = '1';
					v[8] = '1';*/
					//cout << "Left diagonal:" << c << " " << d << "\n";
				}
				if (check_right_diagonal_for_win(matrix, v, c, d)) {
					//team_squirrel_wins++;
					b = true;
					/*v[2] = '1';
					v[4] = '1';
					v[6] = '1';*/
					//cout << "Right diagonal:" << c << " " << d << "\n";
				}
				for (int row = 0; row < 3; row++) {
					if (check_row(matrix, v, row, c, d)) {
						//team_squirrel_wins++;
						b = true;
						/*v[(row * 3)] = '1';
						v[(row * 3) + 1] = '1';
						v[(row * 3) + 2] = '1';*/
						//cout << "Row:" << c << " " << d << "\n";
					}
				}
				for (int column = 0; column < 3; column++) {
					if (check_column(matrix, v, column, c, d)) {
						//team_squirrel_wins++;
						b = true;
						/*v[column] = '1';
						v[column + 3] = '1';
						v[column + 6] = '1';*/
						//cout << "Column:" << c << " " << d << "\n";
					}
				}
				if (b) {
					team_squirrel_wins++;
				}
			}
		}
	}
	cout << solo_squirrel_wins << "\n";
	cout << team_squirrel_wins << "\n";
}