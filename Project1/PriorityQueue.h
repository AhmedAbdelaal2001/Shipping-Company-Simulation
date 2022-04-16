#pragma once
#include "QueueInterface.h"
#include "ArrayList.h"

template <class T>
class PriorityQueue :public QueueInterface<T> {
private:
	ArrayList<T> list; //List of pointers to the stored elements.

	//Returns the index position of the parent of an element at a given index position.
	int parent(int index) {                                       //O(1)
		int parent = (index - 1) / 2;
		return (index < 0) ? index : parent;
	}

	//Returns the index position of the left child of an element at a given index position.
	int leftChild(int index) {                                     //O(1)
		int leftChild = 2 * index + 1;
		return (leftChild >= list.getCount()) ? index : leftChild;
	}

	//Returns the index position of the right child of an element at a given index position.
	int rightChild(int index) {
		int rightChild = 2 * index + 2;
		return (rightChild >= list.getCount()) ? index : rightChild;    //O(1)
	}

	//This function is for maintaining the heap property after insertion.
	void heapifyUp(int index) {                                         //O(logn)
		
		int parentIndex = parent(index);
		if (*list[index] > *list[parentIndex]) {
			list.swap(index, parentIndex);
			heapifyUp(parentIndex);
		}
	}

	//This function is for maintaining the heap property after deletion.
	void heapifyDown(int index) {                                       //O(logn)

		if (!list[index])
			return;
		
		int rch = rightChild(index);
		int lch = leftChild(index);
		int biggerChild = list.max(rch, lch);

		if (*list[index] < *list[biggerChild]) {
			list.swap(index, biggerChild);
			heapifyDown(biggerChild);
		}
	}

public:

	//Constructor
	PriorityQueue(int maxSize = 10) : list(maxSize){};

	bool isEmpty() { return list.isEmpty(); }


	void enqueue(T item) {                                //O(logn)
		list.insertEnd(item);
		heapifyUp(list.getCount() - 1);
	}

	bool dequeue(T& item) {                                       //O(logn)

		list.swap(list.getCount() - 1, 0);
		T itemPtr = nullptr;
		bool check = list.deleteEnd(itemPtr);
		heapifyDown(0);

		item = itemPtr;
		return check;

	}

	T peek() {                                          //O(1)
		return list[0];
	}

	//Prints the stored content.
	void printQueue() {                                      //O(n)
		list.printList();
	}
};

void PriorityQueueTest() {

	int choice = 0, inputNum1 = 0, inputNum2 = 0, queueSize = 0;
	int* ellymzbtna = nullptr;
	bool check = true;
	char decision;

	cout << "Enter the size of the priority queue you wish to create: ";
	cin >> queueSize;
	cout << "Creating List: " << endl;
	PriorityQueue<int*> heap(queueSize);
	cout << "Priority Queue Created!" << endl;

	while (check) {

		cout << "**********************************************************************************" << endl;
		cout << "1. Enqueue:" << endl;
		cout << "2. Dequeue:" << endl;
		cout << "3. Peek: " << endl;
		cout << "4. Print Queue: " << endl;
		cin >> choice;

		switch (choice) {

		case 1:
			cout << "Input the number you wish to insert: ";
			cin >> inputNum1;
			ellymzbtna = new int(inputNum1);
			heap.enqueue(ellymzbtna);
			cout << "Element Inserted." << endl;
			break;

		case 2:
			cout << "Deleting the last element: " << endl;
			check = heap.dequeue(ellymzbtna);

			if (ellymzbtna)
			{
				cout << "Last element deleted." << endl;
				cout << "Deleted Element: " << *ellymzbtna << endl;
			}
			else
				cout << "List already empty." << endl;
			
			break;

		case 3:
			cout << "PeEkInG..." << endl;
			ellymzbtna = heap.peek();
			if (ellymzbtna)
				cout << *heap.peek() << endl;
			else
				cout << "m3rftsh" << endl;
			
			break;

		case 4:
			cout << "Printing Queue..." << endl;
			heap.printQueue();
			
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
