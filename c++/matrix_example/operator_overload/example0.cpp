#include <iostream>

template <typename T>
std::pair<T, T> operator+(const std::pair<T, T>& a, const std::pair<T, T>& b) {
	std::pair<T, T> ret;
	ret.first = a.first + b.first;
	ret.second = a.second + b.second;
	return ret;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::pair<T, T>& a) {
	out << a.first << " " << a.second;
	return out;
}

template <typename T>
std::istream& operator>>(std::istream& in, std::pair<T, T>& a) {
	in >> a.first >> a.second;
	return in;
}

int main(const int argc, const char** argv) {
	std::pair<int, int> p1(1, 2);
	std::pair<int, int> p2(4, 5);

	std::pair<int, int> p3 = p1 + p2;

	std::cout << "p1: " << p1 << "\n";
	std::cout << "p2: " << p2 << "\n";
	std::cout << "p3 (p1 + p2) = " << p3 << "\n";

	std::pair<int, int> p4;
	std::cout << "Enter vector p4: ";
	std::cin >> p4;

	std::cout << "p4 : " << p4 << "\n";

	return 0;
}
