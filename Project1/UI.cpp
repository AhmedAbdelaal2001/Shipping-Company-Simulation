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


void UI::print(Time currTime, PriorityQueue<Truck*>* waitingNormalTrucks, PriorityQueue<Truck*>* normalNightTrucks,
	PriorityQueue<Truck*>* waitingSpecialTrucks, PriorityQueue<Truck*>* specialNightTrucks, PriorityQueue<Truck*>* waitingVIPTrucks,
	PriorityQueue<Truck*>* VIPNightTrucks, Queue<Truck*>* normalCheckupTrucks, Queue<Truck*>* specialCheckupTrucks,
	Queue<Truck*>* VIPCheckupTrucks, PriorityQueue<Truck*>* movingTrucks, CrossLinkedList<Cargo*>* waitingNormalCargo,
	Queue<Cargo*>* waitingSpecialCargo, PriorityQueue<Cargo*>* waitingVIPCargo, Queue<Event*>* EventList,
	Queue<Cargo*>* normalDeliveredCargo, Queue<Cargo*>* specialDeliveredCargo, Queue<Cargo*>* VIPDeliveredCargo,
	PriorityQueue<Truck*>* LoadingTrucks, MaintenanceTrucks* normalMaintenance, MaintenanceTrucks* specialMaintenance,
	MaintenanceTrucks* VIPMaintenance, MaintenanceTrucks* nightVIPMaintenance, MaintenanceTrucks* nightSpecialMaintenance,
	MaintenanceTrucks* nightNormalMaintenance) {
	
	if (mode == "Interactive") {
		cin.get();

	}
	else if (mode == "Step_By_Step") {
		Sleep(1000);
	}


	cout << endl << "Current Time (Day:Hour):" << currTime << endl;

	cout << waitingNormalCargo->getCount() + waitingVIPCargo->getCount() + waitingSpecialCargo->getCount() << " ";
	cout << "Waiting Cargos: ";
	waitingNormalCargo->printList();
	cout << " ";
	cout << "(";
	waitingSpecialCargo->printQueue();
	cout << ")";
	cout << " ";
	cout << "{";
	waitingVIPCargo->printQueue();
	cout << "}";

	cout << endl << "-------------------------------------------------------------------------------------------------------" << endl;

	cout << LoadingTrucks->getCount() << " Loading Trucks: ";
	LoadingTrucks->printQueue();
	cout << endl << "-------------------------------------------------------------------------------------------------------" << endl;

	cout << waitingNormalTrucks->getCount() + normalNightTrucks->getCount() + waitingSpecialTrucks->getCount() + specialNightTrucks->getCount() + waitingVIPTrucks->getCount() + VIPNightTrucks->getCount();
	cout << " Empty Trucks: ";
	cout << "["; 
	waitingNormalTrucks->printQueue(); if (!waitingNormalTrucks->isEmpty() && !normalNightTrucks->isEmpty()) cout << ","; normalNightTrucks->printQueue(); cout << "] ";
	cout << "("; 
	waitingSpecialTrucks->printQueue(); if (!waitingSpecialTrucks->isEmpty() && !specialNightTrucks->isEmpty()) cout << ","; specialNightTrucks->printQueue(); 
	cout << ") ";
	cout << "{"; 
	waitingVIPTrucks->printQueue(); if (!waitingVIPTrucks->isEmpty() && !VIPNightTrucks->isEmpty()) cout << ",";  VIPNightTrucks->printQueue(); 
	cout << "}";

	cout << endl << "-------------------------------------------------------------------------------------------------------" << endl;

	cout << movingTrucks->getCount() << " Moving Cargos: ";
	movingTrucks->printQueue();

	cout << endl << "-------------------------------------------------------------------------------------------------------" << endl;

	cout << normalCheckupTrucks->getCount() + specialCheckupTrucks->getCount() + VIPCheckupTrucks->getCount() << " In-Checkup Trucks: ";
	cout << "[";
	normalCheckupTrucks->printQueue();
	cout << "] ";
	cout << "(";
	specialCheckupTrucks->printQueue();
	cout << ")";
	cout << " ";
	cout << "{";
	VIPCheckupTrucks->printQueue();
	cout << "}";
	cout << endl << "-------------------------------------------------------------------------------------------------------" << endl;

	cout << normalMaintenance->getCount() + nightNormalMaintenance->getCount() + specialMaintenance->getCount() + nightSpecialMaintenance->getCount() + VIPMaintenance->getCount() + nightVIPMaintenance->getCount();
	cout << " In-Maintenance Trucks: ";
	cout << "[";
	normalMaintenance->printQueue(); if (!normalMaintenance->isEmpty() && !nightNormalMaintenance->isEmpty()) cout << ","; nightNormalMaintenance->printQueue(); cout << "] ";
	cout << "(";
	specialMaintenance->printQueue(); if (!specialMaintenance->isEmpty() && !nightSpecialMaintenance->isEmpty()) cout << ","; nightSpecialMaintenance->printQueue();
	cout << ") ";
	cout << "{";
	VIPMaintenance->printQueue(); if (!VIPMaintenance->isEmpty() && !nightVIPMaintenance->isEmpty()) cout << ",";  nightVIPMaintenance->printQueue();
	cout << "}";

	cout << endl << "-------------------------------------------------------------------------------------------------------" << endl;

	cout << normalDeliveredCargo->getCount() + specialDeliveredCargo->getCount() + VIPDeliveredCargo->getCount() << " ";
	cout << "Delivered Cargos: ";
	cout << "[";
	normalDeliveredCargo->printQueue();
	cout << "] ";
	cout << "(";
	specialDeliveredCargo->printQueue();
	cout << ") ";
	cout << "{";
	VIPDeliveredCargo->printQueue();
	cout << "}";

	cout << endl << "-------------------------------------------------------------------------------------------------------" << endl;

	cout << endl;
}