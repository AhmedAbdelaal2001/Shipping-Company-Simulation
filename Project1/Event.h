#pragma once

#include "Company.h"
#include "Time.h"
#include "Cargo.h"
#include <iostream>
#include <fstream>

using namespace std;

class Company;

class Event
{
private:
	Time eventTime;
	int id;
	Company *pCompany;

public:
	Event(Company* pCompany);

	Company* getPCompany() const;

	void setID(int id);
	int getID() const;

	void setEventTime(Time time);
	Time getEventTime() const;

	virtual bool Execute() = 0;

	virtual void load(ifstream& inputFile) = 0;

	friend ostream& operator<< (ostream & out, Event * event);
};

