#pragma once
#include "ListInterface.h"
#include <iostream>
using namespace std;

template <class T>
class ArrayList : public ListInterface<T> {

private:
	T** arr; //An array of pointers
	int count; //The number of elements in the array
	int maxCount; //The maximum number of elements that can currently be stored in the array
	int initialMaxCount; //The initial maxCount, before any resizing takes place

	//This function resizes the list from size maxCount to newSize
	void resize(int newSize) {                                    //O(n)
		cout << "Resizing..." << endl;
		T** newArr = new T * [newSize];
		
		for (int i = 0; i < count; i++)
			newArr[i] = arr[i];

		delete[] arr;
		arr = newArr;
		maxCount = newSize;
		
		for (int i = count; i < maxCount; i++)
			arr[i] = nullptr;
	}

public:

	//Constructor
	ArrayList(int maxCount = 10) {                              //O(n)
		arr = new T * [maxCount];
		
		for (int i = 0; i < maxCount; i++)
			arr[i] = nullptr;

		count = 0;
		this->maxCount = this->initialMaxCount = maxCount;
	}

	bool swap(int i, int j) {                                //O(1)
		
		if (i >= count || j >= count || i<0 || j<0)
			return false;

		T* temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
		return true;
	}

	void insertEnd(T item) {                                  //O(1) amortized
		
		if (count == maxCount) //If the array grows to size = maxCount, it will be resized to 2*maxSize
			resize(2 * maxCount); //O(n) 
		
		arr[count] = new T;
		*arr[count++] = item;
	}

	bool deleteEnd() {                                         //O(1) amortized
		
		if (count == 0)
			return false;

		delete arr[count - 1];
		arr[count-- - 1] = nullptr;
		
		if (maxCount > initialMaxCount && count < maxCount / 4) //If the array becomes too small compared to maxSize, it will be resized to
			resize(maxCount / 2); //O(n)                        //maxCount/2, given that it has already been resized before.
			                                                 
		
		return true;
	}

	void PrintList() {                                         //O(n)
		
		for (int i = 0; i < count; i++)
			cout << *arr[i] << " ";

		cout << endl;
	}

	//Destructor, deallocates any dynamically allocated memory.
	~ArrayList() {                                            //O(n)
		cout << "Destroying List..." << endl;

		for (int i = 0; i < count; i++)
			delete arr[i];

	}
};

//This function is for testing the ArrayList class. All of the available methods (swap, insertEnd, deleteEnd, printList)
//can be independently executed and tested through this function.
void ArrayListTest() {

	int choice = 0, inputNum1 = 0, inputNum2 = 0, arrSize = 0;
	bool check = true;
	char decision;

	cout << "Enter the size of the list you wish to create: ";
	cin >> arrSize;
	cout << "Creating List: " << endl;
	ArrayList<int> list(arrSize);
	cout << "List Created!" << endl;

	while (check) {

		cout << "**********************************************************************************" << endl;
		cout << "1. Insert at the end:" << endl;
		cout << "2. Delete From the end:" << endl;
		cout << "3. Swap 2 elements: " << endl;
		cout << "4. Print the List: " << endl;
		cin >> choice;

		switch (choice) {

		case 1:
			cout << "Input the number you wish to insert: ";
			cin >> inputNum1;
			list.insertEnd(inputNum1);
			cout << "Element Inserted." << endl;
			break;

		case 2:
			cout << "Deleting the last element: " << endl;
			check = list.deleteEnd();

			if (check)
				cout << "Last element deleted." << endl;
			else
				cout << "List already empty." << endl;

			break;

		case 3:
			cout << "Enter the index of the first number: ";
			cin >> inputNum1;
			cout << "Enter the index of the second number: ";
			cin >> inputNum2;
			check = list.swap(inputNum1, inputNum2);

			if (check)
				cout << "Items swapped" << endl;
			else
				cout << "Items could not be swapped" << endl;

			break;

		case 4:
			cout << "Printing the list: " << endl;
			list.PrintList();
			cout << "List Printed." << endl;
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
