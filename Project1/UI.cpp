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

void UI::print(Time currTime, PriorityQueue<Truck*>* waitingNormalTrucks, PriorityQueue<Truck*>* waitingSpecialTrucks,PriorityQueue<Truck*>* waitingVIPTrucks, Queue<Truck*>* normalCheckupTrucks, Queue<Truck*>* specialCheckupTrucks, Queue<Truck*>* VIPCheckupTrucks, PriorityQueue<Truck*>* movingTrucks, CrossLinkedList<Cargo*>* waitingNormalCargo, Queue<Cargo*>* waitingSpecialCargo, PriorityQueue<Cargo*>* waitingVIPCargo, Queue<Event*>* EventList, Queue<Cargo*>* normalDeliveredCargo, Queue<Cargo*>* specialDeliveredCargo, Queue<Cargo*>* VIPDeliveredCargo, PriorityQueue<Truck*>* LoadingTrucks) {
	if (mode == "Interactive") {
		cin.get();
		
	}
	else if (mode == "Step_By_Step") {
		Sleep(1000);
	}
	cout << "Current Time (Day:Hour):" << currTime << endl;

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

	cout << waitingNormalTrucks->getCount() + waitingSpecialTrucks->getCount() + waitingVIPTrucks->getCount();
	cout << " Empty Trucks: ";
	cout << "["; waitingNormalTrucks->printQueue(); cout << "] ";
	cout << "("; waitingSpecialTrucks->printQueue(); cout << ") ";
	cout << "{"; waitingVIPTrucks->printQueue(); cout << "}";

	cout << endl << "-------------------------------------------------------------------------------------------------------" << endl;

	cout << movingTrucks->getCount() << " Moving Cargos: ";
	movingTrucks->printQueue();

	cout << endl << "-------------------------------------------------------------------------------------------------------" << endl;

	cout << normalCheckupTrucks-> getCount() << " In-Checkup Trucks: ";
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