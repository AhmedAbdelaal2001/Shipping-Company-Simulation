#pragma once
#include "HashMap.h"

//A custom data structure consisting of a linked list and a HashMap crosslinked together.
template <class T>
class CrossLinkedList {

private:
	LinkedList<T> list;
	HashMap<Node<T>*> hashMap;

public:
	CrossLinkedList(int maxSize) : hashMap(maxSize) { }

	void insertLast(T itemPtr, int key) {           //O(1) amortized
		list.insertEnd(itemPtr);
		Node<T>* tail = list.peekLast();
		hashMap.insertItem(key, tail);
	}

	T deleteFirst() {                                //O(1) amortized
		T delPtr = list.deleteFirst();
		if (!delPtr)
			return nullptr;

		int key = *delPtr;
		hashMap.removeItem(key);

		return delPtr;
	}

	T deleteElement(int key) {                        //O(1) amortized
		Node<T>* delPtr = hashMap.removeItem(key);
		
		return list.deleteNode(delPtr);

	}

	void printList() {                                 //O(n)
		list.printList();
		cout << endl;
		hashMap.printMap();
	}
};

void CrossLinkedListTest() {
	int choice = 0, inputNum1 = 0, inputNum2 = 0, size = 0;
	int* inputNum1Ptr = nullptr;
	bool check = true;
	char decision;

	cout << "Enter the size of the list you wish to create: ";
	cin >> size;
	cout << "Creating List: " << endl;
	CrossLinkedList<int*> list(size);
	cout << "List Created!" << endl;

	while (check) {

		cout << "**********************************************************************************" << endl;
		cout << "1. Insert:" << endl;
		cout << "2. Delete:" << endl;
		cout << "3. DeleteFirst" << endl;
		cout << "4. Print: " << endl;
		cin >> choice;

		switch (choice) {

		case 1:
			cout << "Input the number you wish to insert: ";
			cin >> inputNum1;
			inputNum1Ptr = new int(inputNum1);
			list.insertLast(inputNum1Ptr, inputNum1);
			cout << "Element Inserted." << endl;
			break;

		case 2:
			cout << "Enter the element you wish to delete: " << endl;
			cin >> inputNum1;
			inputNum1Ptr = list.deleteElement(inputNum1);

			if (inputNum1Ptr)
			{
				cout << "Element deleted." << endl;
				cout << "Deleted Element: " << *inputNum1Ptr << endl;
			}
			else
				cout << "Element not in the list." << endl;

			break;

		case 3:
			inputNum1Ptr = list.deleteFirst();
			if (inputNum1Ptr) {
				cout << "Element deleted." << endl;
				cout << "Deleted Element: " << *inputNum1Ptr << endl;
			} else
				cout << "List Empty." << endl;
			
			break;

		case 4:
			cout << "Printing List..." << endl;
			list.printList();

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