#include "UI.h"


UI::UI() {
	cout << "Enter mode: (Interactive, Step_By_Step, Silent)" << endl;
	cin >> mode;
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
void UI::silentPrint() {
	cout << "Silent Mode" << endl;
	cout << "Simulation Starts..." << endl;
	cout << "Simulation ends, Output file created" << endl;
}