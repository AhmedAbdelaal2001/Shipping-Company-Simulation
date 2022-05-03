#include "Truck.h"

int Truck::currID = 0;

Truck::Truck(char type, int capacity, Time checkupTime, int speed/*, Time deliveryInterval, int deliveredCargos, int deliveryJourneys, Time activeTime*/)
{
	currID++;
	cargoList = new PriorityQueue<Cargo*>(capacity);
	setID(currID);
	setType(type);
	setCapacity(capacity);
	setCheckupTime(checkupTime);
	setSpeed(speed);
	setMovedDistance(0);
	/*setDeliveryInterval(deliveryInterval);
	setDeliveredCargos(deliveredCargos);
	setDeliveredJourneys(deliveryJourneys);
	setActiveTime(activeTime);*/
	setPriority(speed / capacity);

}

bool Truck::isFull() {
	return cargoList->getCount() == capacity;
}

Time Truck::getMoveTime() {
	moveTime.setHours(-1 * priority);
	return moveTime;
}

bool Truck::isEmpty() {
	return cargoList->getCount() == 0;
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

void Truck::setMovedDistance(int movedDistance) {
	this->movedDistance = movedDistance;
}

int Truck::getMovedDistance() const {
	return movedDistance;
}

//void Truck::setDeliveryInterval(Time deliveryInterval)
//{
//	this->deliveryInterval = deliveryInterval;
//}
//
//Time Truck::getDeliveryInterval() {
//	return deliveryInterval;
//}
//
//void Truck::setDeliveredCargos(int deliveredCargos)
//{
//	this->deliveredCargos = deliveredCargos;
//}
//
//int Truck::getDeliveredCargos() {
//	return deliveredCargos;
//}
//
//void Truck::setDeliveredJourneys(int deliveryJourneys)
//{
//	this->deliveryJourneys = deliveryJourneys;
//}
//
//int Truck::getDeliveredJourneys() {
//	return deliveryJourneys;
//}

void Truck::setActiveTime(Time activeTime)
{
	this->activeTime = activeTime;
}

Time Truck::getActiveTime() {
	return activeTime;
}

void Truck::enqueueCargo(Cargo* loading) {
	cargoList->enqueue(loading);
}


void Truck::saveToFile(ofstream outFile) {
	outFile << id << "	";
}

ostream& operator << (ostream& out, Truck* truckPtr) {
	out << truckPtr->getID();
	Cargo* tempCargoPtr = nullptr;
	truckPtr->cargoList->peek(tempCargoPtr);

	if (tempCargoPtr) {
		switch (tempCargoPtr->getType()) {
		case 'N':
			out << "[";
			break;
		case 'S':
			out << "(";
			break;
		case 'V':
			out << "{";
			break;
		}

		truckPtr->cargoList->printQueue();

		switch (tempCargoPtr->getType()) {
		case 'N':
			out << "]";
			break;
		case 'S':
			out << ")";
			break;
		case 'V':
			out << "}";
			break;
		}
	}

	return out;
}


void Truck::setPriority(int priority)
{
	this->priority = priority;
}

int Truck::getPriority() const {
	return priority;
}

void Truck::updatePriority(int extraPriority) {
	priority += extraPriority;
}

int Truck::calcMovingPriority(Time currTime) {
	Cargo* frontCargo = nullptr;
	if(cargoList->peek(frontCargo))
		return currTime.getTotalHours() + (frontCargo->getDistance() - movedDistance) / speed + frontCargo->getLoadTime();
	return currTime.getTotalHours() + movedDistance / speed;
}


bool Truck::operator > (Truck* truckPtr) {
	return priority > truckPtr->getPriority();
}

Truck::~Truck() {
	delete cargoList;
}