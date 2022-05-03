#pragma once
#include "Container.h"

//A Priority Queue (PQ) Interface. 
template <class T>
class QueueInterface : public Container<T> {

public:
	
	// Returns count of items
	virtual int getCount() const = 0;
	//Checks whether the queue is empty or not.
	virtual bool isEmpty() = 0;

	//Adds an item to the PQ.
	virtual void enqueue(T item) = 0;
	
	//Removes the item of maximum priority from the PQ.
	virtual bool dequeue(T& item) = 0;

	//Returns the item of maximum priority, without affecting the PQ. 
	virtual bool peek(T& item) = 0;

	//Prints the PQ.
	virtual void printQueue() = 0;
};
