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
	ArrayList<Cargo> cargoList;
	int deliveredCargos;
	int deliveryJourneys;
	Time activeTime;

public:
	Truck(char type, int capacity, Time checkupTime, int speed, int deliveryInterval, int deliveredCargos, int deliveryJourneys, Time activeTime);

	//E3ml el setters wel getters.

};

