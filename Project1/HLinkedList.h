#pragma once
#include "LinkedList.h"
#include "HNode.h"

//A class which inherits from the LinkedList class, to be used in the HashMap, since it will carry chains made up of nodes carrying the
//item as well as its key.
template <class T>
class HLinkedList : public LinkedList<T> {

public:
	
	//Inserts an item at the end of the list along with its corresponding key. If no key is given, set it to -1
	void insertEnd(T newItem, int key = -1) {                     //O(1)
		HNode<T>* temp = new HNode<T>(key, newItem);

		if (!this->tail) {
			this->head = this->tail = temp;
			return;
		}

		temp->setPrev(this->tail);
		this->tail->setNext(temp);
		this->tail = temp;
	}

	//Finds an item in the list using its key, and returns a pointer to the node carrying the item
	Node<T>* find(int key) {                           //O(n)

		if (!this->tail)
			return nullptr;

		if (this->tail->getKey() == key)
			return this->tail;

		Node<T>* temp = this->head;

		while (temp->getNext()) {
			if (temp->getKey() == key)
				return temp;
		}

		return nullptr;

	}

	//Returns the key of the first item. If the list is empty, return -1
	int returnFirstKey() {                               //O(1)

		return this->head ? this->head->getKey() : -1;

	}
	
};