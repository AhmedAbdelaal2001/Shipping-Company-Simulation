#pragma once

#include "QueueInterface.h"
#include "LinkedList.h"

template <class T>
class Queue : public QueueInterface<T> {

private:
	
	LinkedList<T> list;

public:
	

	bool isEmpty() { return list.isEmpty(); }

	void enqueue(T item) { list.insertEnd(item); }

	bool dequeue(T& item) { return list.deleteFirst(item); }

	bool peek(T& item) { return list.peekFirst(item); }

	void printQueue() { list.printList(); }
};

//void QueueTest() {
//
//	int choice = 0, inputNum1 = 0, inputNum2 = 0;
//	int* inputNum1Ptr = nullptr;
//	Node<int*>* nodePtr = nullptr;
//	bool check = true;
//	char decision;
//
//	cout << "Creating List: " << endl;
//	Queue<int*> queue;
//	cout << "List Created!" << endl;
//
//	while (check) {
//
//		cout << "**********************************************************************************" << endl;
//		cout << "1. Enqueue:" << endl;
//		cout << "2. Dequeue:" << endl;
//		cout << "3. Peek: " << endl;
//		cout << "4. Print the List: " << endl;
//		cin >> choice;
//
//		switch (choice) {
//
//		case 1:
//			cout << "Input the number you wish to enqueue: ";
//			cin >> inputNum1;
//			inputNum1Ptr = new int(inputNum1);
//			queue.enqueue(inputNum1Ptr);
//			cout << "Element Inserted." << endl;
//			break;
//
//		case 2:
//			cout << "Deleting the first element: " << endl;
//
//
//			if (queue.dequeue(inputNum1Ptr))
//				cout << "Last element deleted." << endl << "Deleted Element: " << *inputNum1Ptr << endl;
//			else
//				cout << "List already empty." << endl;
//
//			break;
//
//		case 3:
//			inputNum1Ptr = queue.peek();
//			cout << "First Item is: " << *inputNum1Ptr << endl;
//			
//			break;
//
//		case 4:
//			cout << "Printing the queue: " << endl;
//			queue.printQueue();
//			cout << endl << "List Printed." << endl;
//			break;
//
//		default:
//			cout << "Unrecognized input." << endl;
//		}
//
//		cout << "Do you wish to continue? (y/n)";
//		cin >> decision;
//		if (decision == 'y')
//			check = true;
//		else
//			check = false;
//	}
//}
