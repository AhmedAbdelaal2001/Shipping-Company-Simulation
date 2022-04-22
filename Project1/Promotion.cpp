#include "Promotion.h"


Promotion::Promotion(Company* pCompany) : Event(pCompany) {
	extraCost = 0;
}

void Promotion::load(ifstream& inputFile) {

	char colon;
	int id, days, hours;

	inputFile >> days >> colon >> hours;
	Time eventTime(days, hours);
	setEventTime(eventTime);

	inputFile >> id >> extraCost;
	setID(id);
}

bool Promotion::Execute()
{
	Company* pCompany = Event::getPCompany();
	Cargo* promotedCargo;
	bool promotionFlag = pCompany->deleteNormalCargo(Event::getID(), promotedCargo);
	
	if (!promotionFlag)
		return false;
	
	promotedCargo->setType('V');
	int oldCost = promotedCargo->getCost();
	int newCost = oldCost + extraCost;
	promotedCargo->setCost(newCost);
	promotedCargo->updatePriority(newCost);
	
	pCompany->enqueueVIP(promotedCargo);
	return true;
}