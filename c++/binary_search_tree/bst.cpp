#include <stack>
#include <string>
#include <iostream>
#include <vector>

template <typename T>
struct Node {
	Node(const T& d) : data(d) {};
	T data;
	Node<T>* left_child = nullptr;
	Node<T>* right_child = nullptr;
};

template <typename T>
void addToBST(Node<T>*& root, const T& data) {
	if (!root) {
		root = new Node(data);
	}
	else {
		Node<T>* tmp = root;
		while (tmp) {
			if (tmp->data <= data) {
				if (tmp->right_child) {
					tmp = tmp->right_child;
				}
				else {
					tmp->right_child = new Node(data);
					return;
				}
			}
			else {
				if (tmp->left_child) {
					tmp = tmp->left_child;
				}
				else {
					tmp->left_child = new Node(data);
					return;
				}
			}
		}
	}
}

template <typename T>
void preorder(Node<T>* node) {
	if (node == nullptr) {
		return;
	}
	std::cout << node->data << ", ";
	preorder(node->left_child);
	preorder(node->right_child);
}

template <typename T>
void inorder(Node<T>* node) {
	if (node == nullptr) {
		return;
	}
	inorder(node->left_child);
	std::cout << node->data << ", ";
	inorder(node->right_child);
}

template <typename T>
void postorder(Node<T>* node) {
	if (node == nullptr) {
		return;
	}
	postorder(node->left_child);
	postorder(node->right_child);
	std::cout << node->data << ", ";
}

template <typename T>
void addToBSTRecursive(Node<T>*& root, const T& data) {
	if (!root) {
		root = new Node(data);
	}
	else {
		Node<T>* tmp = root;
		if (tmp->data <= data) {
			if (tmp->right_child) {
				tmp = tmp->right_child;
			}
			else {
				tmp->right_child = new Node(data);
				return;
			}
		}
		else {
			if (tmp->left_child) {
				tmp = tmp->left_child;
			}
			else {
				tmp->left_child = new Node(data);
				return;
			}
		}
		addToBST(tmp, data);
	}
}

int main(void) {
	Node<int>* root = nullptr;
	Node<int>* root2 = nullptr;
	std::cout << "\nAdding to bst normally";
	std::vector<int> nums{1, 3, -1, 8, 2};
	for (auto num : nums) {
		addToBST(root, num);
	}
	std::cout << "\nAdding to bst recursively";
	for (auto num : nums) {
		addToBSTRecursive(root2, num);
	}
	std::cout << "Printing normal tree";
	std::cout << "\nPreorder : ";
	preorder(root);
	std::cout << "\nInorder : ";
	inorder(root);
	std::cout << "\nPostorder : ";
	postorder(root);
	std::cout << "\nPrinting recursively added tree";
	std::cout << "\nPreorder : ";
	preorder(root2);
	std::cout << "\nInorder : ";
	inorder(root2);
	std::cout << "\nPostorder : ";
	postorder(root2);
	std::cout << "\n";
	return 0;
}
