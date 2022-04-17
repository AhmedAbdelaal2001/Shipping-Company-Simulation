#pragma once

#include <iostream>

using namespace std;

class UI
{

private:
	string mode;

public:
	UI();

	string getFileName();

	void print(string message);
	
	void silentPrint();
};

