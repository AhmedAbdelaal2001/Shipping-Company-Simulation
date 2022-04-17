#include "Preparation.h"

Perparation::Perparation(Time eventTime, Company* pCompany, int id, char type, int distance, int cost, Time loadTime)
	: Event(eventTime, pCompany, id)
{
	this->type = type;
	this->distance = distance;
	this->cost = cost;
	this->loadTime = loadTime;
}



bool Perparation::Execute() {
	
	Time LTime(loadTime);
	Cargo* newCargo = new Cargo(Event::getEventTime(), LTime, Event::getID(), type, distance, cost);

	switch (type) {
	
	case 'N':
		getPCompany()->getWaitingNormalCargo()->insertLast(newCargo, Event::getID());
		break;

	case 'S':
		getPCompany()->getWaitingSpecialCargo()->enqueue(newCargo);
		break;

	case 'V':
		getPCompany()->getWaitingVIPCargo()->enqueue(newCargo);
	}

	return true;

}
