#pragma once
#include "Cargo.h"
#include "ArrayList.h"
#include "PriorityQueue.h"

class Truck
{
private:
	char type;
	int id;
	int capacity;
	int speed;
	int movedDistance;
	Time checkupTime;
	Time deliveryInterval;
	Time activeTime;
	Time moveTime;
	PriorityQueue<Cargo*>* cargoList;
	int deliveredCargos;
	int deliveryJourneys;
	int priority;
	static int currID;

public:
	Truck(char type, int capacity, Time checkupTime, int speed/*, Time deliveryInterval, int deliveredCargos, int deliveryJourneys, Time activeTime*/);

	bool isFull();
	bool isEmpty();

	void setType(char type);
	char getType();

	Time getMoveTime();

	void setCapacity(int capacity);
	int getCapacity();

	void setID(int id);
	int getID() const;

	void setSpeed(int speed);
	int getSpeed();

	void setMovedDistance(int movedDistance);
	int getMovedDistance() const;

	void setCheckupTime(Time checkupTime);
	Time getCheckupTime();

	// for phase 2
	/*void setDeliveryInterval(Time deliveryInterval);
	Time getDeliveryInterval();

	void setDeliveredCargos(int deliveredCargos);
	int getDeliveredCargos();

	void setDeliveredJourneys(int deliveryJourneys);
	int getDeliveredJourneys();*/

	void setPriority(int priority);   // when trucks move from waiting to loading or loading to moving priority is recalculated and set
	int getPriority() const;
	void updatePriority(int extraPriority);

	void setActiveTime(Time activeTime);  // sets Active time after calculation
	Time getActiveTime();

	int calcMovingPriority(Time);

	void enqueueCargo(Cargo* loading);

	void saveToFile(ofstream out);   // Writes to output file

	friend ostream& operator << (ostream& out, Truck* truckPtr);

	bool operator > (Truck* truckPtr);  // for comparing truck priorities

	~Truck();
};

