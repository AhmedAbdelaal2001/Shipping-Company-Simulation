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

				p_event = new Preparation(this);

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
	return !EventList->isEmpty() || !waitingNormalCargo->isEmpty() || !waitingSpecialCargo->isEmpty() || !waitingVIPCargo->isEmpty() ||
		!LoadingTrucks->isEmpty();
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


void Company::moveTruckToLoading(Container<Truck*>* truckContainer, Truck* truckPtr) {
	
	truckContainer->dequeue(truckPtr);
	LoadingTrucks->enqueue(truckPtr);

}

void Company::loadCargo(Container<Cargo*>* cargoContainer, Truck* truckPtr) {
	Cargo* loading = nullptr;

	cargoContainer->dequeue(loading);
	loading->setPriority(-1 * loading->getDistance());
	truckPtr->enqueueCargo(loading);
	truckPtr->updatePriority(-1 * loading->getLoadTime());
}

void Company::fillTruckWithCargo(Truck* truckPtr, Container<Truck*>* truckContainer, Container<Cargo*>* cargoContainer,
	int newPriority) {
	
	truckPtr->setPriority(newPriority);

	for (int i = 0; i < truckPtr->getCapacity(); i++) {
		loadCargo(cargoContainer, truckPtr);
	}
	
	moveTruckToLoading(truckContainer, truckPtr);
}

void Company::assignMaxWCargo(Container<Cargo*>* cargoContainer, Truck*& truckPtr, Container<Truck*>* truckContainer, Time currTime,
	int newPriority) {
	Cargo* loading = nullptr;

	

	while (cargoContainer->peek(loading))
		if (loading->calcWait(currTime) >= maxW) {
			truckPtr->setPriority(newPriority);
			if (truckPtr->isFull()) {
				moveTruckToLoading(truckContainer, truckPtr);
				if (!truckContainer->peek(truckPtr)) {
					truckPtr = nullptr;
					break;
				}
			}
			loadCargo(cargoContainer, truckPtr);
		}
		else break;

	if (truckPtr)
		if (!truckPtr->isEmpty())
			moveTruckToLoading(truckContainer, truckPtr);

		truckContainer->peek(truckPtr);

		while (cargoContainer->getCount() >= truckPtr->getCapacity()) {
			fillTruckWithCargo(truckPtr, truckContainer, cargoContainer, newPriority);
			truckContainer->peek(truckPtr);
		}

}


void Company::assignCargo(Container<Cargo*>* cargoContainer, Container<Truck*>** truckContainerArr, int truckContainersNum,
	Time currTime) {
	
	Truck* truckPtr = nullptr;
	int newPriority = -1 * currTime.getTotalHours();

	for (int i = 0; i < truckContainersNum; i++) {
		while (truckContainerArr[i]->peek(truckPtr)) {

			if (cargoContainer->getCount() >= truckPtr->getCapacity()) {
				fillTruckWithCargo(truckPtr, truckContainerArr[i], cargoContainer, newPriority);
			}
			else {
				assignMaxWCargo(cargoContainer, truckPtr, truckContainerArr[i], currTime, newPriority);
				
				if (!truckPtr) break;
				if (truckContainerArr[i]->peek(truckPtr))
					return;

				break;
			}
		}
	}
}

void Company::assignVIP(Time currTime, Container<Cargo*>* cargoContainer) {
	Container<Truck*>* truckContainerArr[3] = { waitingVIPTrucks, waitingNormalTrucks, waitingSpecialTrucks };
	assignCargo(cargoContainer, truckContainerArr, 3, currTime);
}

void Company::assignSpecial(Time currTime, Container<Cargo*>* cargoContainer) {

	Container<Truck*>* truckContainerArr[1] = { waitingSpecialTrucks };
	assignCargo(cargoContainer, truckContainerArr, 1, currTime);

}

void Company::assignNormal(Time currTime, Container<Cargo*>* cargoContainer) {
	Container<Truck*>* truckContainerArr[2] = { waitingNormalTrucks, waitingVIPTrucks };
	assignCargo(cargoContainer, truckContainerArr, 2, currTime);
}

void Company::autoPromote(Time currTime) {
	Cargo* promotedCargoPtr = nullptr;
	
	if (!waitingNormalCargo->peek(promotedCargoPtr))
		return;

	while (promotedCargoPtr->calcWait(currTime) >= autoP) {
		
		waitingNormalCargo->dequeue(promotedCargoPtr);
		promotedCargoPtr->setType('V');
		waitingVIPCargo->enqueue(promotedCargoPtr);

		if (!waitingNormalCargo->peek(promotedCargoPtr))
			return;
	}
}

void Company::startDelivery(Time currTime) {
	Truck* truckPtr = nullptr;
	Cargo* headCargoPtr = nullptr;
	int newPriority;

	while (LoadingTrucks->peek(truckPtr) && truckPtr->getMoveTime() == currTime) {
		
		LoadingTrucks->dequeue(truckPtr);
		newPriority = truckPtr->calcMovingPriority(currTime);
		truckPtr->setPriority(newPriority);
		movingTrucks->enqueue(truckPtr);

	}
}



void Company::Simulate() {
	Time currTime(1, 1);

	if (in_out->getMode() == "Silent")
		in_out->printMessage("Silent Mode\nSimulations Starts...");


	while (notTerminated()) {

			
		executeCurrEvents(currTime);

		assignVIP(currTime, waitingVIPCargo);
		assignSpecial(currTime, waitingSpecialCargo);
		assignNormal(currTime, waitingNormalCargo);


		startDelivery(currTime);

		autoPromote(currTime);

		if (in_out->getMode() != "Silent")
			printAll(currTime);

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
