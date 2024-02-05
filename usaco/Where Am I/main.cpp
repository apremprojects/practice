#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <algorithm>
#include <iostream>

using namespace std;

int getAppearances(const string& mailboxes, const int start, const int K) {
    string t = mailboxes.substr(start, K + 1);
    //cout << "Searching for " << t << "\n";
    int ct = 0;
    for (int i = 0; i < mailboxes.size() - K; i++) {
        string m = mailboxes.substr(i, K + 1);
        //cout << "m -> " << m << "\n";
        if (t == m) {
            ct++;
        }
    }
    return ct;
}

int main() {
    int N;
    string mailboxes;
    cin >> N >> mailboxes;
    for (int K = 1; K < N -1; K++) {
        bool b = true;
        for (int start = 0; start < N - K; start++) {
            //cout << mailboxes.substr(start, K + 1) << " -> " << getAppearances(mailboxes, start, K) << "\n";
            if (getAppearances(mailboxes, start, K) != 1) {
                //check if it is possible to uniquely know your position there.
                b = false;
            }
            
        }
        if (b) {
            cout << K + 1 << "\n";
            return 0;
        }
    }
}