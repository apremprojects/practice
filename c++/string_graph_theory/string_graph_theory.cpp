#include <iostream>
#include <vector>
#include <string>
#include <stack>

using std::cout;
using std::cin;
using std::vector;
using std::string;
using std::stack;

void dfsRec(int p, string& s, vector<bool>& visited, string& path) {
	static int count = 0;
	visited[p] = true;
	path.push_back(s[p]);
	if (path.length() == s.length()) {
		count++;
		cout << "Count -> " << count  << " -> " << path << "\n";
	}
	for (int i = 0; i < s.size(); i++) {
		if (!visited[i]) {
			dfsRec(i, s, visited, path);
		}
	}
	visited[p] = false;
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
	vector<bool> visited(s.size());
	string path;
	for (int i = 0; i < s.length(); i++) {
		dfs(i, s, visited, path);
	}
	return 0;
}
