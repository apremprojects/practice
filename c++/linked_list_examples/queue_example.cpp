#include "queue.h"

int main(void) {
	Queue<int> q;
	for (int i = 1; i <= 3; i++) {
		q.push(i);
		q.print();
		//std::cout << "front:" << q.front() << "\n";
	}
	while (!q.empty()) {
		//std::cout << "front:" << q.front() << "\n";
		q.pop();
		q.print();
	}
	return 0;
}