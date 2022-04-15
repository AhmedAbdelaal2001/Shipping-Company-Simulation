#pragma once
#include "Time.h"

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

	Cargo(Time prepTime, int loadTime = 0, char type = 'U', float distance = 0, float cost = 0, float priority = 0);

	//Eftkr el setters wel getters
};

