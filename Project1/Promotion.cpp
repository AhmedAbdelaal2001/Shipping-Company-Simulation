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
	Company* pCompany = Event::getPCompany(); //get Ptr to company
	Cargo* promotedCargo;
	bool promotionFlag = pCompany->deleteNormalCargo(Event::getID(), promotedCargo); //return waitingNormal->deleteElement. 
	
	if (!promotionFlag) //empty waiting Normal Cargo list : if the id  refers to a loaded or delivered or moving cargo .
		return false;
	
	promotedCargo->setType('V');             //set type to VIP
	int oldCost = promotedCargo->getCost();  // update its cost 
	                                          
	int newCost = oldCost + extraCost;
	promotedCargo->setCost(newCost);         // update  priority
	promotedCargo->updatePriority(newCost);
	
	pCompany->enqueueVIP(promotedCargo);     //add it to vip waiting list
	return true;
}