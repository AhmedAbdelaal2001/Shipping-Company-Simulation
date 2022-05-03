#include "Company.h"
#include "Preparation.h"
#include "Promotion.h"
#include "Cancellation.h"
#include <fstream>

Company::Company() {


	in_out = new UI(this);

	readFromFile();

}

void Company::readFromFile() {
	in_out->printMessage("Enter input file name: ");
	string fileName = in_out->getFileName();

	ifstream inputFile(fileName);

	in_out->printMessage("Enter output file name: ");
	outFileName = in_out->getFileName();

	cout << "Enter mode: (Interactive, Step_By_Step, Silent)" << endl;
	in_out->getModefromUser();



	if (!inputFile.fail()) {

		int n_Count, s_Count, v_Count, n_Speed, s_Speed, v_Speed, n_Capacity, s_Capacity, v_Capacity, checkup, autoProm, MaxW, eventsCount, id, days, hours;
		Time n_CheckupD, s_CheckupD, v_CheckupD;
		char event_Type;
		Event* p_event;

		inputFile >> n_Count >> s_Count >> v_Count;

		inputFile >> n_Speed >> s_Speed >> v_Speed;

		inputFile >> n_Capacity >> s_Capacity >> v_Capacity;

		inputFile >> journeysBeforeCheckup;

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

		waitingNormalTrucks = new PriorityQueue<Truck*>(n_Count);
		waitingSpecialTrucks = new PriorityQueue<Truck*>(s_Count);
		waitingVIPTrucks = new PriorityQueue<Truck*>(v_Count);

		normalCheckupTrucks = new Queue<Truck*>;
		specialCheckupTrucks = new Queue<Truck*>;
		VIPCheckupTrucks = new Queue<Truck*>;

		movingTrucks = new PriorityQueue<Truck*>(n_Count + s_Count + v_Count);

		Truck* TruckPtr;
		for (int i = 0; i < n_Count; i++)
		{
			TruckPtr = new Truck('N', n_Capacity, n_CheckupD, n_Speed);
			waitingNormalTrucks->enqueue(TruckPtr);
		}
		for (int i = 0; i < s_Count; i++)
		{
			TruckPtr = new Truck('S', s_Capacity, s_CheckupD, s_Speed);
			waitingSpecialTrucks->enqueue(TruckPtr);
		}
		for (int i = 0; i < v_Count; i++)
		{
			TruckPtr = new Truck('V', v_Capacity, v_CheckupD, v_Speed);
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
	in_out->print(currTime, waitingNormalTrucks, waitingSpecialTrucks, waitingVIPTrucks, normalCheckupTrucks, specialCheckupTrucks, VIPCheckupTrucks, movingTrucks, waitingNormalCargo, waitingSpecialCargo, waitingVIPCargo, EventList, normalDeliveredCargo, specialDeliveredCargo, VIPDeliveredCargo, LoadingTrucks);
}

void Company::executeCurrEvents(Time currTime) {

	Event* frontEvent;

	while (EventList->peek(frontEvent) && currTime == frontEvent->getEventTime())
	{
		EventList->dequeue(frontEvent);
		frontEvent->Execute();

	}
}

void Company::assignVIP(Time currTime) {
	Truck* truckPtr = nullptr;
	Cargo* loading = nullptr;
	while (true) {

		if (waitingVIPTrucks->peek(truckPtr)) {}
		else if (waitingNormalTrucks->peek(truckPtr)) {}
		else if (waitingSpecialTrucks->peek(truckPtr)) {}
		else break;


		if (waitingVIPCargo->getCount() >= truckPtr->getCapacity())
		{
			switch (truckPtr->getType()) {
			case 'V':
				waitingVIPTrucks->dequeue(truckPtr);
				break;
			case 'N':
				waitingNormalTrucks->dequeue(truckPtr);
				break;
			case 'S':
				waitingSpecialTrucks->dequeue(truckPtr);
				break;
			}

			Time readyTime = currTime;
			for (int i = 0; i < truckPtr->getCapacity(); i++) {
				waitingVIPCargo->dequeue(loading);
				loading->setPriority(-1 * loading->getDistance());
				truckPtr->enqueueCargo(loading);
				readyTime = readyTime + loading->getLoadTime();
			}
			int priority = readyTime.getTotalHours();
			truckPtr->setPriority(priority);

			LoadingTrucks->enqueue(truckPtr);
		}
		else break;


	}
}

void Company::assignSpecial(Time currTime) {

	Truck* truckPtr = nullptr;
	Cargo* loading = nullptr;

	while (waitingSpecialTrucks->peek(truckPtr)) {

		if (waitingSpecialCargo->getCount() >= truckPtr->getCapacity()) {

			Time readyTime = currTime;
			waitingSpecialTrucks->dequeue(truckPtr);

			for (int i = 0; i < truckPtr->getCapacity(); i++) {
				waitingSpecialCargo->dequeue(loading);
				loading->setPriority(-1 * loading->getDistance());
				truckPtr->enqueueCargo(loading);
				readyTime = readyTime + loading->getLoadTime();
			}
			int priority = readyTime.getTotalHours();
			truckPtr->setPriority(priority);

			LoadingTrucks->enqueue(truckPtr);

		}
		else break;
	}
}

void Company::assignNormal(Time currTime) {
	Truck* truckPtr = nullptr;
	Cargo* loading = nullptr;
	while (true) {

		if (waitingNormalTrucks->peek(truckPtr)) {}
		else if (waitingVIPTrucks->peek(truckPtr)) {}
		else break;


		if (waitingNormalCargo->getCount() >= truckPtr->getCapacity())
		{
			switch (truckPtr->getType()) {
			case 'V':
				waitingVIPTrucks->dequeue(truckPtr);
				break;
			case 'N':
				waitingNormalTrucks->dequeue(truckPtr);
				break;
			}

			Time readyTime = currTime;
			for (int i = 0; i < truckPtr->getCapacity(); i++) {
				waitingNormalCargo->deleteFirst(loading);
				loading->setPriority(-1 * loading->getDistance());
				truckPtr->enqueueCargo(loading);
				readyTime = readyTime + loading->getLoadTime();
			}
			int priority = readyTime.getTotalHours();
			truckPtr->setPriority(priority);

			LoadingTrucks->enqueue(truckPtr);
		}
		else break;
	}
}

void Company::autoPromote(Time currTime) {


}


void Company::Simulate() {
	Time currTime(1, 1);
	Time startTime(1, 5), endTime(0, 23), readyTime;
	Truck* truckPtr = nullptr;
	Cargo* delivered, * loading;
	int counter = 0;


	if (in_out->getMode() == "Silent")
		in_out->printMessage("Silent Mode\nSimulations Starts...");


	while (notTerminated()) {


		executeCurrEvents(currTime);

		assignVIP(currTime);

		assignSpecial(currTime);

		assignNormal(currTime);

		autoPromote(currTime);


		if (in_out->getMode() != "Silent")
			printAll(currTime);

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


Company::~Company() {
	delete waitingNormalTrucks;
	waitingNormalTrucks = nullptr;
	delete waitingSpecialTrucks;
	waitingSpecialTrucks = nullptr;
	delete waitingVIPTrucks;
	waitingVIPTrucks = nullptr;

	delete normalCheckupTrucks;
	normalCheckupTrucks = nullptr;
	delete specialCheckupTrucks;
	specialCheckupTrucks = nullptr;
	delete VIPCheckupTrucks;
	VIPCheckupTrucks = nullptr;

	delete movingTrucks;
	movingTrucks = nullptr;

	delete waitingNormalCargo;
	waitingNormalCargo = nullptr;
	delete waitingSpecialCargo;
	waitingSpecialCargo = nullptr;
	delete waitingVIPCargo;
	waitingVIPCargo = nullptr;

	delete EventList;
	EventList = nullptr;

	delete normalDeliveredCargo;
	normalDeliveredCargo = nullptr;
	delete specialDeliveredCargo;
	specialDeliveredCargo = nullptr;
	delete VIPDeliveredCargo;
	VIPDeliveredCargo = nullptr;

	delete LoadingTrucks;
	LoadingTrucks = nullptr;

}
