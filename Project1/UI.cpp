#include "UI.h"
#include "Windows.h"

UI::UI(Company* pCompany) {
	this->pCompany = pCompany;
}

string UI::getMode() const {
	return mode;
}

void UI::getModefromUser() {
	cin >> mode;

}

string UI::getFileName() {
	string fileName;
	cout << "Enter file name: (appended by .txt)" << endl;
	cin >> fileName;
	return fileName;
}

void UI::printMessage(string message) {
	cout << message << endl;
}

void UI::print(Time currTime) {
	if (mode == "Interactive") {
		pCompany->printAll(currTime);
		cin.get();
	}
	else if (mode == "Step_By_Step") {
		pCompany->printAll(currTime);
		Sleep(1000);
	}
}