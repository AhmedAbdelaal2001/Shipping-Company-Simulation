#pragma once


//An Ordered List Interface.
template <class T>
class ListInterface {
public:
	
	//Swaps the elements at index positions i and j.
	virtual bool swap(int i, int j) = 0;

	//Inserts a new element at the end of the list.
	virtual void insertEnd(T item) = 0;

	//deletes the last element in the list.
	virtual T* deleteEnd() = 0;

	//Prints all the elements.
	virtual void PrintList() = 0;
};