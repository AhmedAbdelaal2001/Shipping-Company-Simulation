#pragma once
#include "Time.h"
#include <iostream>
using namespace std;

class Cargo
{

private:
	int id;
	Time prepTime;
	Time loadTime;
	char type;
	int distance;
	int cost;
	int priority;

public:
	Cargo();

	Cargo(Time prepTime, Time loadTime, int id, char type = 'U', float distance = 0, float cost = 0, float priority = 0);

	friend ostream& operator << (ostream& out, Cargo cargo);

	void setId(int id);
	int getId() const;

	void setPrepTime(Time prepTime);
	Time getPrepTime() const;

	void setLoadTime(Time loadTime);
	Time getLoadTime() const;

	void setType(char type);
	char getType();

	void setDistance(int distance);
	int getDistance() const;

	void setCost(int cost);
	int getCost() const;

	void setPriority(int priority);
	int getPriority() const;
};

