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
	string mode;

public:
	UI(Company* pCompany);

	string getMode() const;
	
	void getModefromUser();

	string getFileName();

	void printMessage(string message);
	
	void print(Time currTime);


};

