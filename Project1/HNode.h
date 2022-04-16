#pragma once
#include "Node.h"

template <class T>
class HNode : public Node<T> {

private:
	int key;

public:
	HNode(int key = 0, T itemptr = nullptr, Node<T>* next = nullptr, Node<T>* prev = nullptr) : 
		Node<T>(itemptr, next, prev) 
	{
		setKey(key);
	}

	int getKey() const { return key; }
	void setKey(int key) { this->key = key; }

};