#include <iostream>
#include <vector>
#include <string>

using namespace std;

const vector<pair<int, int>> generate_points(const int n, const int max_x, const int max_y) {
	vector<pair<int, int>> result(n);
	for (int i = 0; i < n; i++) {
		result[i] = pair<int, int>(rand() % max_x, rand() % max_y);
	}
	return result;
}

bool operator<(const pair<int, int> &a, const pair<int, int> &b) {
	if (a.first <= b.first) {
		if (a.second <= b.second) {
			return true;
		}
	}
	return false;
}

void disp_points(const vector<pair<int, int>>& a) {
	cout << "Points: \n";
	for (auto n : a) {
		cout << n.first << ", " << n.second << "\n";
	}
}

const pair<pair<int, int>, pair<int, int>> bounding_box(const vector<pair<int, int>> &result) {
	pair<int, int> ll = result[0];
	pair<int, int> ur = result[0];
	for (int i = 0; i < result.size(); i++) {
		ll.first = std::min(ll.first, result[i].first);
		ur.first = std::max(ur.first, result[i].first);
		ll.second = std::min(ll.second, result[i].second);
		ur.second = std::max(ur.second, result[i].second);
	}
	return pair<pair<int, int>, pair<int,int>>(ll, ur);
}

int main()
{
	auto result = generate_points(10, 300, 300);
	disp_points(result);
	auto b_box = bounding_box(result);
	cout << "Lower left -> (" << b_box.first.first << ", " << b_box.first.second << ")\n";
	cout << "Upper right -> (" << b_box.second.first << ", " << b_box.second.second << ")\n";
}
