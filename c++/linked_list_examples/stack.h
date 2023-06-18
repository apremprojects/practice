#pragma once
#include <iostream>

template <typename T>
class Stack {
public:
	Stack();
	~Stack();

	T top();
	bool empty();
	void push(const T& data);
	void pop();

	void print();

private:
	struct Node {
		Node(const T& d):data(d) {};
		T data;
		Node* next = nullptr;
	};
	Node* top_node;
};

template <typename T>
Stack<T>::Stack():top_node(nullptr) {}

template <typename T>
Stack<T>::~Stack() {}

template <typename T>
T Stack<T>::top() {
	return top_node;
}

template <typename T>
bool Stack<T>::empty() {
	return top_node == nullptr;
}

template <typename T>
void Stack<T>::push(const T& data) {
	Node* new_node = new Node(data);
	new_node->next = top_node;
	top_node = new_node;
}

template <typename T>
void Stack<T>::pop() {
	Node* tmp = top_node->next;
	top_node->next = nullptr;
	delete top_node;
	top_node = tmp;
}

template <typename T>
void Stack<T>::print() {
	Node* tmp = top_node;
	while (tmp) {
		std::cout << tmp->data << ", ";
		tmp = tmp->next;
	}
	std::cout << "\n";
}
