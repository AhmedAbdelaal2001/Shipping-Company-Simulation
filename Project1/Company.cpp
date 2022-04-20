#include "Company.h"
#include "Preparation.h"
#include "Promotion.h"
#include "Cancellation.h"
#include <fstream>

Company::Company() {
	

	UI input(this);
	
	input.print("Enter input file name: ");
	string fileName = input.getFileName();

	ifstream inputFile(fileName);

	input.print("Enter output file name: ");
	outFileName = input.getFileName();

	cout << "Enter mode: (Interactive, Step_By_Step, Silent)" << endl;
	cin >> mode;

	nc_Count = sc_Count = vc_Count = cAutoP = 0;

	if (!inputFile.fail()) {


		inputFile >> n_Count >> s_Count >> v_Count;

		inputFile >> n_Speed >> s_Speed >> v_Speed;

		inputFile >> n_Capacity >> s_Capacity >> v_Capacity;

		inputFile >> journeysBeforeCheckup;

		int checkup, autoProm, MaxW;

		inputFile >> checkup;
		n_CheckupD.setHours(checkup);

		inputFile >> checkup;
		s_CheckupD.setHours(checkup);

		inputFile >> checkup;
		v_CheckupD.setHours(checkup);

		inputFile >> autoProm;
		autoP.setDays(autoProm);

		inputFile >> MaxW;
		maxW.setHours(MaxW);

		inputFile >> eventsCount;
		EventList = new Queue<Event*>;

		char event_Type, cargoType, colon;
		int id, days, hours;
		Event* p_event;

		for (int i = 0; i < eventsCount; i++) {
			inputFile >> event_Type;

			if (event_Type == 'R') {

				int distance, cost;
				inputFile >> cargoType;

				if (cargoType == 'N')
					nc_Count++;
				else if (cargoType == 'S')
					sc_Count++;
				else if (cargoType == 'V')
					vc_Count++;

				inputFile >> days >> colon >> hours;
				Time eventTime(days, hours);

				inputFile >> id >> distance;

				inputFile >> hours;
				Time loadingTime(0, hours);

				inputFile >> cost;

				p_event = new Perparation(eventTime, this, id, cargoType, distance, cost, loadingTime);

				EventList->enqueue(p_event);
			}
			else if (event_Type == 'P') {
				int extra_Money;

				inputFile >> days >> colon >> hours;
				Time eventTime(days, hours);

				inputFile >> id >> extra_Money;

				p_event = new Promotion(eventTime, this, id, extra_Money);

				EventList->enqueue(p_event);
			}
			else if (event_Type == 'X') {
				nc_Count--;

				inputFile >> days >> colon >> hours;
				Time eventTime(days, hours);

				inputFile >> id;

				p_event = new Cancellation(eventTime, this, id);

				EventList->enqueue(p_event);
			}
		}



		waitingNormalCargo = new CrossLinkedList<Cargo*>(2 * n_Capacity);
		waitingSpecialCargo = new Queue<Cargo*>;
		waitingVIPCargo = new PriorityQueue<Cargo*>(2 * v_Capacity);

		normalDeliveredCargo = new Queue<Cargo*>;
		specialDeliveredCargo = new Queue<Cargo*>;
		VIPDeliveredCargo = new Queue<Cargo*>;
	

	}
}

//CrossLinkedList<Cargo*>* Company::getWaitingNormalCargo() const {
//	return waitingNormalCargo;
//}
//
//Queue<Cargo*>* Company::getWaitingSpecialCargo() const {
//	return waitingSpecialCargo;
//}
//
//PriorityQueue<Cargo*>* Company::getWaitingVIPCargo() const {
//	return waitingVIPCargo;
//}
//
//Queue<Event*>* Company::getEventList() const {
//	return EventList;
//}

bool Company::deleteNormalCargo(int id, Cargo*& delCargo) {
	return waitingNormalCargo->deleteElement(id, delCargo);
}

void Company::enqueueNormal(Cargo* cargo, int id) {
	waitingNormalCargo->insertLast(cargo, id);
}
void Company::enqueueSpecial(Cargo* cargo) {
	waitingSpecialCargo->enqueue(cargo);
}

void Company::enqueueVIP(Cargo* cargo) {
	waitingVIPCargo->enqueue(cargo);
}

void Company::saveToFile() {
	
	/*ofstream outFile("Output.txt");
	Cargo* temp;
	Time totalWait, avgWait;
	int totalCount = nc_Count + sc_Count + vc_Count;

	while (deliveredCargo->dequeue(temp)) {
		temp->saveToFile(outFile);
		totalWait = totalWait + temp->getWaitingTime();
		outFile << endl;
	}

	avgWait = totalWait / totalCount;

	outFile << "Cargos: " << totalCount << "	" << "[N: " << nc_Count << ", S: " << sc_Count << ", V: " << vc_Count << "]" << endl;
	
	outFile << "Cargo Avg Wait = " << avgWait << endl;

	int percentProm = (float) (cAutoP / nc_Count) * 100;
	outFile << "Auto-promoted Cargos: " << percentProm << "%" << endl;*/



}

bool Company::notTerminated() {
	return !EventList->isEmpty() || !waitingNormalCargo->isEmpty() || !waitingSpecialCargo->isEmpty() || !waitingVIPCargo->isEmpty();
}

void Company::print(Time currTime) {
	UI output(this);
	if (mode == "Interactive")
		output.interactivePrint(currTime);
	else if (mode == "Step_By_Step")
		output.stepByStepPrint();
	else if (mode == "Silent")
		output.silentPrint();

}

void Company::printAll(Time currTime) {
	cout << "Current Time (Day:Hour):" << currTime << endl;

	cout << waitingNormalCargo->getCount() + waitingVIPCargo->getCount() + waitingSpecialCargo->getCount() << " ";
	cout << "Waiting Cargos: ";
	waitingNormalCargo->printList() ;
	cout << " ";
	cout << "(";
	waitingSpecialCargo->printQueue();
	cout << ")";
	cout << " ";
	cout << "{";
	waitingVIPCargo->printQueue();
	cout << "}";

	cout << endl << "--------------------------------------" << endl;

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

	cout << endl << "--------------------------------------" << endl;
	cout << endl;

}

void Company::Simulate() {
	Time currTime(1, 1);
	Event* frontEvent;
	Cargo* delivered;


	while (notTerminated()) {
		
		while (EventList->peek(frontEvent) && currTime == frontEvent->getEventTime())
		{
			EventList->dequeue(frontEvent);
			frontEvent->Execute();
		}

		++currTime;

		if (currTime % 5 == 0) {
			if (waitingNormalCargo->deleteFirst(delivered)) {
				normalDeliveredCargo->enqueue(delivered);
				delivered->setDeliveryTime(currTime);
				delivered->setWaitingTime(currTime - delivered->getPrepTime());
			}

			if (waitingSpecialCargo->dequeue(delivered)) {
				specialDeliveredCargo->enqueue(delivered);
				delivered->setDeliveryTime(currTime);
				delivered->setWaitingTime(currTime - delivered->getPrepTime());
			}

			if (waitingVIPCargo->dequeue(delivered)) {
				VIPDeliveredCargo->enqueue(delivered);
				delivered->setDeliveryTime(currTime);
				delivered->setWaitingTime(currTime - delivered->getPrepTime());
			}
		}
				
		print(currTime);
	}
	//saveToFile();
}
