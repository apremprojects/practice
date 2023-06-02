#include <iostream>
#include <cmath>


int factorial(int x) {
	if (x == 1) {
		return 1;
	}
	else {
		return factorial(x-1) * x;
	}
}


double ex(double x, int n) {
	double result = 0;
	int factorial = 1;
	double xs = x;
	for (int i = 0; i < n; i++) {
		result += xs / factorial;
		factorial *= (i+1);
		xs *= x;
	}
	return result;
}

int f(int x) {
	if (x == 0) {
		return 0;
	}
	if (x == 1) {
		return 1;
	}
	return f(x - 1) + f(x - 2);
}


int main()
{
	int n = 5;

	std::cout << "Listing factorials...\n";
	for (int i = 0; i < n; i++) {
		std::cout << factorial(5) << "\n";
	}

	std::cout << "Listing ex...\n";
	for (int i = 1; i < n; i++) {
		std::cout << ex(i,10) << "\n";
	}

	std::cout << "Listing fibonacci numbers...\n";
	for (int i = 0; i < n; i++) {
		std::cout << f(i) << "\n";
	}

	return 0;
}
