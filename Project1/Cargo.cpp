#include "Cargo.h"

ostream& operator << (ostream& out, Cargo* cargo) {

	out << cargo->getId();
	return out;
}

bool Cargo::operator > (Cargo* cargo) {
	return priority > cargo->getPriority();
}

//Default Constructor
Cargo::Cargo() {
	Time zeroTime(0, 1);
	setPrepTime(zeroTime);
	setLoadTime(0);
	setId(0);
	setType('U');
	setDistance(0);
	setCost(0);
	setPriority(0);
}

//non-default constructor
Cargo::Cargo(Time prepTime, Time loadTime, int id, char type, int distance, float cost, float priority) {

	if (type == 'V')
		priority = computePriority(cost, distance, prepTime);  //Computes the priority according according the cargo's cost, distance, and prep time

	setPrepTime(prepTime);
	setLoadTime(loadTime);
	setId(id);
	setType(type);
	setDistance(distance);
	setCost(cost);
	setPriority(priority);      //Sets the priority with the value calculated above
}

int Cargo::computePriority(int cost, int distance, Time prepTime) {
	priority = cost + distance - 10 * prepTime.getDays() - 5 * prepTime.getHours(); //Priority equation, cost and distance increase the
																						 //cargo's priority while a high preparation time 
																						//decreases it
	return priority;
}

int Cargo::updatePriority(int newCost) {                                 //Used in promotions 

	computePriority(newCost, distance, prepTime);                        //The cargo's priority is calculated using its new cost
	return priority;
}

//Setters and Getters
void Cargo::setId(int id) { this->id = id; }
int Cargo::getId() const { return id; }

void Cargo::setPrepTime(Time prepTime) { this->prepTime = prepTime; }
Time Cargo::getPrepTime() const { return prepTime; }

void Cargo::setLoadTime(Time loadTime) { this->loadTime = loadTime; }
Time Cargo::getLoadTime() const { return loadTime; }

void Cargo::setDeliveryTime(Time deliveryTime) {
	this->deliveryTime = deliveryTime;
}
Time Cargo::getDeliveryTime() const {
	return deliveryTime;
}

void Cargo::setWaitingTime(Time waitingTime) {
	this->waitingTime = waitingTime;
}
Time Cargo::getWaitingTime() const {
	return waitingTime;
}

void Cargo::setType(char type) { this->type = type; }
char Cargo::getType() { return type; }

void Cargo::setDistance(int distance) { this->distance = distance; }
int Cargo::getDistance() const { return distance; }

void Cargo::setCost(int cost) { this->cost = cost; }
int Cargo::getCost() const { return cost; }

void Cargo::setPriority(int priority) { this->priority = priority; }
int Cargo::getPriority() const { return priority; }

void Cargo::setPriorityToDistance() { priority = -1 * distance; }


Time Cargo::calcWait(Time currTime) {
	return currTime - prepTime;
}

// Writes the cargo's info to the output file.
void Cargo::saveToFile(ofstream& outFile) {
	outFile << deliveryTime.getDays() << ":" << deliveryTime.getHours() << "	" << id << "	" << prepTime.getDays() << ":" << prepTime.getHours() << "	" << waitingTime.getDays() << ":" << waitingTime.getHours() << "	";
}

Cargo::operator int() {
	return id;
}