#pragma once
#include "UI.h"
#include "CrossLinkedList.h"
#include"Queue.h"
#include "PriorityQueue.h"
#include "Event.h"
#include "MaintenanceTrucks.h"

#include "Truck.h"

class Event;
class UI;

class Company
{
private:

	bool isLoadingVIP, isLoadingSpecial, isLoadingNormal;

	Time autoP;
	Time maxW;

	int autoPromoted, failedTrucks;

	CrossLinkedList<Cargo*>* waitingNormalCargo;
	Queue<Cargo*>* waitingSpecialCargo;
	PriorityQueue<Cargo*>* waitingVIPCargo;

	PriorityQueue<Truck*>* waitingNormalTrucks;
	PriorityQueue<Truck*>* waitingSpecialTrucks;
	PriorityQueue<Truck*>* waitingVIPTrucks;

	PriorityQueue<Truck*>* normalNightTrucks;
	PriorityQueue<Truck*>* specialNightTrucks;
	PriorityQueue<Truck*>* VIPNightTrucks;

	PriorityQueue<Truck*>* movingTrucks;
	
	Queue<Event*>* EventList;

	PriorityQueue<Truck*>* LoadingTrucks;
	
	Queue<Cargo*>* normalDeliveredCargo;
	Queue<Cargo*>* specialDeliveredCargo;
	Queue<Cargo*>* VIPDeliveredCargo;

	Queue<Truck*>* normalCheckupTrucks;
	Queue<Truck*>* specialCheckupTrucks;
	Queue<Truck*>* VIPCheckupTrucks;

	MaintenanceTrucks* VIPMaintenance;
	MaintenanceTrucks* specialMaintenance;
	MaintenanceTrucks* normalMaintenance;

	MaintenanceTrucks* nightVIPMaintenance;
	MaintenanceTrucks* nightSpecialMaintenance;
	MaintenanceTrucks* nightNormalMaintenance;

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

	Cargo* firstDelivered(Cargo* nCargo, Cargo* sCargo, Cargo* vCargo);

	void readFromFile();
	void saveToFile(Time);

	void executeCurrEvents(Time currTime);

	bool notEndOfSimulation();
	bool inWorkingHours(Time currTime);

	void moveTruckToLoading(Container<Truck*>*, Truck*);
	void loadCargo(Container<Cargo*>*, Truck*, Time);
	void moveCargoToDelivered(Cargo*);

	void fillTruckWithCargo(Truck*, Container<Truck*>*, Container<Cargo*>*, Time);
	void moveTruckToWaiting(Truck*);
	void moveToCheckup(Truck*, Time);
	void moveToMaintenance(Truck*, Time);
	void returnFromMaintenance(Time);
	void returnFromCheckup(Time);


	bool assignCargo(Container<Cargo*>*, Container<Truck*>**, int, Time);
	void assignMaxWCargo(Container<Cargo*>*, Truck*&, Container<Truck*>*, Time);

	void assignVIP(Time currTime, Container<Cargo*>*);
	void assignSpecial(Time currTime, Container<Cargo*>*);
	void assignNormal(Time currTime, Container<Cargo*>*);

	void autoPromote(Time currTime);

	void startDelivery(Time currTime);
	void completeDelivery(Time currTime);


	void printAll(Time currTime);

	void Simulate();


	~Company();
};

