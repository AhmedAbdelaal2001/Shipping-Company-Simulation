#include "Truck.h"

int Truck::currID = 0;
int Truck::journeysBeforeCheckup = 0;

Truck::Truck(char type, int capacity, Time checkupTime, int speed, int journeysBeforeCheckup, char shiftTime)
{
	currID++;
	this->journeysBeforeCheckup = journeysBeforeCheckup;
	cargoList = new PriorityQueue<Cargo*>(capacity);
	setID(currID);
	setType(type);
	setCapacity(capacity);
	setCheckupTime(checkupTime);
	setSpeed(speed);
	setMovedDistance(0);
	worksAtNight = shiftTime == 'N' ? true : false;
	/*setDeliveryInterval(deliveryInterval);
	setDeliveredCargos(deliveredCargos);
	setDeliveredJourneys(deliveryJourneys);
	setActiveTime(activeTime);*/
	setWaitingPriority();
	deliveredCargos = deliveryJourneys = 0;
}

bool Truck::isFull() {
	return cargoList->getCount() == capacity;
}

Time Truck::getMoveTime() {
	Time newMoveTime;
	newMoveTime.setHours(-1 * priority);
	moveTime = newMoveTime;

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
	this->checkupDuration = checkupTime;
}

Time Truck::getCheckupTime() const {
	return checkupDuration;
}

void Truck::setLeaveTime(Time currTime) {
	leaveTime  = currTime + checkupDuration;
}
Time Truck::getLeaveTime() const {
	return leaveTime;
}

void Truck::setMoveTime(Time moveTime) { this->moveTime = moveTime; }
Time Truck::getMoveTime() const { return moveTime; }

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

void Truck::setDeliveryInterval(Time deliveryInterval) {
	this->deliveryInterval = deliveryInterval;
}

Time Truck::getDeliveryInterval() {
	return deliveryInterval;
}

void Truck::incrementDeliveredCargos() {
	deliveredCargos++;
}

int Truck::getDeliveredCargos() {
	return deliveredCargos;
}

void Truck::incrementDeliveredJourneys() {
	deliveryJourneys++;
}

int Truck::getDeliveredJourneys() {
	return deliveryJourneys;
}

void Truck::incrementActiveTime(Time currTime) {
	activeTime = activeTime + (currTime - moveTime);
}

Time Truck::getActiveTime() {
	return activeTime;
}

bool Truck::needsCheckup() const {
	return deliveryJourneys == journeysBeforeCheckup;
}


void Truck::returnStats(Time currTime) {
	Time restartTime;

	setMovedDistance(0);
	setWaitingPriority();
	setDeliveryInterval(currTime - getMoveTime());
	setMoveTime(restartTime);
	incrementDeliveredJourneys();

}

void Truck::deliveryStats(Time currTime, Cargo* deliveredCargo) {
	
	deliveredCargo->setDeliveryTime(currTime);
	incrementDeliveredCargos();
	setMovedDistance(deliveredCargo->getDistance());
	setMovingPriority(currTime);

}

void Truck::enqueueCargo(Cargo* loading) {
	cargoList->enqueue(loading);
	moveTime = moveTime + loading->getLoadTime();
}

bool Truck::dequeueCargo(Cargo*& cargoPtr) {
	
	return cargoList->dequeue(cargoPtr);

}

bool Truck::containsNormal()
{
	Cargo* cargoPtr = nullptr;
	if (cargoList->peek(cargoPtr) && cargoPtr->getType() == 'N')
		return true;

	return false;
}

bool Truck::containsSpecial()
{
	Cargo* cargoPtr = nullptr;
	if (cargoList->peek(cargoPtr) && cargoPtr->getType() == 'S')
		return true;

	return false;
}

bool Truck::containsVIP()
{
	Cargo* cargoPtr = nullptr;
	if (cargoList->peek(cargoPtr) && cargoPtr->getType() == 'V')
		return true;

	return false;
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

void Truck::setWaitingPriority() {

	setPriority(speed / capacity);

}


int Truck::getPriority() const {
	return priority;
}

void Truck::incrementPriority(int extraPriority) {
	priority += extraPriority;
}

void Truck::setPriorityToMoveTime() {
	
	priority = -1 * moveTime.getTotalHours();

}


void Truck::setMovingPriority(Time currTime) {
	Cargo* frontCargo = nullptr;

	if(cargoList->peek(frontCargo))
		priority = (currTime + frontCargo->getLoadTime()).getTotalHours() + (frontCargo->getDistance() - movedDistance) / speed;
	else
		priority = currTime.getTotalHours() + movedDistance / speed;

	priority *= -1;
}


bool Truck::operator > (Truck* truckPtr) {
	return priority > truckPtr->getPriority();
}

Truck::~Truck() {
	delete cargoList;
}