#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>

using std::cout;
using std::vector;
using std::string;
using std::ostream;
using std::ofstream;
using std::sort;

struct Record {
	string name;
	int age;
	int score;
};

vector<Record> getRecords(const size_t n);
void dump(const vector<Record>& records, ostream& out);

vector<Record> sortByIncreasingName(const vector<Record>& records) {
	auto out = records;
	std::sort(out.begin(), out.end(), [](const auto& a, const auto& b) {return a.name < b.name;});
	return out;
}

vector<Record> sortByIncreasingAge(const vector<Record>& records) {
	auto out = records;
	std::sort(out.begin(), out.end(), [](const auto& a, const auto& b) {return a.age < b.age; });
	return out;
}

vector<Record> sortByIncreasingScore(const vector<Record>& records) {
	auto out = records;
	std::sort(out.begin(), out.end(), [](const auto& a, const auto& b) {return a.score < b.score; });
	return out;
}

vector<Record> sortByDecreasingName(const vector<Record>& records) {
	auto out = records;
	std::sort(out.begin(), out.end(), [](const auto& a, const auto& b) {return a.name > b.name; });
	return out;
}

vector<Record> sortByDecreasingAge(const vector<Record>& records) {
	auto out = records;
	std::sort(out.begin(), out.end(), [](const auto& a, const auto& b) {return a.age > b.age; });
	return out;
}

vector<Record> sortByDecreasingScore(const vector<Record>& records) {
	auto out = records;
	std::sort(out.begin(), out.end(), [](const auto& a, const auto& b) {return a.score > b.score; });
	return out;
}

int main(const int argc, const char** argv) {
	const auto records = getRecords(15);
	// Print Records
	dump(records, cout);

	// Sort by increasing name
	dump(sortByIncreasingName(records), 
		ofstream("order_by_increasing_name.txt", ofstream::out | ofstream::trunc));
	// Sort by increasing age
	dump(sortByIncreasingAge(records), 
		ofstream("order_by_increasing_age.txt", ofstream::out | ofstream::trunc));
	// Sort by increasing score
	dump(sortByIncreasingScore(records), 
		ofstream("order_by_increasing_score.txt", ofstream::out | ofstream::trunc));
	// Sort by decreasing name
	dump(sortByDecreasingName(records), 
		ofstream("order_by_decreasing_name.txt", ofstream::out | ofstream::trunc));
	// Sort by decreasing age
	dump(sortByDecreasingAge(records), 
		ofstream("order_by_decreasing_age.txt", ofstream::out | ofstream::trunc));
	// Sort by decreasing score
	dump(sortByDecreasingScore(records), 
		ofstream("order_by_decreasing_score.txt", ofstream::out | ofstream::trunc));
	return 0;
}

string randName() {
	string name;
	size_t count = 3 + rand() % 4;
	name.push_back('A' + rand() % 26);
	for (size_t i = 0; i < count; i++) {
		char ch = 'a' + rand() % 26;
		name.push_back(ch);
	}
	return name;
}

vector<Record> getRecords(const size_t n) {
	vector<Record> records(n);
	for (auto& student : records) {
		student.name = randName();
		student.age = 12 + rand() % 3;
		student.score = 10 + rand() % 25;
	}
	return records;
}

void dump(const vector<Record>& records, ostream& out) {
	for (size_t i = 0; i < records.size(); i++) {
		out << i << ": (" 
				<< records[i].name << ", " 
				<< records[i].age << ", " 
				<< records[i].score << ")\n";
	}
}
