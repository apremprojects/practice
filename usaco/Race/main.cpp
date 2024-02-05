#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <algorithm>
#include <iostream>
using namespace std;

int dist(const int start_vel, const int time) {
	int dist = 0;
	for (int i = start_vel; i <= start_vel + time; i++) {
		dist += i;
	}
	return dist;
}

			/*
			cout << "ramp_t -> " << ramp_t << "\n";
			cout << "coast_distance -> " << coast_distance << "\n";
			cout << "coast_velocity -> " << coast_velocity << "\n";
			cout << "ramp_up_dist -> " << ramp_up_dist << "\n";
			cout << "ramp_down_dist -> " << ramp_down_dist << "\n";
			*/
int main() {
	int K, N;
	cin >> K >> N;
	vector<int> Xs(N);
	for (int i = 0; i < N; i++) {
		cin >> Xs[i];
	}
	for (const int X : Xs) {
		//cout << "X -> " << X << "\n";
		int ramp_t = 0;
		int ans = std::numeric_limits<int>::max();
		int ramp_up_dist = 0, ramp_down_dist = 0, coast_distance = 0, coast_velocity = 0;
		while (true) {
			int coast_velocity = X + ramp_t;
			ramp_up_dist = dist(0, coast_velocity);
			ramp_down_dist = dist(X, ramp_t - 1);
			coast_distance = K - ramp_up_dist - ramp_down_dist;
			if (ramp_up_dist < 0 || ramp_down_dist < 0 || coast_distance < 0) {
				//cout << ramp_up_dist << ", " << ramp_down_dist << ", " << coast_distance << "\n";
				break;
			}
			int a_time = coast_velocity;
			//cout << "Increase spd to " << coast_velocity << "m/s, taking " << a_time << " seconds and covering " << ramp_up_dist << " meters \n";
			
			int c_time = coast_distance / coast_velocity;
			while (ramp_up_dist + ramp_down_dist + (c_time * coast_velocity) < K) {
				c_time++;
			}
			//cout << "Keep speed at " << coast_velocity << "m/s for " << c_time << " seconds and covering " << c_time * coast_velocity << " meters\n";
			
			int d_time = ramp_t;
			//cout << "Decelerate to " << X << "m/s, taking " << d_time << " seconds and covering " << ramp_down_dist << " meters\n";
			
			int new_ans = a_time + c_time + d_time;
			ans = std::min(ans, new_ans);
			//cout << "here -> " << new_ans << "\n";
			ramp_t++;
		}
		if (ans == std::numeric_limits<int>::max()) {
			if ((K - dist(0, X)) % X == 0) {
				ans = X + (K - dist(0, X)) / X;
			}
		}
		cout << ans << "\n";
	}
}