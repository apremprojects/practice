#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <list>
#include <algorithm>
#include <array>
#include <iostream>

using namespace std;

int count_neighbors(const int N, const int num, const vector<array<int, 2>>& cow_pairs) {
	int ct = 0;
	for (int i = 0; i <= N - 1; i++) {
		if (cow_pairs[i][0] == num || cow_pairs[i][1] == num) {
			ct++;
		}
	}
	return ct;
}

int name_to_num(const string name) {
	if (name == "Beatrice") {
		return 0;
	}
	else if (name == "Belinda") {
		return 1;
	}
	else if (name == "Bella") {
		return 2;
	}
	else if (name == "Bessie") {
		return 3;
	}
	else if (name == "Betsy") {
		return 4;
	}
	else if (name == "Blue") {
		return 5;
	}
	else if (name == "Buttercup") {
		return 6;
	}
	else if (name == "Sue"){
		return 7;
	}
	cout << "Never happens";
	return stoi(name);
}

string num_to_name(const int i) {
	if (i == 0) {
		return "Beatrice";
	}
	else if (i == 1) {
		return "Belinda";
	}
	else if (i == 2) {
		return "Bella";
	}
	else if (i == 3) {
		return "Bessie";
	}
	else if (i == 4) {
		return "Betsy";
	}
	else if (i == 5) {
		return "Blue";
	}
	else if (i == 6) {
		return "Buttercup";
	}
	else if (i == 7) {
		return "Sue";
	}
	cout << "Never happens\n";
	return to_string(i);
}

int main() {
	int N;
	cin >> N;
	vector<array<int, 2>> cow_pairs(N);		
	string first_name = "-1", second_name = "-1";
	for (int i = 0; i <= N-1; i++) {
		cin >> first_name;
		cow_pairs[i][0] = name_to_num(first_name);
		for (int j = 1; j <= 4; j++) {
			cin >> second_name;
		}
		cin >> second_name;
		cow_pairs[i][1] = name_to_num(second_name);
		//cout << "Name -> " << cow_pairs[i][0] << " " << cow_pairs[i][1] << "\n";
	}
	vector<int> sol(8, -1);
	vector<bool> used(8, false);
	for (int cow = 0; cow <= 7; cow++) {
		//cout << "Cow #" << cow << " has " << count_neighbors(N, cow, cow_pairs) << " neighbors.\n";
		if (count_neighbors(N, cow, cow_pairs) < 2) {
			sol[0] = cow;
			used[cow] = true;
			break;
		}
	}
	//start cow is first cow with less than 2 neighbors
	for (int i = 1; i <= 7; i++) {
		//cout << "i -> " << i << "\n";
		for (int j = 0; j <= N-1; j++) {
			//cout << "j -> " << j << "\n";
			if (sol[i - 1] == cow_pairs[j][0] && !used[cow_pairs[j][1]]) {
				sol[i] = cow_pairs[j][1];
				used[cow_pairs[j][1]] = true;
				//cout << "here\n";
				break;
			}
			else if (sol[i - 1] == cow_pairs[j][1] && !used[cow_pairs[j][0]]) {
				sol[i] = cow_pairs[j][0];
				used[cow_pairs[j][0]] = true;
				//cout << "here\n";
				break;
			}
		}
		if (sol[i] != -1) {
			continue;
		}
		for (int cow = 0; cow <= 7; cow++) {
			if (used[cow]) {
				//cout << "Continuing\n";
				continue;
			}
			if (count_neighbors(N, cow, cow_pairs) < 2) {
				sol[i] = cow;
				used[cow] = true;
				break;
			}
		}
	}
	for (const int i : sol) {
		cout << num_to_name(i) << "\n";
	}
}
/*
3
Buttercup must be milked beside Bella
Blue must be milked beside Bella
Sue must be milked beside Beatrice
*/