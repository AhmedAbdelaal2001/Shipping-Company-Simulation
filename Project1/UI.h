#pragma once

#include <iostream>
#include "CrossLinkedList.h"
#include"Queue.h"
#include "PriorityQueue.h"
#include "Time.h"
#include "Event.h"
#include "Company.h"
#include "Truck.h"

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
	
	// prints all the companies data (waiting lists, loading lists, moving lists... etc.)
	void print(Time currTime, PriorityQueue<Truck*>* waitingNormalTrucks, PriorityQueue<Truck*>* normalNightTrucks,  PriorityQueue<Truck*>* waitingSpecialTrucks, PriorityQueue<Truck*>* specialNightTrucks, PriorityQueue<Truck*>* waitingVIPTrucks, PriorityQueue<Truck*>* VIPNightTrucks, Queue<Truck*>* normalCheckupTrucks, Queue<Truck*>* specialCheckupTrucks, Queue<Truck*>* VIPCheckupTrucks, PriorityQueue<Truck*>* movingTrucks, CrossLinkedList<Cargo*>* waitingNormalCargo, Queue<Cargo*>* waitingSpecialCargo, PriorityQueue<Cargo*>* waitingVIPCargo, Queue<Event*>* EventList, Queue<Cargo*>* normalDeliveredCargo, Queue<Cargo*>* specialDeliveredCargo, Queue<Cargo*>* VIPDeliveredCargo, PriorityQueue<Truck*>* LoadingTrucks);



};

