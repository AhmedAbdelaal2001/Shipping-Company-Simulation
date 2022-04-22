#include "Event.h"

Event::Event(Company* pCompany)
{
	this->pCompany = pCompany;
	id = -1;
}


Company* Event::getPCompany() const {
	return pCompany;
}

void Event::setID(int id) {
	this->id = id;
}

int Event::getID() const {
	return id;
}

void Event::setEventTime(Time time) {
	eventTime = time;
}

Time Event::getEventTime() const{
	return eventTime;
}

ostream& operator<< (ostream& out, Event* event) {
	// TODO:
	return out;
}