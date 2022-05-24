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


void UI::print(Time currTime, Queue<Event*>* EventList, Container<Cargo*>** cargoContainersArr, Container<Truck*>** truckContainersArr)
{
	
	if (mode == "Interactive") {
		cin.get();

	}
	else if (mode == "Step_By_Step") {
		Sleep(1000);
	}

	cout << endl << "Current Time (Day:Hour):" << currTime << endl;

	printContainerBatch("Waiting Cargos: ", cargoContainersArr, 0, 3);
	printContainerBatch("Loading Trucks: ", truckContainersArr, 0, 1);
	printContainerBatch("Empty Trucks: ", truckContainersArr, 1, 6);
	printContainerBatch("Moving Cargos: ", truckContainersArr, 7, 1);
	printContainerBatch("In-Checkup Trucks: ", truckContainersArr, 8, 3);
	printContainerBatch("In-Maintenance Trucks: ", truckContainersArr, 11, 6);
	printContainerBatch("Delivered Cargos: ", cargoContainersArr, 3, 3);

	cout << endl;
}