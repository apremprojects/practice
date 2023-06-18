#pragma once
#include <iostream>
template <typename T>
class DoublyLinkedList {
public:
	DoublyLinkedList();
	~DoublyLinkedList();

	bool empty();

	T front();
	void push_front(const T& data);
	void pop_front();

	T back();
	void push_back(const T& data);
	void pop_back();

	void printForward();
	void printReverse();

private:
	struct Node {
		Node(const T& d) :data(d) {};
		T data;
		Node* prev = nullptr;
		Node* next = nullptr;
	};
	Node* front_node;
	Node* back_node;
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList()
	: front_node(nullptr),
	  back_node(nullptr) {}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {}

template <typename T>
bool DoublyLinkedList<T>::empty() {
	return front_node == nullptr;
}

template <typename T>
T DoublyLinkedList<T>::front() {
	return front_node->data;
}

template <typename T>
void DoublyLinkedList<T>::push_front(const T& data) {
	Node* new_node = new Node(data);
	if (front_node) {
		new_node->next = front_node;
		front_node->prev = new_node;
		front_node = new_node;
	}
	else {
		front_node = back_node = new_node;
	}
}

template <typename T>
void DoublyLinkedList<T>::pop_front() {
	Node *tmp = front_node->next;
	front_node->next = nullptr;
	delete front_node;
	if (tmp) {
		tmp->prev = nullptr;
	}
	else {
		back_node = nullptr;
	}
	front_node = tmp;
}

template <typename T>
T DoublyLinkedList<T>::back() {
	return back_node->data;
}

template <typename T>
void DoublyLinkedList<T>::push_back(const T& data) {
	Node *new_node = new Node(data);
	if (back_node) {
		back_node->next = new_node;
		new_node->prev = back_node;
		back_node = new_node;
	} else {
		back_node = front_node = new_node;
	}
}

template <typename T>
void DoublyLinkedList<T>::pop_back() {
	Node* tmp = back_node->prev;
	back_node->prev = nullptr;
	delete back_node;
	if (tmp) {
		tmp->next = nullptr;
	}
	else {
		front_node = nullptr;
	}
	back_node = tmp;
}

template <typename T>
void DoublyLinkedList<T>::printForward() {
	Node* tmp = front_node;
	while (tmp) {
		std::cout << tmp->data << ", ";
		tmp = tmp->next;
	}
	std::cout << "\n";
}

template <typename T>
void DoublyLinkedList<T>::printReverse() {
	Node* tmp = back_node;
	while (tmp) {
		std::cout << tmp->data << ", ";
			tmp = tmp->prev;
	}
	std::cout << "\n";
}
