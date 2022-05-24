#pragma once

template <class T>
class Container {

public:
	virtual int getCount() const = 0;
	virtual bool dequeue(T& item) = 0;
	virtual bool peek(T& item) = 0;
	virtual void print() = 0;
	virtual bool isEmpty() = 0;
};