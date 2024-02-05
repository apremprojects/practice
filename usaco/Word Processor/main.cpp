#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <algorithm>
#include <iostream>

using namespace std;

int main() {
	int N, K;
	cin >> N >> K;
	vector<string> raw_words(N);
	for (int i = 0; i < N; i++) {
		cin >> raw_words[i];
	}
	int len = 0;
	for (int i = 0; i < N; i++) {
		if (len + raw_words[i].size() > K) {
			cout << "\n";
			len = 0;
		}
		cout << raw_words[i] << " ";
		len += raw_words[i].size();
	}
}