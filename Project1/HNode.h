#pragma once
#include "Node.h"

//A special type of node to be used in the HashMap. It carries a key for each item, as well the normal data members present in the Node class.
template <class T>
class HNode : public Node<T> {

private:
	int key;  //Key corresponding to the item

public:

	//Constructor
	HNode(int key = 0, T item = nullptr, Node<T>* next = nullptr, Node<T>* prev = nullptr) : 
		Node<T>(item, next, prev) 
	{
		setKey(key);
	}

	//Setters and Getters
	int getKey() const { return key; }
	void setKey(int key) { this->key = key; }

};