#include "UI.h"
#include "Windows.h"

UI::UI(Company* pCompany) {
	this->pCompany = pCompany;
}

void UI::getModefromFile() {
	cin >> mode;

}

string UI::getMode() const {
	return mode;
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
		cin.get();
		pCompany->printAll(currTime);
	}
	else if (mode == "Step_By_Step") {
		Sleep(1000);
		pCompany->printAll(currTime);

	}
}