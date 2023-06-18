#pragma once
#include <iostream>

template <typename T>
class Queue {
public:
	Queue();
	~Queue();

	T front();
	bool empty();
	void push(const T& data);
	void pop();

	void print();

private:
	struct Node {
		Node(const T& d) :data(d) {};
		T data;
		Node* next = nullptr;
	};
	Node* front_node;
	Node* back_node;
};

template <typename T>
Queue<T>::Queue()
	: front_node(nullptr),
    back_node(nullptr) {}

template <typename T>
Queue<T>::~Queue() {}

template <typename T>
T Queue<T>::front() {
	return front_node->data;
}

template <typename T>
bool Queue<T>::empty() {
	return front_node == nullptr;
}

template <typename T>
void Queue<T>::push(const T& data) {
	if (back_node) {
		back_node->next = new Node(data);
		back_node = back_node->next;
	}
	else {
		front_node = back_node = new Node(data);
	}
}

template <typename T>
void Queue<T>::pop() {
	Node* tmp = front_node->next;
	front_node->next = nullptr;
	delete front_node;
	if (tmp) {
		front_node = tmp;
	}
	else {
		front_node = nullptr;
		back_node = nullptr;
	}
}

template <typename T>
void Queue<T>::print() {
	Node* tmp = front_node;
	while (tmp) {
		std::cout << tmp->data << ", ";
		tmp = tmp->next;
	}
	std::cout << "\n";
}
