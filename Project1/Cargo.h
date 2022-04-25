#pragma once
#include "Time.h"
#include <iostream>
#include <fstream>

using namespace std;

class Cargo
{

private:
	int id;
	Time prepTime;
	Time loadTime;
	Time waitingTime;
	Time deliveryTime;
	char type;
	int distance;
	int cost;
	int priority;

public:
	Cargo();

	Cargo(Time prepTime, Time loadTime, int id, char type = 'U', int distance = 0, float cost = 0, float priority = 0);



	int computePriority(int cost, int distance, Time prepTime);
	int updatePriority(int cost);

	friend ostream& operator << (ostream& out, Cargo* cargo);
	bool operator > (Cargo* cargo);

	void setId(int id);
	int getId() const;

	void setPrepTime(Time prepTime);
	Time getPrepTime() const;

	void setLoadTime(Time loadTime);
	Time getLoadTime() const;

	void setWaitingTime(Time waitingTime);
	Time getWaitingTime() const;

	void setDeliveryTime(Time deliveryTime);
	Time getDeliveryTime() const;

	void setType(char type);
	char getType();

	void setDistance(int distance);
	int getDistance() const;

	void setCost(int cost);
	int getCost() const;

	void setPriority(int priority);
	int getPriority() const;

	void saveToFile(ofstream& outFile);

	operator int();
};

