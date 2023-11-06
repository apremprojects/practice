#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <algorithm>
#include <iostream>

using namespace std;

struct cow_t {
    int start_time, end_time, buckets, cow;
};

struct num_t {
    num_t(const int _cow, const int _time, const int _buckets, const bool _starting):cow(_cow), time(_time), buckets(_buckets), starting(_starting) {};
    int cow, time, buckets;
    bool starting;
};

bool operator<(const cow_t &a, const cow_t &b) {
    return a.start_time < b.start_time;
}

bool operator<(const num_t& a, const num_t& b) {
    return a.time < b.time;
}

vector<num_t> genNums(vector<cow_t>& cows) {
    vector<num_t> nums;
    nums.reserve(2 * cows.size());
    for (int i = 0; i < cows.size(); i++) {
        num_t one(cows[i].cow, cows[i].start_time, cows[i].buckets, true);
        num_t two(cows[i].cow, cows[i].end_time, cows[i].buckets, false);
        nums.push_back(one);
        nums.push_back(two);
    }
    sort(nums.begin(), nums.end());
    return nums;
}

vector<int> getBusyIndices(const vector<bool> &busies, int amt) {
    vector<int> results;
    int i = 0;
    while (amt > 0) {
        if (!busies[i]) {
            results.push_back(i);
            amt--;
        }
        i++;
    }
    return results;
}

int countBuckets(const vector<bool> &busies) {
    int ct = 0;
    for (auto i : busies) {
        if (i) {
            ct++;
        }
    }
    return ct;
}

int getMaxBucketsNeeded(vector<cow_t> &cows) {
    sort(cows.begin(), cows.end());
    vector<num_t> nums = genNums(cows);
    vector<vector<int>> cow_busy_indices(100);
    vector<bool> busies(1000, false);
    int maxBuckets = 0;
    for (num_t i : nums) {
        maxBuckets = std::max(maxBuckets, countBuckets(busies));
        if (i.starting) { //starting
            vector<int> busy_indices = getBusyIndices(busies, i.buckets);
            //busy the busy_indices
            for (int indice : busy_indices) {
                busies[indice] = true;
            }
            cow_busy_indices[i.cow] = busy_indices;
        }
        else {//ending
            vector<int> busy_indices = cow_busy_indices[i.cow];
            for (int indice : busy_indices) {
                busies[indice] = false;
            }
            cow_busy_indices[i.cow].clear();
        }
    }
    return maxBuckets;
}


int main() {
    int N;
    cin >> N;
    vector<cow_t> cows(N);
    for (int i = 0; i < N; i++) {
        cin >> cows[i].start_time >> cows[i].end_time >> cows[i].buckets;
        cows[i].cow = i;
    }
    int result = getMaxBucketsNeeded(cows);
    cout << result << "\n";
}