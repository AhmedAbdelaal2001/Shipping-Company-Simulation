#include "Cargo.h"

Cargo::Cargo(Time prepTime, Time loadTime, int id, char type, float distance, float cost, float priority) {

	if (type == 'V')
		priority = cost + distance - 10 * prepTime.getDays() - 5 * prepTime.getHours();

	setPrepTime(prepTime);
	setLoadTime(loadTime);
	setId(id);
	setType(type);
	setDistance(distance);
	setCost(cost);
	setPriority(priority);
}

void Cargo::setId(int id) { this->id = id; }
int Cargo::getId() const { return id; }

void Cargo::setPrepTime(Time prepTime) { this->prepTime = prepTime; }
Time Cargo::getPrepTime() const { return prepTime; }

void Cargo::setLoadTime(Time loadTime) { this->loadTime = loadTime; }
Time Cargo::getLoadTime() const { return loadTime; }

void Cargo::setType(char type) { this->type = type; }
char Cargo::getType() { return type; }

void Cargo::setDistance(int distance) { this->distance = distance; }
int Cargo::getDistance() const { return distance; }

void Cargo::setCost(int cost) { this->cost = cost; }
int Cargo::getCost() const { return cost; }

void Cargo::setPriority(int priority) { this->priority = priority; }
int Cargo::getPriority() const { return priority; }