#include "Truck.h"

int Truck::currID = 0;

Truck::Truck(char type, int capacity, Time checkupTime, int speed/*, Time deliveryInterval, int deliveredCargos, int deliveryJourneys, Time activeTime*/):
	cargoList(capacity)
{
	currID++;
	setID(currID);
	setType(type);
	setCapacity(capacity);
	setCheckupTime(checkupTime);
	setSpeed(speed);
	/*setDeliveryInterval(deliveryInterval);
	setDeliveredCargos(deliveredCargos);
	setDeliveredJourneys(deliveryJourneys);
	setActiveTime(activeTime);*/
	setPriority(speed/capacity);
}

void Truck::setType(char type)
{
	this->type = type;
}

char Truck::getType() {
	return type;
}

void Truck::setCapacity(int capacity)
{
	this->capacity = capacity;
}

int Truck::getCapacity() {
	return capacity;
}

void Truck::setCheckupTime(Time checkupTime)
{
	this->checkupTime = checkupTime;
}

Time Truck::getCheckupTime() {
	return checkupTime;
}

void Truck::setID(int id) {
	this->id = id;
}
int Truck::getID() const {
	return id;
}

void Truck::setSpeed(int speed)
{
	this->speed = speed;
}

int Truck::getSpeed() {
	return speed;
}

void Truck::setDeliveryInterval(Time deliveryInterval)
{
	this->deliveryInterval = deliveryInterval;
}

Time Truck::getDeliveryInterval() {
	return deliveryInterval;
}

void Truck::setDeliveredCargos(int deliveredCargos)
{
	this->deliveredCargos = deliveredCargos;
}

int Truck::getDeliveredCargos() {
	return deliveredCargos;
}

void Truck::setDeliveredJourneys(int deliveryJourneys)
{
	this->deliveryJourneys = deliveryJourneys;
}

int Truck::getDeliveredJourneys() {
	return deliveryJourneys;
}

void Truck::setActiveTime(Time activeTime)
{
	this->activeTime = activeTime;
}

Time Truck::getActiveTime() {
	return activeTime;
}

void Truck::saveToFile(ofstream outFile) {
	outFile << id << "	";
}

ostream& operator << (ostream& out, Truck* truckPtr) {
	out << truckPtr->getID();
	return out;
	//TODO:cargos el gowaha
}


void Truck::setPriority(int priority)
{
	this->priority = priority;
}
int Truck::getPriority() const {
	return priority;
}
bool Truck::operator > (Truck* truckPtr) {
		return priority > truckPtr->getPriority();
}