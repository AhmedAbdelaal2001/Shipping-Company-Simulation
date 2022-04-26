#include "Company.h"
#include "Preparation.h"
#include "Promotion.h"
#include "Cancellation.h"
#include <fstream>

Company::Company() {
	

	in_out = new UI(this);
	
	in_out->printMessage("Enter input file name: ");
	string fileName = in_out->getFileName();

	ifstream inputFile(fileName);

	in_out->printMessage("Enter output file name: ");
	outFileName = in_out->getFileName();

	cout << "Enter mode: (Interactive, Step_By_Step, Silent)" << endl;
	in_out->getModefromFile();

	cAutoP = 0;

	if (!inputFile.fail()) {

		int n_Count, s_Count, v_Count;

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

		char event_Type;
		int id, days, hours;
		Event* p_event;

		for (int i = 0; i < eventsCount; i++) {
			inputFile >> event_Type;

			if (event_Type == 'R') {

				p_event = new Perparation(this);

				p_event->load(inputFile);

				EventList->enqueue(p_event);
			}
			else if (event_Type == 'P') {

				p_event = new Promotion(this);

				p_event->load(inputFile);

				EventList->enqueue(p_event);
			}
			else if (event_Type == 'X') {

				p_event = new Cancellation(this);

				p_event->load(inputFile);

				EventList->enqueue(p_event);
			}
		}



		waitingNormalCargo = new CrossLinkedList<Cargo*>(2 * n_Capacity);
		waitingSpecialCargo = new Queue<Cargo*>;
		waitingVIPCargo = new PriorityQueue<Cargo*>(2 * v_Capacity);

		normalDeliveredCargo = new Queue<Cargo*>;
		specialDeliveredCargo = new Queue<Cargo*>;
		VIPDeliveredCargo = new Queue<Cargo*>;
	
		waitingNormalTrucks = new PriorityQueue<Truck*>( n_Count);
		waitingSpecialTrucks = new PriorityQueue<Truck*>(s_Count);
		waitingVIPTrucks = new PriorityQueue<Truck*>(v_Count);
		CheckupTrucks = new Queue<Truck*>;
		movingTrucks = new PriorityQueue<Truck*>(n_Count + s_Count + v_Count);
		Truck* TruckPtr;
		for (int i = 0; i < n_Count; i++)
		{
			TruckPtr = new Truck('N', n_Capacity, checkup, n_Speed);
			waitingNormalTrucks->enqueue(TruckPtr);
		}
		for (int i = 0; i < s_Count; i++)
		{
			TruckPtr = new Truck('S', s_Capacity, checkup, s_Speed);
			waitingSpecialTrucks->enqueue(TruckPtr);
		}
		for (int i = 0; i < v_Count; i++)
		{
			TruckPtr = new Truck('V', v_Capacity, checkup, v_Speed);
			waitingVIPTrucks->enqueue(TruckPtr);
		}	
		LoadingTrucks = new PriorityQueue<Truck*>(n_Count + s_Count + v_Count);
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

bool Company::inWorkingHours(Time currTime)
{
	return currTime.getHours() <= 23 && currTime.getHours() >= 5;
}

void Company::printAll(Time currTime) {
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

	cout << endl << "------------------------------------------------------------" << endl; //TODO

	cout << LoadingTrucks->getCount() << " Loading Trucks: ";
	LoadingTrucks->printQueue();
	cout << endl << "------------------------------------------------------------" << endl;

	cout << movingTrucks->getCount() << " Moving Cargos: ";
	movingTrucks->printQueue();

	cout << endl << "------------------------------------------------------------" << endl;

	cout << CheckupTrucks->getCount() << " In-Checkup Trucks: ";
	CheckupTrucks->printQueue();
	cout << endl << "------------------------------------------------------------" << endl;


	cout << waitingNormalCargo->getCount() + waitingSpecialTrucks->getCount() + waitingVIPTrucks->getCount();
	cout << " Empty Trucks: ";
	cout << "["; waitingNormalTrucks->printQueue(); cout << "], ";
	cout << "("; waitingSpecialTrucks->printQueue(); cout << "), ";
	cout << "{"; waitingVIPTrucks->printQueue(); cout <<"}";

	cout << endl << "------------------------------------------------------------" << endl;





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

	cout << endl << "------------------------------------------------------------" << endl;

	cout << endl;

	

}

void Company::Simulate() {
	Time currTime(1, 1);
	Time startTime(1, 5), endTime(0, 23);
	Event* frontEvent;
	Cargo* delivered;
	int counter = 0;

	if (in_out->getMode() == "Silent") 
		in_out->printMessage("Silent Mode\nSimulations Starts...");


	while (notTerminated()) {

		
		while (EventList->peek(frontEvent) && currTime == frontEvent->getEventTime())
		{
			EventList->dequeue(frontEvent);
			frontEvent->Execute();

		}


		if (inWorkingHours(currTime) && counter % 5 == 0) {
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
		if (in_out->getMode() != "Silent")
			in_out->print(currTime);
			
		if (inWorkingHours(currTime))
			counter++;
		else
			counter = 0;

		++currTime;
	}

	if (in_out->getMode() == "Silent") {
		in_out->printMessage("Simulations ends, Output file created");
	}

	//saveToFile();
}
