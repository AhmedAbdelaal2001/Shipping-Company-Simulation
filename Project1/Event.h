#pragma once
#include "Time.h"
#include "Cargo.h"
#include "Company.h"

class Event
{
private:
	Time eventTime;
	int id;
	Company* pCompany;

public:
	Event(Time eventTime, Company* pCompany, int id);
	Company* getPCompany() const;
	int getID() const;
	Time getEventTime() const;

	virtual bool Execute() = 0;
};

