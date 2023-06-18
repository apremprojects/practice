// LinkedListDemo.cpp : Defines the entry point for the application.
//
#include <iostream>
#include <fstream>
template <typename T>
struct Node {
	Node(T _data) : data(_data) {};
	~Node() {
		//std::cout << "Node with data " << data << " being destructed.\n"; 
	};
	T data;
	Node<T>* next = nullptr;
};

Node<int>* createLinkedList(const std::string& file_path){
	std::ifstream stream(file_path, std::ofstream::in);
	int num;
	stream >> num;
	Node<int> *head = new Node<int>(num);
	Node<int>* prevNode = head;
	while (!stream.eof()) {
		stream >> num;
		auto node = new Node<int>(num);
		prevNode->next = node;
		prevNode = node;
	}
	return head;
}

template <typename T>
void printLinkedList(Node<T> *node) {
	while (node) {
		std::cout << node->data << ", ";
		node = node->next;
	}
	std::cout << '\n';
}

template <typename T>
void deleteLinkedList(Node<T> *&currentNode) {
	while (currentNode != nullptr) {
		auto temp = currentNode->next;
		currentNode->next = nullptr;
		delete currentNode;
		currentNode = temp;
	}
}

template <typename T>
void deleteLinkedList(Node<T> *&node, int data) {
	Node<T>* temp = node;
	Node<T>* prevNode = nullptr;
	while (temp-> data != data) {
		prevNode = temp;
		temp = temp->next;
	}
	if (prevNode == nullptr) {
		node = node->next;
	}
	else {
		prevNode->next = temp->next;
	}
	temp->next = nullptr;
	delete temp;
}

template <typename T>
void insertLinkedList(Node<T>*& node, int val, int newVal) {
	Node<T>* temp = node;
	while (temp->data != val) {
		temp = temp->next;
	}
	if (temp->next != nullptr) {
		Node<T>* newNode = new Node<T>(newVal);
		newNode->next = temp->next;
		temp->next = newNode;
	}

}

template <typename T>
void invert(Node<T>*& nextNode) {
	Node<T>* prevNode = nullptr;
	while (nextNode != nullptr)
	{
		Node<T>* tmp = nextNode->next;
		nextNode->next = prevNode;
		prevNode = nextNode;
		nextNode = tmp;
	}
	nextNode = prevNode;
}

int main(const int argc, const char** argv) {
	std::cout << "Creating Linked List...\n";
	if (argc != 2) {
		std::cout << "Filepath missing.\n";
		return 1;
	}
	auto head = createLinkedList(argv[1]);
	std::cout << "Printing Linked List...\n";
	printLinkedList(head);
	std::cout << "Inverting Linked List...\n";
	invert(head);
	std::cout << "Printing Linked List...\n";
	printLinkedList(head);
}
