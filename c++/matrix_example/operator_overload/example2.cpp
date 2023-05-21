#include <iostream>

template <typename T>
class Vector {
public:
	Vector() {};

	Vector(const T x, const T y, const T z) {
		data[0] = x;
		data[1] = y;
		data[2] = z;
	}

	Vector<T> operator+(const Vector<T>& p) {
		return Vector<T>(data[0] + p.data[0], data[1] + p.data[1], data[2] + p.data[2]);
	}

private:
	template <typename T>
	friend std::ostream& operator<<(std::ostream& out, const Vector<T>& a);

	template <typename T>
	friend std::istream& operator>>(std::istream& in, Vector<T>& a);

	T data[3];
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const Vector<T>& a) {
	out << a.data[0] << " " << a.data[1] << " " << a.data[2];
	return out;
}

template <typename T>
std::istream& operator>>(std::istream& in, Vector<T>& a) {
	in >> a.data[0] >> a.data[1] >> a.data[2];
	return in;
}

int main(const int argc, const char** argv) {
	Vector<int> p1(1, 2, 3);
	Vector<int> p2(4, 5, 6);

	Vector<int> p3 = p1 + p2;

	std::cout << "p1: " << p1 << "\n";
	std::cout << "p2: " << p2 << "\n";
	std::cout << "p3: " << p3 << "\n";

	Vector<int> p4;
	std::cout << "Enter vector p4: ";
	std::cin >> p4;

	std::cout << "p4 : " << p4 << "\n";

	return 0;
}
