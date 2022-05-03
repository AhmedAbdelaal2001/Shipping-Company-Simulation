#pragma once
#include "UI.h"
#include "CrossLinkedList.h"
#include"Queue.h"
#include "PriorityQueue.h"
#include "Event.h"

#include "Truck.h"

class Event;
class UI;

class Company
{
private:


	int journeysBeforeCheckup;

	Time autoP;
	Time maxW;

	PriorityQueue<Truck*>* waitingNormalTrucks;
	PriorityQueue<Truck*>* waitingSpecialTrucks;
	PriorityQueue<Truck*>* waitingVIPTrucks;

	Queue<Truck*>* normalCheckupTrucks;
	Queue<Truck*>* specialCheckupTrucks;
	Queue<Truck*>* VIPCheckupTrucks;

	PriorityQueue<Truck*>* movingTrucks;

	CrossLinkedList<Cargo*>* waitingNormalCargo;
	Queue<Cargo*>* waitingSpecialCargo;
	PriorityQueue<Cargo*>* waitingVIPCargo;

	Queue<Event*>* EventList;

	Queue<Cargo*>* normalDeliveredCargo;
	Queue<Cargo*>* specialDeliveredCargo;
	Queue<Cargo*>* VIPDeliveredCargo;

	PriorityQueue<Truck*>* LoadingTrucks;


	string outFileName;

	UI* in_out;

public:

	Company();
	/*Queue<Event*>* getEventList() const;
	CrossLinkedList<Cargo*>* getWaitingNormalCargo() const;
	Queue<Cargo*>* getWaitingSpecialCargo() const;
	PriorityQueue<Cargo*>* getWaitingVIPCargo() const;*/

	bool deleteNormalCargo(int id, Cargo*& delCargo);

	void enqueueNormal(Cargo* cargo, int id);
	void enqueueSpecial(Cargo* cargo);
	void enqueueVIP(Cargo* cargo);

	void readFromFile();
	void saveToFile();

	void executeCurrEvents(Time currTime);

	bool notTerminated();
	bool inWorkingHours(Time currTime);

	void assignVIP(Time currTime);
	void assignSpecial(Time currTime);
	void assignNormal(Time currTime);

	void autoPromote(Time currTime);

	void Simulate();

	void printAll(Time currTime);

	~Company();
};

