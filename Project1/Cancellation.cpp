#include "Cancellation.h"

Cancellation::Cancellation(Company* pCompany) : Event(pCompany) {


}

bool Cancellation::Execute() {

	Company* pCompany = getPCompany();
	Cargo* cancelledCargo;

	return pCompany->deleteNormalCargo(getID(), cancelledCargo);
}


void Cancellation::load(ifstream& inputFile) {
	char colon;
	int id, days, hours;

	inputFile >> days >> colon >> hours;
	Time eventTime(days, hours);
	setEventTime(eventTime);

	inputFile >> id;
	setID(id);
}