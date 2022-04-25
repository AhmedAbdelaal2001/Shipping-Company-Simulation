#pragma once
#include "Cargo.h"
#include "ArrayList.h"

class Truck
{
private:
	char type;
	int id;
	int capacity;
	Time checkupTime;
	int speed;
	Time deliveryInterval;
	ArrayList<Cargo*> cargoList;
	int deliveredCargos;
	int deliveryJourneys;
	int priority;
	Time activeTime;
	static int currID;

public:
	Truck(char type, int capacity, Time checkupTime, int speed/*, Time deliveryInterval, int deliveredCargos, int deliveryJourneys, Time activeTime*/);

	
	void setType(char type);
	char getType();

	void setCapacity(int capacity);
	int getCapacity();

	void setID(int id);
	int getID() const;
	
	void setSpeed(int speed);
	int getSpeed();

	void setCheckupTime(Time checkupTime);
	Time getCheckupTime();
	
	void setDeliveryInterval(Time deliveryInterval);
	Time getDeliveryInterval();
	
	void setDeliveredCargos(int deliveredCargos);
	int getDeliveredCargos();
	
	void setDeliveredJourneys(int deliveryJourneys);
	int getDeliveredJourneys();
	
	void setPriority(int priority);
	int getPriority() const ;
	void setActiveTime(Time activeTime);
	Time getActiveTime();

	void saveToFile(ofstream out);

	friend ostream& operator << (ostream& out, Truck* truckPtr);

	bool operator > (Truck* truckPtr);



};

