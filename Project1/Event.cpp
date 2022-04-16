#include "Event.h"
Event::Event(Time eventTime, Company* pCompany, int id)
{
	this->eventTime = eventTime;
	this->pCompany = pCompany;
	this->id = id;
}

Company* Event::getPCompany() const {
	return pCompany;
}

int Event::getID() const {
	return id;
}

Time Event::getEventTime() const{
	return eventTime;
}