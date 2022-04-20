#include "UI.h"


UI::UI(Company* pCompany) {
	this->pCompany = pCompany;
}


string UI::getFileName() {
	string fileName;
	cout << "Enter file name: (appended by .txt)" << endl;
	cin >> fileName;
	return fileName;
}

void UI::print(string message) {
	cout << message << endl;
}


void UI::interactivePrint(Time currTime) {
	pCompany->printAll(currTime);
}

void UI::stepByStepPrint() {

}

void UI::silentPrint() {
	cout << "Silent Mode" << endl;
	cout << "Simulation Starts..." << endl;
	cout << "Simulation ends, Output file created" << endl;
}