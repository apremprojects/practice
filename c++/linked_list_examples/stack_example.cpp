#include "stack.h"

int main(void) {
	Stack<int> stack;
	for (int i = 1; i <= 10; i++) {
		stack.push(i);
		stack.print();
	}
	while(!stack.empty()) {
		stack.pop();
		stack.print();
	}
	return 0;
}
