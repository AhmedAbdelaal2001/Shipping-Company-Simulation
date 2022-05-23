#pragma once
#include "PriorityQueue.h"
#include "Truck.h"

class MaintenanceTrucks: public PriorityQueue<Truck*> {

public:
	bool dequeue(Truck*);

};

