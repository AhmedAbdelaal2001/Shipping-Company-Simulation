#include "Preparation.h"
#include <fstream>

Perparation::Perparation(Company* pCompany) : Event(pCompany)
{
	// Setting the parameters to default values
	cargoType = 'U';
	distance = -1;
	cost = -1;

}


void Perparation::load(ifstream& inputFile) {

	// loading 
	inputFile >> cargoType;

	char colon;
	int id, days, hours;

	inputFile >> days >> colon >> hours;
	Time eventTime(days, hours);
	setEventTime(eventTime);

	inputFile >> id >> distance;
	setID(id);

	inputFile >> hours;
	Time loadingTime(0, hours);

	inputFile >> cost;
}



bool Perparation::Execute() {
	
	Time LTime(loadTime);
	Cargo* newCargo = new Cargo(Event::getEventTime(), LTime, Event::getID(), cargoType, distance, cost);

	switch (cargoType) {
	
	case 'N':
		getPCompany()->enqueueNormal(newCargo, Event::getID());
		break;

	case 'S':
		getPCompany()->enqueueSpecial(newCargo);
		break;

	case 'V':
		getPCompany()->enqueueVIP(newCargo);
	}

	return true;

}
