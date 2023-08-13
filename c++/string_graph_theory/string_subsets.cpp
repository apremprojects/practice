#include <iostream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

void subRec(int p, string& s, string& path) {
	static int count = 0;
	path.push_back(s[p]);
	count++;
	cout << "Count -> " << count << " -> " << path << "\n";
	for (int i = p + 1; i < s.size(); i++) {
		subRec(i, s, path);
	}
	path.pop_back();
}

void dfs(int p, string& s, vector<bool>& visited, string& path) {
	stack<int> stack;
	stack.push(p);
	while (!stack.empty()) {
		auto n = stack.top();
		stack.pop();
		if (visited[n]) {
			visited[n] = false;
			path.pop_back();
			continue;
		}
		visited[n] = true;
		path.push_back(s[n]);
		stack.push(n);
		static int count = 0;
		if (path.length() == s.length()) {
			count++;
			cout << "Count -> " << count << " -> " << path << "\n";
		}
		for (int i = s.length() - 1; i >= 0; i--) {
			if (!visited[i]) {
				stack.push(i);
			}
		}
	}
}

int main()
{
	string s;
	cin >> s;
	string path;
	path.reserve(s.length() + 1);
	for (int i = 0; i < s.length(); i++) {
		subRec(i, s, path);
	}
	return 0;
}
