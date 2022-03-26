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
			resize(2 * maxCount); 
		
		arr[count] = new T;
		*arr[count++] = item;
	}

	bool deleteEnd() {                                         //O(1) amortized
		
		if (count == 0)
			return false;

		delete arr[count-- - 1];
		
		if (count > initialMaxCount && count < maxCount / 4) //If the array becomes too small compared to maxSize, it will be resized to
			resize(maxCount / 2);                            //maxCount/2, given that it has already been resized before.
			                                                 
		
		return true;
	}

	void PrintList() {                                         //O(1)
		
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
