#include "doubly_linked_list.h"

int main(void) {
	DoublyLinkedList<int> dlist;
	std::cout << "Populating dlist with push_back\n";
	for(int i = 1; i <= 10; i++) {
		dlist.push_back(i);
	}
	std::cout << "Printing dlist from front to back and back to front\n";
	dlist.printForward();
	dlist.printReverse();
	std::cout << "Printing front of dlist and popping the front\n";
	while(!dlist.empty()) {
		std::cout << dlist.front() << "\n";
		dlist.pop_front();
	}
	std::cout << "Populating dlist with push_front\n";
	for (int i = 1; i <= 10; i++) {
		dlist.push_front(i);
	}
	std::cout << "Printing dlist front to back and back to front\n";
	dlist.printForward();
	dlist.printReverse();
	std::cout << "Printing back of dlist and popping the back\n";
	while (!dlist.empty()) {
		std::cout << dlist.back() << "\n";
		dlist.pop_back();
	}
	return 0;
}
