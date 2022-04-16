#pragma once

#include <iostream>
using namespace std;

template <class T>
class Node {

private:
	T itemptr;
	Node<T>* next;
	Node<T>* prev;

public:

	Node(T itemptr = nullptr, Node<T>* next = nullptr, Node<T>* prev = nullptr) {
		setItemPtr(itemptr);
		setNext(next);
		setPrev(prev);
	}

	friend ostream& operator << (ostream & out, Node<T> node);

	virtual int getKey() const { return -1; }
	virtual void setKey(int key) { }
	
	T getItemPtr() const { return itemptr; }
	void setItemPtr(T itemptr) { this->itemptr = itemptr; }

	Node<T>* getNext() const { return next; }
	void setNext(Node<T>* next) { this->next = next; }

	Node<T>* getPrev() const { return prev; }
	void setPrev(Node<T>* prev) { this->prev = prev; }

	void printNode() const {
		cout << *itemptr << " ";
	}
};
