#pragma once
#include "PQueueInterface.h"
#include "ArrayList.h"

template <class T>
class BinaryHeap :public PQueueInterface<T> {
private:
	ArrayList<T> list;

	int parent(int index) {
		int parent = (index - 1) / 2;
		return (index < 0) ? index : parent;
	}

	int leftChild(int index) {
		int leftChild = 2 * index + 1;
		return (leftChild >= list.getCount()) ? index : leftChild;
	}

	int rightChild(int index) {
		int rightChild = 2 * index + 2;
		return (rightChild >= list.getCount()) ? index : rightChild;
	}

	void heapifyUp(int index) {
		
		int parentIndex = parent(index);
		if (*list[index] > *list[parentIndex]) {
			list.swap(index, parentIndex);
			heapifyUp(parentIndex);
		}
	}
	void heapifyDown(int index) {
		
		int rch = rightChild(index);
		int lch = leftChild(index);
		int biggerChild = list.max(rch, lch);

		if (*list[index] < *list[biggerChild]) {
			list.swap(index, biggerChild);
			heapifyDown(biggerChild);
		}
	}

public:
	BinaryHeap(int maxSize = 10) : list(maxSize){};

	void enqueue(T item) {
		list.insertEnd(item);
		heapifyUp(list.getCount() - 1);
	}

	T* dequeue() {

		if (list.isEmpty())
			return nullptr;

		list.swap(list.getCount() - 1, 0);

		T* itemPtr = list.deleteEnd();

		if (!list.isEmpty())
			heapifyDown(0);

		return itemPtr;
		
		/*if (list.swap(list.getCount() - 1, 0)) {
			dequeued = list.deleteEnd();
			heapifyDown(0);
		}
		else {
			dequeued = list.deleteEnd();
		}*/

	}

	T* peek() {
		if (list.isEmpty())
			return nullptr;

		return list[0];
	}

	void printQueue() {
		list.PrintList();
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
	BinaryHeap<int> heap(queueSize);
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
			heap.enqueue(inputNum1);
			cout << "Element Inserted." << endl;
			break;

		case 2:
			cout << "Deleting the last element: " << endl;
			ellymzbtna = heap.dequeue();

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
				cout << heap.peek() << endl;
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
