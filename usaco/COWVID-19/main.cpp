#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <array>
#include <set>
#include <fstream>
using namespace std;

bool f(const pair<int, int>& a, const pair<int, int>& b) {
    return a.second < b.second;
}

int simulate(const vector<pair<int, int>> &cows, const int cow_num) {
    vector<pair<bool, int>> infected(cows.size(), pair<bool, int>(false, 1));
    infected[cow_num] = pair<bool, int>(true, 1);
    int day = 1;
    while (true) {
        //do sim
        //check if any infected cows can infect other cows
        int cows_inf_today = 0;
        for (int pot_inf = 0; pot_inf < infected.size(); pot_inf++) {
            if (infected[pot_inf].first) {
                for (int pot_vic = 0; pot_vic < cows.size(); pot_vic++) {
                    if (abs(cows[pot_inf].second - cows[pot_vic].second) <= infected[pot_inf].second && infected[pot_vic].first == false) {
                        //infect the pot_vic'th cow
                        infected[pot_vic] = pair<bool, int>(true, day + 1);
                        cows_inf_today++;
                    }
                }
            }
        }
        if (cows_inf_today == 0) {
            break;
        }
        day++;
    }
    int ct = 0;
    for (auto i : infected) {
        //cout << i.first << " ";
        if (i.first) {
            ct++;
        }
    }
    //cout << "\n";
    return ct;
}

int main() {
    int N;
    cin >> N;
    vector<pair<int, int>> cows(N);
    for (int i = 0; i < N; i++) {
        cows[i].first = i;
        cin >> cows[i].second;
    }
    /*cout << "Cows:\n";
    for (auto i : cows) {
        cout << i.first << " -> " << i.second << "\n";
    }*/
    int max_inf = 0;
    for (int cow_num = 0; cow_num < N; cow_num++) {
        int sim = simulate(cows, cow_num);
        //cout << "Ran sim, if Cow #" << cow_num << " infected, " << sim << " cows will be infected\n";
        max_inf = std::max(max_inf, sim);
    }
    cout << max_inf << "\n";
}