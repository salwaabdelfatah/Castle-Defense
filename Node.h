#pragma once
template <typename T>
class Node {
	T data;
	Node* next;
	Node* prev;
public:
	Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}

	void setNext(Node<T>* nextNode) {
		next = nextNode;
	}
	void setPrev(Node<T>* prevNode) {
		prev = prevNode;
	}
	void setData(const T& value) {
		data = value;
	}

	T getData() {
		return data;
	}
	Node<T>* getNext() {
		return next;
	}
	Node<T>* getPrev() {
		return prev;
	}
};