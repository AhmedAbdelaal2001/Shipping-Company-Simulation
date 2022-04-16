#pragma once
#include "ListInterface.h"
#include "Node.h"

template <class T>
class LinkedList{

protected:
	
	Node<T>* head;
	Node<T>* tail;
	int itemsCount;

public:

	LinkedList() {                                         //O(1)
		head = nullptr;
		tail = nullptr;
		itemsCount = 0;
	}

	Node<T>* peekLast() { return tail; }                   //O(1)
	Node<T>* peekFirst() { return head; }                  //O(1)

	bool isEmpty() {                                       //O(1)
		if (head)
			return false;
		return true;
	}

	virtual void insertEnd(T newItem, int key = -1) {     //O(1)
		itemsCount++;
		Node<T>* newNode = new Node<T>(newItem);
		
		if (!head) {
			head = tail = newNode;
			return;
		}

		newNode->setPrev(tail);
		tail->setNext(newNode);
		tail = newNode;
	}

	bool deleteFirst(T& deletedItem) {                                    //O(1)
		if (isEmpty())
			return false;

		itemsCount--;
		Node<T>* temp = head;
		deletedItem = head->getItem();
		head = temp->getNext();
		
		if (head)
			head->setPrev(nullptr);
		else
			tail = nullptr;
		
		delete temp;
		
		return true;
	}

	bool deleteLast(T& deletedItem) {                                    //O(1)
		if (isEmpty())
			return false;

		itemsCount--;
		Node<T>* temp = tail;
		deletedItem = tail->getItem();
		tail = temp->getPrev();
		
		if (tail)
			tail->setNext(nullptr);
		else
			head = nullptr;

		delete temp;
		return true;
	}

	bool deleteNode(Node<T>* nodePtr, T& deletedItem) {                     //O(1)

		if (!nodePtr)
			return false;

		if (!(nodePtr->getPrev())) {
			return deleteFirst(deletedItem);
		}
		else if (!(nodePtr->getNext())) {
			return deleteLast(deletedItem);
		}
		else {
			itemsCount--;
			nodePtr->getPrev()->setNext(nodePtr->getNext());
			nodePtr->getNext()->setPrev(nodePtr->getPrev());
			deletedItem = nodePtr->getItem();
			delete nodePtr;
			return true;
		}
	}

	bool Delete(T it, T& deletedItem) //for promotion
	{

		if (tail->getItem() == it)
			return deleteLast(deletedItem);

		bool flag = false;
		Node<T>* ptr = head;

		while (ptr)
		{
			
			if (ptr->getItem() == it)
			{
				flag = true;
				break;
			}
			ptr = ptr->getNext();
		
		}

		if (flag == false)
			return false;
		
		return deleteNode(ptr, deletedItem);
	}

	void printList() {                                  //O(n)
		Node<T>* temp = head;
		while (temp) {
			temp->printNode();
			temp = temp->getNext();
		}
	}
	 

	//To be commented out.
	virtual Node<T>* find(int index) {
		Node<T>* temp = head;
		for (int i = 0; i < index; i++) {
			if (!temp) return nullptr;
			temp = temp->getNext();
		}
		return temp;
	}

	~LinkedList() {                                 //O(n)
		Node<T>* temp = head;
		while (temp) {
			delete temp->getItem();
			temp = temp->getNext();
		}
	}
};

void LinkedListTest() {

	int choice = 0, inputNum1 = 0, inputNum2 = 0;
	int* inputNum1Ptr = nullptr;
	Node<int*>* nodePtr = nullptr;
	bool check = true;
	char decision;

	cout << "Creating List: " << endl;
	LinkedList<int*> list;
	cout << "List Created!" << endl;

	while (check) {

		cout << "**********************************************************************************" << endl;
		cout << "1. Insert at the end:" << endl;
		cout << "2. Delete From the beginning:" << endl;
		cout << "3. Delete an element: " << endl;
		cout << "4. Print the List: " << endl;
		cin >> choice;

		switch (choice) {

		case 1:
			cout << "Input the number you wish to insert: ";
			cin >> inputNum1;
			inputNum1Ptr = new int(inputNum1);
			list.insertEnd(inputNum1Ptr);
			cout << "Element Inserted." << endl;
			break;

		case 2:
			cout << "Deleting the first element: " << endl;
	

			if (list.deleteFirst(inputNum1Ptr))
				cout << "Last element deleted." << endl << "Deleted Element: " << *inputNum1Ptr << endl;
			else
				cout << "List already empty." << endl;

			break;

		case 3:
			cout << "Enter the index you wish to delete: ";
			cin >> inputNum1;
			nodePtr = list.find(inputNum1);

			if (list.deleteNode(nodePtr, inputNum1Ptr))
				cout << "Element Deleted: " << *inputNum1Ptr << endl;
			else
				cout << "Element not found" << endl;

			break;

		case 4:
			cout << "Printing the list: " << endl;
			list.printList();
			cout << endl << "List Printed." << endl;
			break;

		default:
			cout << "Unrecognized input." << endl;
		}

		cout << "Do you wish to continue? (y/n)";
		cin >> decision;
		if (decision == 'y')
			check = true;
		else
			check = false;
	}
}
