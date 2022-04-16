#pragma once
#include "CrossLinkedList.h"
#include"Queue.h"
#include "PriorityQueue.h"
#include "Cargo.h"
#include "Truck.h"

class Company
{
private:
	CrossLinkedList<Cargo*>* waitingNormalCargo;
	Queue<Cargo*>* waitingSpecialCargo;
	PriorityQueue<Cargo*>* waitingVIPCargo;

public:
	Company(int normalTruckCapacity, int VIPTruckCapacity);

	CrossLinkedList<Cargo*>* getWaitingNormalCargo() const;
	Queue<Cargo*>* getWaitingSpecialCargo() const;
	PriorityQueue<Cargo*>* getWaitingVIPCargo() const;

	void save();
	void load();
};

