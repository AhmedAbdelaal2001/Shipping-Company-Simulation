#pragma once

template<class T>
class MapInterface {

	//Find the item corresponding to a given key.
	virtual T* findItem(int key) = 0;

	//Inserts a key-item pair.
	virtual void insertItem(int key, T* itemPtr) = 0;

	//Removes a key-item pair given a key.
	virtual T* removeItem(int key) = 0;

	//Prints the stored elements.
	virtual void printMap() = 0;
};
