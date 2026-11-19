#pragma once
#include "Node.h"
template <typename T>
class doubleLinkedList {
	int count;
	Node<T>* head;
	Node<T>* tail;

	doubleLinkedList(const doubleLinkedList&);
	doubleLinkedList& operator =(const doubleLinkedList&);

public:
	doubleLinkedList() : head(nullptr), tail(nullptr), count(0) {}

	~doubleLinkedList() {
		Node<T>* current = head;
		while (current) {
			Node<T>* next = current->getNext();
			delete current;
			current = next;
		}
	}

	void insertEnd(const T& item) {
		Node<T>* new_node = new Node<T>(item);
		if (!head)
			head = tail = new_node;
		else {
			tail->setNext(new_node);
			new_node->setPrev(tail);
			tail = new_node;

		}
		count++;
	}

	bool removeNode(Node<T>* old_node) {
		if (!old_node)
			return false;
		if (old_node->getPrev())
			old_node->getPrev()->setNext(old_node->getNext());
		else
			head = old_node->getNext();
		if (old_node->getNext())
			old_node->getNext()->setPrev(old_node->getPrev());
		else
			tail = old_node->getPrev();

		delete old_node;
		count--;
		return true;
	}

	bool removeFirst(T& out) {
		if (!head)
			return false;
		out = head->getData();
		return removeNode(head);
	}

	int Count() const {
		return count;
	}
	bool isEmpty() const {
		return count == 0;
	}
	Node<T>* GetHead() const{
		return head; 
	}

	Node<T>* Find(const T& item) const
	{
		Node<T>* c = head;

		while (c)
		{
			if (c->getData() == item)
				return c;

			c = c->getNext();
		}

		return nullptr;
	}
	bool GetAt(int index, T& out) const
	{
		if (index < 0 || index >= count) 
			return false;
		Node<T>* c = head;
		while (index--) 
			c = c->getNext();
		out = c->getData();
		return true;
	}
};