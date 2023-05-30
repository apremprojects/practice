// random_number_shuffling.cpp : Defines the entry point for the application.
//
#include <iostream>
#include <vector>
#include <vector>
#include <numeric>


class Shuffle {
public:
	Shuffle(std::vector<int> _v) : v(_v) {};
	int pop() {
		std::swap(v[rand() % v.size()], v[v.size() - 1]);
		int num = v.back();
		v.pop_back();
		return num;
	}
	bool isNumLeft() {
		return v.size() > 0;
	}
private:
	std::vector<int> v;
};


int main() {
	std::vector<int> v(10);
	std::iota(v.begin(), v.end(), 0);
	Shuffle shuffle(v);
	while (shuffle.isNumLeft()) {
		std::cout << "Number: " << shuffle.pop() << "\n";
	}
	return 0;
}
