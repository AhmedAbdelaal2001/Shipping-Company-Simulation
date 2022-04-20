#include "Promotion.h"


Promotion::Promotion(Time eventTime, Company* pCompany, int id, int extraCost) : Event(eventTime, pCompany, id) {
	this->extraCost = extraCost;
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