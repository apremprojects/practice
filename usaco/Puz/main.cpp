#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

int main() {
	double A, B, V;
	cin >> A >> B >> V;
	if (A > V) {
		cout << "1\n";
		return 0;
	}
	double dminusone = (V - A) / (A - B);
	cout << static_cast<int>(ceil(dminusone) + 1);
}