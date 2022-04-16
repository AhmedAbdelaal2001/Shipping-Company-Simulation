#include "Cancellation.h"

Cancellation::Cancellation(Time eventTime, Company* pCompany, int id) : Event(eventTime, pCompany, id) {

	this->id = id;

}

bool Cancellation::Execute() {

	Company* pCompany = Event::getPCompany();
	Cargo* cancelledCargo;

	return pCompany->getWaitingNormalCargo()->deleteElement(Event::getID(), cancelledCargo);
}