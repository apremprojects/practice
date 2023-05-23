#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <random>
#include <cmath>

using std::cout;
using std::vector;
using std::ostream;
using std::ofstream;
using std::sort;

struct Point {
	double x;
	double y;
	double z;
};

vector<Point> getRandomPoints(const size_t n);
void dump(const vector<Point>& points, ostream& out);

void sortByIncreasingX(vector<Point>& points) {
	std::sort(points.begin(), points.end(), [](const auto &a, const auto &b){return a.x < b.x; });
}

void sortByIncreasingY(vector<Point>& points) {
	std::sort(points.begin(), points.end(), [](const auto& a, const auto& b){return a.y < b.y; });
}

void sortByIncreasingDistanceToOrigin(vector<Point>& points) {
	std::sort(points.begin(), points.end(), [](const auto& a, const auto& b) {
		return sqrt(pow(a.x,2) + pow(a.y, 2) + pow(a.z, 2)) < sqrt(pow(b.x, 2) + pow(b.y, 2) + pow(b.z, 2));
	});
}

void sortByDecreasingX(vector<Point>& points) {
	std::sort(points.begin(), points.end(), [](const auto &a, const auto &b){return a.x > b.x; });
}

int main(const int argc, const char** argv) {
	vector<Point> points = getRandomPoints(10);
	dump(points, cout);

	// Sort by increasing x coordinate
	sortByIncreasingX(points);
	dump(points, ofstream("point_order_by_increasing_x.txt", ofstream::out | ofstream::trunc));

	// Sort by increasing y coordinate
	sortByIncreasingY(points);
	dump(points, ofstream("point_order_by_increasing_y.txt", ofstream::out | ofstream::trunc));

	// Sort by increasing distance to origin
	sortByIncreasingDistanceToOrigin(points);
	dump(points, ofstream("point_order_by_increasing_distance_to_origin.txt", ofstream::out | ofstream::trunc));

	// Sort by increasing x coordinate
	sortByDecreasingX(points);
	dump(points, ofstream("point_order_by_decreasing_x.txt", ofstream::out | ofstream::trunc));

	return 0;
}

void dump(const vector<Point>& points, ostream& out) {
	for (size_t i = 0; i < points.size(); i++) {
		out << i << " : (" 
				<< points[i].x << ", " 
				<< points[i].y << ", " 
				<< points[i].z << ")\n";
	}
}

vector<Point> getRandomPoints(const size_t n) {
	vector<Point> points(n);
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dis(-100.0, 100.0);
	for (size_t i = 0; i < n; i++) {
		points[i].x = dis(gen);
		points[i].y = dis(gen);
		points[i].z = dis(gen);
	}
	return points;
}
