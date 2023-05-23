#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>
#include <fstream>

using std::cout;
using std::vector;
using std::string;
using std::ostream;
using std::ofstream;
using std::sort;
using std::shared_ptr;

class Record {
public:
	Record(const int id, const double score, const string name)
		: id_(id),
		  score_(score),
		  name_(name) {};

	int id() { return id_; }
	double score() const { return score_; }
	string name() const { return name_; }

private:
	int id_;
	double score_;
	string name_;
};

vector<shared_ptr<Record>> getRandomRecords(const size_t n);
void dump(const vector<shared_ptr<Record>>& records, ostream& out);

void sortByIncreasingId(vector<shared_ptr<Record>>& records) {
	sort(records.begin(), records.end(), [](const auto& a, const auto& b) {return b->id() > a->id(); });
}

void sortByIncreasingScore(vector<shared_ptr<Record>>& records) {
	sort(records.begin(), records.end(), [](const auto& a, const auto& b) {return b->score() > a->score(); });
}

void sortByIncreasingName(vector<shared_ptr<Record>>& records) {
	sort(records.begin(), records.end(), [](const auto& a, const auto& b) {return b->name() > a->name(); });
}

int main(const int argc, const char** argv) {
	auto records = getRandomRecords(10);
	dump(records, cout);

	// Sort by increasing ids
	sortByIncreasingId(records);
	dump(records, ofstream("objects_order_by_increasing_id.txt", ofstream::out | ofstream::trunc));

	// Sort by increasing scores
	sortByIncreasingScore(records);
	dump(records, ofstream("objects_order_by_increasing_score.txt", ofstream::out | ofstream::trunc));

	// Sort by increasing names
	sortByIncreasingName(records);
	dump(records, ofstream("objects_order_by_increasing_names.txt", ofstream::out | ofstream::trunc));

	return 0;
}

string randName() {
	string name;
	size_t count = 3 + rand() % 6;
	for (size_t i = 0; i < count; i++) {
		char ch = 'A' + rand() % 26;
		name.push_back(ch);
	}
	return name;
}

void dump(const vector<shared_ptr<Record>>& records, ostream& out) {
	for (size_t i = 0; i < records.size(); i++) {
		out << i << ": (" << records[i]->id() << ", " << records[i]->score() << ", " << records[i]->name() << ")\n";
	}
}

vector<shared_ptr<Record>> getRandomRecords(const size_t n) {
	vector<shared_ptr<Record>> records(n);
	for (size_t i = 0; i < n; i++) {
		const double score = 1.0 / static_cast<double>(rand() % 300);
		records[i].reset(new Record(n - i, score, randName()));
	}
	return records;
}
