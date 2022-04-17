#pragma once

#include "Company.h"
#include "Time.h"
#include "Cargo.h"
#include <iostream>

using namespace std;

class Company;

class Event
{
private:
	Time eventTime;
	int id;
	Company *pCompany;

public:
	Event(Time eventTime, Company* pCompany, int id);
	Company* getPCompany() const;
	int getID() const;
	Time getEventTime() const;

	virtual bool Execute() = 0;

	friend ostream& operator<< (ostream & out, Event * event);
};

