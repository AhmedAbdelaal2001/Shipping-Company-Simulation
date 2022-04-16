#include "Company.h"

Company::Company(int normalTruckCapacity, int VIPTruckCapacity) {
	
	waitingNormalCargo = new CrossLinkedList<Cargo*>(2 * normalTruckCapacity);
	waitingSpecialCargo = new Queue<Cargo*>;
	waitingVIPCargo = new PriorityQueue<Cargo*>(2 * VIPTruckCapacity);
}

CrossLinkedList<Cargo*>* Company::getWaitingNormalCargo() const {
	return waitingNormalCargo;
}

Queue<Cargo*>* Company::getWaitingSpecialCargo() const {
	return waitingSpecialCargo;
}

PriorityQueue<Cargo*>* Company::getWaitingVIPCargo() const {
	return waitingVIPCargo;
}
