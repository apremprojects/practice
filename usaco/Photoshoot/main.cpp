#include <iostream>
#include <vector>
using namespace std;


int main() {
    int N;
    cin >> N;
    vector<int> B(N - 1);
    for (int i = 0; i < N - 1; i++) {
        cin >> B[i];
    }
    vector<int> A(N);
    for (int val = 1; val <= B[0] - 1; val++) {
        //val = first value of A
        bool worked = true;
        vector<bool> used(N + 1, false);

        A[0] = val;
        used[val] = true;

        for (int i = 1; i <= N - 1; i++) {
            A[i] = B[i - 1] - A[i - 1];

            if (A[i] < 1 || A[i] > N || used[A[i]]) {
                //A has invalid values
                worked = false;
                break;
            }

            used[A[i]] = true;
        }
        if (worked) {
            for (const int i : A) {
                cout << i << " ";
            }
            return 0;
        }
    }
}