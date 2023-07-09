#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
#include <list>
#include <string>
#include <queue>

struct Graph {
	std::vector<std::list<int>> adj_list;
	void print(){
		std::cout << "Adjacency list:\n";
		for (int i = 0; i < adj_list.size(); i++) {
			std::cout << i << " : ";
			for (auto b : adj_list[i]) {
				std::cout << b << " ";
			}
			std::cout << "\n";
		}
	}
};

Graph create_graph(const std::string& file_name) {
	Graph graph;
	std::ifstream stream(file_name);
	int vcount;
	stream >> vcount;
	graph.adj_list.resize(vcount);
	while (!stream.eof()) {
		int v1, v2;
		stream >> v1;
		stream >> v2;
		graph.adj_list[v1].push_back(v2);
	}
	return graph;
}

void dfs(const Graph& graph, const int vertex, std::vector<bool> &visited) {
	std::cout << "DFS\n";
	int vcur = vertex;
	std::stack<int> vstack;
	vstack.push(vertex);
	visited[vertex] = true;
	while (!vstack.empty()) {
		int v = vstack.top();
		vstack.pop();
		visited[v] = true;
		for (int n : graph.adj_list[v]) {
			if (!visited[n]) {
				vstack.push(n);
			}
		}
	}
}

int do_dfs(Graph& graph) {
	std::vector<bool> visited(graph.adj_list.size(), false);
	int cl_count = 0;
	for (int i = 0; i < graph.adj_list.size(); i++) {
		if (!visited[i]) {
			dfs(graph, i, visited);
			cl_count++;
		}
	}
	return cl_count;
}


void bfs(const Graph& graph, const int vertex, std::vector<bool>& visited) {
	std::queue<int> queue;
	queue.push(vertex);
	visited[vertex] = true;
	std::cout << "BFS\n";
	while (!queue.empty()) {
		int node = queue.front();
		queue.pop();
		for (int n : graph.adj_list[node]) { //iterate through node neighbors
			if (!visited[n]) {
				queue.push(n);
				visited[n] = true;
			}
		}
	}
}

int do_bfs(Graph& graph) {
	std::vector<bool> visited(graph.adj_list.size(), false);
	int cl_count = 0;
	for (int i = 0; i < graph.adj_list.size(); i++) {
		if (!visited[i]) {
			bfs(graph, i, visited);
			cl_count++;
		}
	}
	return cl_count;
}

int main() {
	Graph graph = create_graph("graph1.txt");
	graph.print();
	std::cout << "Cluster count(bfs) -> " << do_bfs(graph) << "\n";
	std::cout << "Cluster count(dfs) -> " << do_dfs(graph) << "\n";
	return 0;
}