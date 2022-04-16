#pragma once

//A Priority Queue (PQ) Interface. 
template <class T>
class QueueInterface {

public:
	
	//Adds an item to the PQ.
	virtual void enqueue(T item) = 0;
	
	//Removes the item of maximum priority from the PQ.
	virtual bool dequeue(T& item) = 0;

	//Returns the item of maximum priority, without affecting the PQ. 
	virtual T peek() = 0;

	//Prints the PQ.
	virtual void printQueue() = 0;
};
