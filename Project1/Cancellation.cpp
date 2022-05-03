#include "Cancellation.h"

Cancellation::Cancellation(Company* pCompany) : Event(pCompany) {
	// Constructor only sets the company pointers
}

bool Cancellation::Execute() {

	Company* pCompany = getPCompany();
	Cargo* cancelledCargo;

	return pCompany->deleteNormalCargo(getID(), cancelledCargo);  // Calling a function in company to delete cancelled cargo
}


void Cancellation::load(ifstream& inputFile) {

	// Loading cancellation parameters
	char colon;
	int id, days, hours;

	inputFile >> days >> colon >> hours;
	Time eventTime(days, hours);
	setEventTime(eventTime);

	inputFile >> id;
	setID(id);
}