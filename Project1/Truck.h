#pragma once
#include "Cargo.h"
#include "ArrayList.h"

class Truck
{
private:
	char type;
	int capacity;
	Time checkupTime;
	int speed;
	int deliveryInterval;
	ArrayList<Cargo*> cargoList;
	int deliveredCargos;
	int deliveryJourneys;
	Time activeTime;

public:
	Truck(char type, int capacity, Time checkupTime, int speed, int deliveryInterval, int deliveredCargos, int deliveryJourneys, Time activeTime);

	
	void setType(char type);
	char getType();

	void setCapacity(int capacity);
	int getCapacity();
	
	void setCheckupTime(Time checkupTime);
	Time getCheckupTime();
	
	void setSpeed(int speed);
	int getSpeed();
	
	void setDeliveryInterval(int deliveryInterval);
	int getDeliveryInterval();
	
	void setDeliveredCargos(int deliveredCargos);
	int getDeliveredCargos();
	
	void setDeliveredJourneys(int deliveryJourneys);
	int getDeliveredJourneys();
	
	void setActiveTime(Time activeTime);
	Time getActiveTime();

};

