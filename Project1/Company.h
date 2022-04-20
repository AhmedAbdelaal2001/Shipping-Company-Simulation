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
	int n_Count;
	int s_Count;
	int v_Count;

	int nc_Count;
	int sc_Count;
	int vc_Count;

	int cAutoP;
	
	int n_Speed;
	int s_Speed;
	int v_Speed;

	int n_Capacity;
	int s_Capacity;
	int v_Capacity;

	int journeysBeforeCheckup;

	Time n_CheckupD;
	Time s_CheckupD;
	Time v_CheckupD;

	Time autoP;
	Time maxW;

	int eventsCount;


	CrossLinkedList<Cargo*>* waitingNormalCargo;
	Queue<Cargo*>* waitingSpecialCargo;
	PriorityQueue<Cargo*>* waitingVIPCargo;

	Queue<Event*>* EventList;

	Queue<Cargo*>* normalDeliveredCargo;
	Queue<Cargo*>* specialDeliveredCargo;
	Queue<Cargo*>* VIPDeliveredCargo;

	string outFileName;

	string mode;

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

	void saveToFile();

	void Simulate();
	bool notTerminated();

	void print(Time currTime);

	void printAll(Time currTime);
	
};

