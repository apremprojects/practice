#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <array>
#include <set>
#include <fstream>
using namespace std;

struct circle_t {
    int x_i;
    int y_i;
    int r_i;
    int i;
};

bool intersection(const circle_t& a, const circle_t& b) {
    int dist = sqrt((a.x_i - b.x_i) * (a.x_i - b.x_i) + (a.y_i - b.y_i) * (a.y_i - b.y_i));
    return dist == a.r_i + b.r_i;
}

bool operator<(const circle_t& a, const circle_t& b) {
    if (a.x_i < b.x_i) {
        return true;
    }
    else if(a.x_i == b.x_i){
        return a.y_i < b.y_i;
    }
    return false;
}

int main() {
    int N;
    cin >> N;
    vector<circle_t> circles(N);
    for (int i = 0; i < N; i++) {
        cin >> circles[i].x_i >> circles[i].y_i >> circles[i].r_i;
        circles[i].i = i;
    }
    vector<int> int_ct(N, 0);
    for (int i = 0; i < N; i++) {
        for (int b = 0; b < N; b++) {
            if (intersection(circles[i], circles[b])) {
                int_ct[i]++;
            }
        }
    }
    vector<circle_t> res;
    res.reserve(2);
    for (int i = 0; i < N; i++) {
        if (int_ct[i] == 1) {
            res.push_back(circles[i]);
        }
    }
    if (res[0].x_i == 0 && res[0].y_i == 0) {
        cout << res[1].x_i << " " << res[1].y_i << "\n";
    }
    else {
        cout << res[0].x_i << " " << res[0].y_i << "\n";
    }
}