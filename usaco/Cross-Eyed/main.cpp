#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <array>
#include <set>
#include <fstream>
using namespace std;

int main() {
	string A, B;
	cin >> A >> B;
	string Acpy = A;
	string Bcpy = B;
	for (char& i : Acpy) {
		if (i == '6')
		{
			i = '5';
		}
	}
	for (char& i : Bcpy) {
		if (i == '6')
		{
			i = '5';
		}
	}
	int min = stoi(Acpy) + stoi(Bcpy);
	Acpy = A;
	Bcpy = B;
	for (char& i : Acpy) {
		if (i == '5')
		{
			i = '6';
		}
	}
	for (char& i : Bcpy) {
		if (i == '5')
		{
			i = '6';
		}
	}
	int max = stoi(Acpy) + stoi(Bcpy);
	cout << min << " " << max << "\n";
}