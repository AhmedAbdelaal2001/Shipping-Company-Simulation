#pragma once

template <class T>
class PQueueInterface {

public:
	
	virtual void enqueue(T item) = 0;
	
	virtual T* dequeue() = 0;

	virtual T* peek() = 0;
};
