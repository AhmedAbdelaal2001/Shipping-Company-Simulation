#pragma once

template<class T>
class MapInterface {

	virtual T* findItem(int key) = 0;

	virtual void insertItem(int key, T* itemPtr) = 0;

	virtual T* removeItem(int key) = 0;

	virtual void printMap() = 0;
};
