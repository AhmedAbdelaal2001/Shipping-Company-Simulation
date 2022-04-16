#pragma once
#include "MapInterface.h"
#include "HLinkedList.h"

template <class T>
class HashMap : public MapInterface<T> {

private:
	HLinkedList<T>* arr;
	int count;
	int a;                      
	int b;                      // a and b are integers that will correspond to a specific hash function from the universal hash family.
	int p;                     // a large prime number, which limits the possible values of a and b.
	int maxSize;
	int initialMaxSize;


	//Randomly chooses values for a and b.
	void computeParameters() {                             //O(1)
		srand(time(0));
		a = rand() % (p - 1);
		b = rand() % (p - 1);
	}

	//Computes the hash of a given key.
	int hash(int key)                                    //O(1)
	{
		return ((a * key + b) % p) % maxSize;
	}

	//Rehashes the entire hashMap, used when the number of elements reaches a level that increases the probability of collisions.
	void rehash(int newSize) {                         //O(n)
		int oldSize = maxSize;
		maxSize = newSize;
		computeParameters();
		int key = 0, index = 0;
		HLinkedList<T>* newArr = new HLinkedList<T>[newSize];
		
		for (int i = 0; i < oldSize; i++) {
			while (true) {
				
				key = arr[i].returnFirstKey();
				T firstItemPtr = arr[i].deleteFirst();
				
				if (firstItemPtr) {
					index = hash(key);
					newArr[index].insertEnd(firstItemPtr, key);
					continue;
				
				}

				break;
			}
		}

		delete[] arr;
		arr = newArr;
		
	}

public:

	HashMap(int maxSize) {
		
		count = 0;
		this->maxSize = maxSize;
		initialMaxSize = maxSize;
		arr = new HLinkedList<T>[maxSize];
		
		p = 1009;
		computeParameters();
	}

	T findItem(int key) {                              //O(1)
		
		int index = hash(key);
		Node<T>* temp = arr[index].find(key);
		if (temp)
			return temp->getItemPtr();
		return nullptr;
		
	}

	void insertItem(int key, T itemPtr) {                //O(1) amortized
		
		if (count >= 0.75 * maxSize)
			rehash(2 * maxSize);

		int index = hash(key);
		arr[index].insertEnd(itemPtr, key);
		count++;
	}

	T removeItem(int key) {                              //O(1) amortized
		
		if (maxSize > initialMaxSize && count <= 0.25 * maxSize)
			rehash(maxSize / 2);

		int index = hash(key);
		Node<T>* nodePtr = arr[index].find(key);
		count--;


		return arr[index].deleteNode(nodePtr);
	}

	void printMap() {                               //O(n)

		for (int i = 0; i < maxSize; i++) {
			cout << "Index = " << i << endl;
			arr[i].printList();
			cout << endl;
		}
		cout << endl;
	}

	~HashMap() {
		delete[] arr;
	}
};

void HashMapTest() {
	int choice = 0, inputNum1 = 0, inputNum2 = 0, size = 0;
	int* inputNum1Ptr = nullptr;
	bool check = true;
	char decision;

	cout << "Enter the size of the hash table you wish to create: ";
	cin >> size;
	cout << "Creating List: " << endl;
	HashMap<int*> hashMap(size);
	cout << "Hash Table Created!" << endl;

	while (check) {

		cout << "**********************************************************************************" << endl;
		cout << "1. Insert:" << endl;
		cout << "2. Delete:" << endl;
		cout << "3. Find: " << endl;
		cout << "4. Print: " << endl;
		cin >> choice;

		switch (choice) {

		case 1:
			cout << "Input the number you wish to insert: ";
			cin >> inputNum1;
			inputNum1Ptr = new int(inputNum1);
			hashMap.insertItem(inputNum1, inputNum1Ptr);
			cout << "Element Inserted." << endl;
			break;

		case 2:
			cout << "Enter the element you wish to delete: " << endl;
			cin >> inputNum1;
			inputNum1Ptr = hashMap.removeItem(inputNum1);

			if (inputNum1Ptr)
			{
				cout << "Element deleted." << endl;
				cout << "Deleted Element: " << *inputNum1Ptr << endl;
			}
			else
				cout << "Element not in the list." << endl;

			break;

		case 3:
			cout << "Enter the key you wish to search for" << endl;
			cin >> inputNum1;
			inputNum1Ptr = hashMap.findItem(inputNum1);
			if (inputNum1Ptr)
				cout << "Element Found." << endl;
			else
				cout << "Element Not Found." << endl;

			break;

		case 4:
			cout << "Printing Hash Table..." << endl;
			hashMap.printMap();

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
