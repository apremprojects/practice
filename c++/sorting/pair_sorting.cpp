#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <random>

using std::cout;
using std::vector;
using std::ostream;
using std::ofstream;
using std::sort;
using std::string;
using std::pair;

vector<pair<int, string>> getRandomPairs(const size_t n);
void dump(const vector<pair<int, string>>& pairs, ostream& out);

void sortByIncreasingFirst(vector<pair<int, string>>& pairs) {
	sort(pairs.begin(), pairs.end(), [](const auto& a, const auto& b) {
		return b.first > a.first;
	});
}

void sortByIncreasingSecond(vector<pair<int, string>>& pairs) {
	sort(pairs.begin(), pairs.end(), [](const auto& a, const auto& b) {
		return b.second > a.second;
	});
}

void sortByDecreasingFirst(vector<pair<int, string>>& pairs) {
	sort(pairs.begin(), pairs.end(), [](const auto& a, const auto& b) {
		return b.first < a.first;
	});
}

void sortByDecreasingSecond(vector<pair<int, string>>& pairs) {
	sort(pairs.begin(), pairs.end(), [](const auto& a, const auto& b) {
		return b.second < a.second;
	});
}

int main(const int argc, const char** argv) {
	vector<pair<int, string>> pairs = getRandomPairs(10);
	dump(pairs, cout);

	// Sort by increasing first
	sortByIncreasingFirst(pairs);
	dump(pairs, ofstream("pairs_order_by_increasing_first.txt", ofstream::out | ofstream::trunc));

	// Sort by increasing second
	sortByIncreasingSecond(pairs);
	dump(pairs, ofstream("pairs_order_by_increasing_second.txt", ofstream::out | ofstream::trunc));

	// Sort by decreasing first
	sortByDecreasingFirst(pairs);
	dump(pairs, ofstream("pairs_order_by_decreasing_first.txt", ofstream::out | ofstream::trunc));

	// Sort by decreasing second
	sortByDecreasingSecond(pairs);
	dump(pairs, ofstream("pairs_order_by_decreasing_second.txt", ofstream::out | ofstream::trunc));

	return 0;
}

void dump(const vector<pair<int, string>>& pairs, ostream& out) {
	for (size_t i = 0; i < pairs.size(); i++) {
		out << i << " : (" << pairs[i].first << ", " << pairs[i].second << ")\n";
	}
}

string randString() {
	string name;
	size_t count = 2 + rand() % 5;
	for (size_t i = 0; i < count; i++) {
		char ch = 'a' + rand() % 26;
		name.push_back(ch);
	}
	return name;
}

vector<pair<int, string>> getRandomPairs(const size_t n) {
	vector<pair<int, string>> pairs;
	pairs.reserve(n);
	for (size_t i = 0; i < n; i++) {
		pairs.emplace_back(250 - rand() % 500, randString());
	}
	return pairs;
}
