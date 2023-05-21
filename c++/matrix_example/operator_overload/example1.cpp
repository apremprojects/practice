#include <iostream>

template <typename T>
struct Vector {
	T x, y, z;
};

template <typename T>
Vector<T> operator+(const Vector<T>& a, const Vector<T>& b) {
	Vector<T> out;
	out.x = a.x + b.x;
	out.y = a.y + b.y;
	out.z = a.z + b.z;
	return out;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Vector<T>& a) {
	out << a.x << " " << a.y << " " << a.z;
	return out;
}

template <typename T>
std::istream& operator>>(std::istream& in, Vector<T>& a) {
	in >> a.x >> a.y >> a.z;
	return in;
}

int main(const int argc, const char** argv) {
	Vector<int> p1 = { 1, 2, 3 };
	Vector<int> p2 = { 4, 5, 6 };

	Vector<int> p3 = p1 + p2;

	std::cout << "p1: " << p1 << "\n";
	std::cout << "p2: " << p2 << "\n";
	std::cout << "p3: " << p3 << "\n";

	Vector<int> p4;
	std::cout << "Enter vector p4: ";
	std::cin >> p4;

	std::cout << "p4: " << p4 << "\n";

	// a, b, c, d  a+b+c+d
	// res = add(add(add(a, b), c), d)

	return 0;
}
