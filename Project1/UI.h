#pragma once

#include <iostream>
#include "CrossLinkedList.h"
#include "Queue.h"
#include "PriorityQueue.h"
#include "Time.h"
#include "Event.h"
#include "Company.h"
#include "Truck.h"
#include "MaintenanceTrucks.h"
#include "Container.h"
#include <string>

using namespace std;

class Company;
class Event;

class UI
{

private:

	Company* pCompany;
	string mode;

public:
	UI(Company* pCompany);

	void getModefromUser();

	string getMode() const;

	string getFileName();		

	void printMessage(string message);

	template <class T>
	void printContainer(Container<T>*, Container<T>*, char);

	template <class T>
	void printContainerBatch(string, Container<T>**, int, int);
	
	// prints all the companies data (waiting lists, loading lists, moving lists... etc.)
	void print(Time currTime, Queue<Event*>* EventList, Container<Cargo*>** cargoContainersArr, Container<Truck*>** truckContainersArr);

};

template<class T>
inline void UI::printContainer(Container<T>* container1, Container<T>* container2, char type)
{
	switch (type)
	{
	case 'N':
		cout << '[';
		break;

	case 'S':
		cout << '(';
		break;
		
	case 'V':
		cout << '{';
		break;
	}

	container1->print(); 
	if (container2 && !container1->isEmpty() && !container2->isEmpty()) cout << ',';
	if (container2) container2->print();

	switch (type)
	{
	case 'N':
		cout << "] ";
		break;

	case 'S':
		cout << ") ";
		break;

	case 'V':
		cout << "} ";
		break;
	}
}

template<class T>
inline void UI::printContainerBatch(string label, Container<T>** containersArr, int index, int size)
{

	if (size == 1) {
		cout << containersArr[index]->getCount() << " " << label;
		containersArr[index]->print();
		cout << endl << "-------------------------------------------------------------------------------------------------------" << endl;
		return;
	}

	int numOfObjects = 0;
	int increment = (size == 3) ? 1 : 2;
	char type = 'N';
	Container<T>* container2;

	for (int i = index; i < index + size; i++)
	{
		numOfObjects += containersArr[i]->getCount();
	}

	cout << numOfObjects << " " << label;

	for (int i = index; i < index + size; i += increment) {

		container2 = (size == 3) ? nullptr : containersArr[i + 1];
		printContainer(containersArr[i], container2, type);

		if (i == index) type = 'S';
		else type = 'V';

	}

	cout << endl << "-------------------------------------------------------------------------------------------------------" << endl;
}
