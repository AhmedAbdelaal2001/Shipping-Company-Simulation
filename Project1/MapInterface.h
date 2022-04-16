#pragma once

template<class T>
class MapInterface {

	//Find the item corresponding to a given key.
	virtual bool findItem(int key, T& item) = 0;

	//Inserts a key-item pair.
	virtual void insertItem(int key, T item) = 0;

	//Removes a key-item pair given a key.
	virtual bool removeItem(int key, T& item) = 0;

	////Prints the stored elements.
	//virtual void printMap() = 0;
};
