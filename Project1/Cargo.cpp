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


	setPrepTime(prepTime);
	setLoadTime(loadTime);
	setId(id);
	setType(type);
	setDistance(distance);
	setCost(cost);
	if (type == 'V')
		computePriority();  //Computes the priority according according the cargo's cost, distance, and prep time
	
}

void Cargo::computePriority() {
	priority = cost + distance - 10 * prepTime.getDays() - 5 * prepTime.getHours(); 
	// VIP cargo with high cost and big distance needs are  at the head of PQ
	//high prepaeration time means its recently waiting , it should be at the end of the pQ
	//low prep time means it's been ready for a long time -> hence, has higher priority to be assinged .
	//prepTime in days is  dominant on PrepTime in hours .
}

int Cargo::updatePriority(int extraCost) {                                 //Used in promotions 
	cost += extraCost;                         //just for readibility 
	computePriority();                        //The cargo's priority is calculated using its new cost
	                                         // if autoP (extra cost==0)
	return priority;
}

//Setters and Getters
void Cargo::setId(int id) { this->id = id; }
int Cargo::getId() const { return id; }

void Cargo::setTruckID(int id)
{
	truckID = id;
}

int Cargo::getTruckID() const
{
	return truckID;
}

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

void Cargo::setWaitingTime(Time currTime) {
	waitingTime = currTime - prepTime;
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