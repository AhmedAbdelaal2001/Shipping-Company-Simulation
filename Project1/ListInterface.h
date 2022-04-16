#pragma once


//An Ordered List Interface.
template <class T>
class ListInterface {
public:
	
	//Checks whether the list is empty or not.
	virtual bool isEmpty() = 0;

	//Inserts a new element at the end of the list.
	virtual void insertEnd(T item) = 0;

	//deletes the last element in the list.
	virtual bool deleteEnd(T& item) = 0;

	//Prints all the elements.
	virtual void printList() = 0;
};