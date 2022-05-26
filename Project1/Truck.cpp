#include "Truck.h"
Time defaultTime;
int Truck::currID = 0;
int Truck::journeysBeforeCheckup = 0;
Time Truck::totalActiveTime = defaultTime;

Truck::Truck(char type, int capacity, Time checkupTime, int speed, int journeysBeforeCheckup, char shiftTime, Time maintenanceD, int maintenanceDistance)
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
	totalMovedDist = 0;
	worksAtNight = shiftTime == 'N' ? true : false;
	failureFlag = false;
	setWaitingPriority();
	deliveredCargos = deliveryJourneys = 0;
	this->maintenanceDistance = maintenanceDistance;
	maintenanceDuration = maintenanceD;
	cargoType = 'X';
}

bool Truck::isFull() {
	return cargoList->getCount() == capacity;
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

bool Truck::WorksAtNight() const
{
	return worksAtNight;
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
	Time defaultTime;
	leaveTime = defaultTime;

	if (needsCheckup() || failureFlag)
		leaveTime = currTime + checkupDuration;
	else if (needsMaintenance())
		leaveTime = currTime + maintenanceDuration;
	
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

void Truck::resetTotalMovedDistance()
{
	totalMovedDist = 0;
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
	totalActiveTime = totalActiveTime + activeTime;

}

Time Truck::getActiveTime() {
	return activeTime;
}

Time Truck::getTotalActiveTime(){
	return totalActiveTime;
}

float Truck::calcUtilization(Time tSIM)
{
	return deliveryJourneys != 0 ? ((float)deliveredCargos) / (capacity * deliveryJourneys) * ((float)activeTime.getTotalHours() / tSIM.getTotalHours()) : 0;
}

bool Truck::needsCheckup() const {
	return deliveryJourneys == journeysBeforeCheckup;
}

bool Truck::needsMaintenance() const
{
	return totalMovedDist >= maintenanceDistance;
}

bool Truck::ifFailed() const
{
	return failureFlag;
}

bool Truck::deliveryFailure()
{
	// generating low probability of failure and dealing with failure if it occurs


	srand(time(0));
	int randomNum = rand() % 100;		//generating a random number between 0-99

	failureFlag = (randomNum >= 0 && randomNum < 10) ? true : false;	

	// applying effect of failure
	if (failureFlag) 
		speed /= 3;


	return failureFlag;
}

void Truck::resetFailureFlag()
{
	failureFlag = false;
}


void Truck::returnStats(Time currTime) {
	Time restartTime;

	// reseting truck's data
	cargoType = 'X';
	setWaitingPriority();
	setMoveTime(restartTime);

	// setting return stats
	totalMovedDist += 2 * movedDistance;
	setMovedDistance(0);
	setDeliveryInterval(currTime - getMoveTime());
	if (!failureFlag)
		incrementDeliveredJourneys();
}

void Truck::deliveryStats(Time currTime, Cargo* deliveredCargo) {
	
	// setting cargo delivery stats
	deliveredCargo->setDeliveryTime(currTime);
	deliveredCargo->setTruckID(id);

	// setting truck delivery stats
	incrementDeliveredCargos();
	setMovedDistance(deliveredCargo->getDistance());
	// recalculating its moving priority
	setMovingPriority(currTime);

}

void Truck::enqueueCargo(Cargo* loading) {
	
	cargoList->enqueue(loading);
	moveTime = moveTime + loading->getLoadTime();
	activeTime = activeTime + loading->getLoadTime();

}

bool Truck::dequeueCargo(Cargo*& cargoPtr) {
	
	bool dequeued =  cargoList->dequeue(cargoPtr);
	if (dequeued) {
		totalUnloadTime = totalUnloadTime + cargoPtr->getLoadTime(); // each time a cargo is dequeued , total unloadTime is incremented
	}
	else
	{
		Time defaultTime;
		totalUnloadTime = defaultTime;
	}

	return dequeued;
}

Time Truck::getTotalUnloadTime() const
{
	return totalUnloadTime;
}

void Truck::setCargoType()
{
	if (containsNormal()) cargoType = 'N';
	else if (containsSpecial()) cargoType = 'S';
	else if (containsVIP()) cargoType = 'V';
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

	if (truckPtr->ifFailed())
		out << "~";
	out << truckPtr->getID();

	switch (truckPtr->cargoType) {
	case 'N':
		out << "[";
		break;
	case 'S':
		out << "(";
		break;
	case 'V':
		out << "{";
		break;
	case 'X':
		break;
	}

	if (!truckPtr->isEmpty()) {

		truckPtr->cargoList->print();
	}

	switch (truckPtr->cargoType) {
	case 'N':
		out << "]";
		break;
	case 'S':
		out << ")";
		break;
	case 'V':
		out << "}";
		break;
	case 'X':
		break;
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

	if (cargoList->peek(frontCargo) && !failureFlag)
		priority = (moveTime + frontCargo->getLoadTime() + totalUnloadTime).getTotalHours() + frontCargo->getDistance() / speed;											//priority = (currTime + frontCargo->getLoadTime()).getTotalHours() + (frontCargo->getDistance() - movedDistance) / speed;
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