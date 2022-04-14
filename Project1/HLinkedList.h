#pragma once
#include "LinkedList.h"
#include "HNode.h"

template <class T>
class HLinkedList : public LinkedList<T> {

public:
	
	void insertEnd(T* newItem, int key = -1) {
		HNode<T>* temp = new HNode<T>(key, newItem);

		if (!this->tail) {
			this->head = this->tail = temp;
			return;
		}

		temp->setPrev(this->tail);
		this->tail->setNext(temp);
		this->tail = temp;
	}

	Node<T>* find(int key) {

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

	int returnFirstKey() {

		return this->head ? this->head->getKey() : -1;

	}
};