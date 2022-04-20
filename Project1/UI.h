#pragma once

#include <iostream>
#include "Company.h"
#include "Time.h"

using namespace std;

class Company;

class UI
{

private:

	Company* pCompany;

public:
	UI(Company* pCompany);

	string getFileName();

	void print(string message);
	
	void interactivePrint(Time currTime);

	void stepByStepPrint();

	void silentPrint();


};

