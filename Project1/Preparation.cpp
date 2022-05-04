#include "Preparation.h"
#include <fstream>

Preparation::Preparation(Company* pCompany) : Event(pCompany)
{
	// Setting the parameters to default values
	cargoType = 'U';
	distance = -1;
	cost = -1;

}


void Preparation::load(ifstream& inputFile) {

	// loading 
	inputFile >> cargoType;

	char colon;
	int id, days, hours;

	inputFile >> days >> colon >> hours;
	Time eventTime(days, hours);
	setEventTime(eventTime);

	inputFile >> id >> distance;
	setID(id);

	inputFile >> loadTime;

	inputFile >> cost;
}



bool Preparation::Execute() {
	Time LT(0, loadTime);

	Cargo* newCargo = new Cargo(Event::getEventTime(), LT, Event::getID(), cargoType, distance, cost);

	switch (cargoType) {

	case 'N':
		getPCompany()->enqueueNormal(newCargo, Event::getID());
		break;

	case 'S':
		getPCompany()->enqueueSpecial(newCargo);
		break;

	case 'V':
		getPCompany()->enqueueVIP(newCargo);
		break;
	}

	return true;

}
