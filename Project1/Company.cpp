#include "Company.h"
#include "Preparation.h"
#include "Promotion.h"
#include "Cancellation.h"
#include <fstream>

Company::Company() {


	in_out = new UI(this);
	isLoadingNormal = isLoadingSpecial = isLoadingVIP = false;
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

		int count, speed, capacity, checkup, autoProm, MaxW, eventsCount, id, days, hours, journeysBeforeCheckup;
		Time n_CheckupD, s_CheckupD, v_CheckupD;
		char type, shiftTime, event_Type;
		Event* p_event;

		inputFile >> count;

		waitingNormalCargo = new CrossLinkedList<Cargo*>;
		waitingSpecialCargo = new Queue<Cargo*>;
		waitingVIPCargo = new PriorityQueue<Cargo*>;

		normalDeliveredCargo = new Queue<Cargo*>;
		specialDeliveredCargo = new Queue<Cargo*>;
		VIPDeliveredCargo = new Queue<Cargo*>;

		waitingNormalTrucks = new PriorityQueue<Truck*>;
		waitingSpecialTrucks = new PriorityQueue<Truck*>;
		waitingVIPTrucks = new PriorityQueue<Truck*>;

		normalCheckupTrucks = new Queue<Truck*>;
		specialCheckupTrucks = new Queue<Truck*>;
		VIPCheckupTrucks = new Queue<Truck*>;

		normalNightTrucks = new PriorityQueue<Truck*>;
		specialNightTrucks = new PriorityQueue<Truck*>;
		VIPNightTrucks = new PriorityQueue<Truck*>;

		movingTrucks = new PriorityQueue<Truck*>(count);

		LoadingTrucks = new PriorityQueue<Truck*>(3);

		/*inputFile >> n_Speed >> s_Speed >> v_Speed;

		inputFile >> n_Capacity >> s_Capacity >> v_Capacity;*/

		inputFile >> journeysBeforeCheckup;

		inputFile >> checkup;
		n_CheckupD.setHours(checkup);

		inputFile >> checkup;
		s_CheckupD.setHours(checkup);

		inputFile >> checkup;
		v_CheckupD.setHours(checkup);

		Truck* TruckPtr;
		for (int i = 0; i < count; i++)
		{
			inputFile >> type >> speed >> capacity >> shiftTime;

			switch (type) {
			case 'N': 
				TruckPtr = new Truck(type, capacity, n_CheckupD, speed, journeysBeforeCheckup, shiftTime);
				shiftTime == 'N'? normalNightTrucks->enqueue(TruckPtr) : waitingNormalTrucks->enqueue(TruckPtr); 
				break;
			case 'S': 
				TruckPtr = new Truck(type, capacity, s_CheckupD, speed, journeysBeforeCheckup, shiftTime);
				shiftTime == 'N' ? specialNightTrucks->enqueue(TruckPtr) : waitingSpecialTrucks->enqueue(TruckPtr); 
				break;
			case 'V': 
				TruckPtr = new Truck(type, capacity, v_CheckupD, speed, journeysBeforeCheckup, shiftTime);
				shiftTime == 'N' ? VIPNightTrucks->enqueue(TruckPtr) : waitingVIPTrucks->enqueue(TruckPtr); 
				break;
			}

		}
		/*for (int i = 0; i < s_Count; i++)
		{

			TruckPtr = new Truck('S', s_Capacity, s_CheckupD, s_Speed, journeysBeforeCheckup);
			waitingSpecialTrucks->enqueue(TruckPtr);
		}
		for (int i = 0; i < v_Count; i++)
		{
			TruckPtr = new Truck('V', v_Capacity, v_CheckupD, v_Speed, journeysBeforeCheckup);
			waitingVIPTrucks->enqueue(TruckPtr);
		}*/


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
		!LoadingTrucks->isEmpty() || !movingTrucks->isEmpty() || !normalCheckupTrucks->isEmpty() || !specialCheckupTrucks->isEmpty() || !VIPCheckupTrucks->isEmpty();
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

	while (EventList->peek(frontEvent) && currTime == frontEvent->getEventTime()) {
		EventList->dequeue(frontEvent);
		frontEvent->Execute();
	}
}


void Company::moveTruckToLoading(Container<Truck*>* truckContainer, Truck* truckPtr) {
	
	truckContainer->dequeue(truckPtr);
	truckPtr->setPriorityToMoveTime();
	LoadingTrucks->enqueue(truckPtr);

}

void Company::loadCargo(Container<Cargo*>* cargoContainer, Truck* truckPtr, Time currTime) {
	Cargo* loading = nullptr;
	
	if (truckPtr->isEmpty())
		truckPtr->setMoveTime(currTime);

	cargoContainer->dequeue(loading);
	loading->setPriorityToDistance();
	truckPtr->enqueueCargo(loading);
}

void Company::moveCargoToDelivered(Cargo* deliveredCargo) {

	switch (deliveredCargo->getType()) {

	case 'N':
		normalDeliveredCargo->enqueue(deliveredCargo);
		break;

	case 'S':
		specialDeliveredCargo->enqueue(deliveredCargo);
		break;

	case 'V':
		VIPDeliveredCargo->enqueue(deliveredCargo);
		break;
	}

}


void Company::fillTruckWithCargo(Truck* truckPtr, Container<Truck*>* truckContainer, Container<Cargo*>* cargoContainer,
	Time currTime) {

	for (int i = 0; i < truckPtr->getCapacity(); i++) {
		loadCargo(cargoContainer, truckPtr, currTime);
	}
	
	moveTruckToLoading(truckContainer, truckPtr);
}

void Company::moveTruckToWaiting(Truck* truckPtr) {
	
	switch (truckPtr->getType()) {

	case 'N':
		waitingNormalTrucks->enqueue(truckPtr);
		break;

	case 'S':
		waitingSpecialTrucks->enqueue(truckPtr);
		break;

	case 'V':
		waitingVIPTrucks->enqueue(truckPtr);
		break;
	}
}

void Company::moveToCheckup(Truck* truckPtr, Time currTime) {

	truckPtr->setLeaveTime(currTime);

	switch (truckPtr->getType()) {

	case 'N':
		normalCheckupTrucks->enqueue(truckPtr);
		break;

	case 'S':
		specialCheckupTrucks->enqueue(truckPtr);
		break;

	case 'V':
		VIPCheckupTrucks->enqueue(truckPtr);
		break;
	}
}

void Company::returnFromCheckup(Time currTime) {

	Truck* nTruck, *sTruck, *vTruck;

	nTruck = sTruck = vTruck = nullptr;

	do {
		
		if (normalCheckupTrucks->peek(nTruck) && nTruck->getLeaveTime() == currTime) {
			normalCheckupTrucks->dequeue(nTruck);
			moveTruckToWaiting(nTruck);
		}
		else
			nTruck = nullptr;

		if (specialCheckupTrucks->peek(sTruck) && sTruck->getLeaveTime() == currTime) {
			specialCheckupTrucks->dequeue(sTruck);
			moveTruckToWaiting(sTruck);
		}
		else
			sTruck = nullptr;


		if (VIPCheckupTrucks->peek(vTruck) && vTruck->getLeaveTime() == currTime) {
			VIPCheckupTrucks->dequeue(vTruck);
			moveTruckToWaiting(vTruck);
		}
		else
			vTruck = nullptr;


	} while (nTruck || sTruck || vTruck);

}




void Company::assignMaxWCargo(Container<Cargo*>* cargoContainer, Truck*& truckPtr, Container<Truck*>* truckContainer, Time currTime) {
	Cargo* loading = nullptr;

	if (cargoContainer->peek(loading) && loading->getType() == 'V') return;

	while (cargoContainer->peek(loading) && loading->calcWait(currTime) >= maxW && !truckPtr->isFull()) {
	/*	if (truckPtr->isFull()) {
			moveTruckToLoading(truckContainer, truckPtr);
			if (!truckContainer->peek(truckPtr)) {
				truckPtr = nullptr;
				break;
			}
		}*/
		
		loadCargo(cargoContainer, truckPtr, currTime);
	
	}

	/*if (!truckPtr->isEmpty()) {

		moveTruckToLoading(truckContainer, truckPtr);
	}*/

	/*while (truckContainer->peek(truckPtr) && cargoContainer->getCount() >= truckPtr->getCapacity()) {
		fillTruckWithCargo(truckPtr, truckContainer, cargoContainer, currTime);
	}*/

}


bool Company::assignCargo(Container<Cargo*>* cargoContainer, Container<Truck*>** truckContainerArr, int truckContainersNum,
	Time currTime) {
	int startIndex, increment;
	
	Truck* truckPtr = nullptr;

	if (inWorkingHours(currTime)) {
		startIndex = 0; increment = 1;
	}
	else {
		startIndex = 1; increment = 2;
	}

	for (int i = startIndex; i < truckContainersNum; i+= increment) {
		if (truckContainerArr[i]->peek(truckPtr)) {

			if (cargoContainer->getCount() >= truckPtr->getCapacity()) {
				fillTruckWithCargo(truckPtr, truckContainerArr[i], cargoContainer, currTime);
				return true;
			}
			else {
				assignMaxWCargo(cargoContainer, truckPtr, truckContainerArr[i], currTime);
				
				if (!truckPtr->isEmpty()) {
					moveTruckToLoading(truckContainerArr[i], truckPtr);
					return true;
				}

				return false;
				/*if (truckContainerArr[i]->peek(truckPtr))
					return;*/
			}
		}
	}

	return false;
}

void Company::assignVIP(Time currTime, Container<Cargo*>* cargoContainer) {
	if (isLoadingVIP) return;

	Container<Truck*>* truckContainerArr[6] = { waitingVIPTrucks, VIPNightTrucks, waitingNormalTrucks, normalNightTrucks, waitingSpecialTrucks, specialNightTrucks };
	isLoadingVIP = assignCargo(cargoContainer, truckContainerArr, 6, currTime);	
}

void Company::assignSpecial(Time currTime, Container<Cargo*>* cargoContainer) {
	if (isLoadingSpecial) return;

	Container<Truck*>* truckContainerArr[2] = { waitingSpecialTrucks, specialNightTrucks };
	isLoadingSpecial = assignCargo(cargoContainer, truckContainerArr, 2, currTime);
}

void Company::assignNormal(Time currTime, Container<Cargo*>* cargoContainer) {
	if (isLoadingNormal) return;

	Container<Truck*>* truckContainerArr[4] = { waitingNormalTrucks, normalNightTrucks, waitingVIPTrucks, VIPNightTrucks };

	isLoadingNormal = assignCargo(cargoContainer, truckContainerArr, 4, currTime);
}

void Company::autoPromote(Time currTime) {
	Cargo* promotedCargoPtr = nullptr;

	while (waitingNormalCargo->peek(promotedCargoPtr) && promotedCargoPtr->calcWait(currTime) >= autoP) {
		
		waitingNormalCargo->dequeue(promotedCargoPtr);
		promotedCargoPtr->setType('V');
		waitingVIPCargo->enqueue(promotedCargoPtr);

	}
}

void Company::startDelivery(Time currTime) {
	Truck* truckPtr = nullptr;
	Cargo* headCargoPtr = nullptr;
	int newPriority;

	while (LoadingTrucks->peek(truckPtr) &&  currTime >= truckPtr->getMoveTime()) {
		
		LoadingTrucks->dequeue(truckPtr);

		if (truckPtr->containsNormal())
			isLoadingNormal = false;
		else if (truckPtr->containsSpecial())
			isLoadingSpecial = false;
		else if (truckPtr->containsVIP())
			isLoadingVIP = false;

		truckPtr->setMovingPriority(currTime);
		movingTrucks->enqueue(truckPtr);

	}
}

void Company::completeDelivery(Time currTime) {

	Truck* truckPtr;
	Cargo* deliveredCargo;

	while (movingTrucks->peek(truckPtr) && -1 * truckPtr->getPriority() == currTime.getTotalHours()) {

		movingTrucks->dequeue(truckPtr);

		if (truckPtr->dequeueCargo(deliveredCargo)) {

			moveCargoToDelivered(deliveredCargo);

			truckPtr->deliveryStats(currTime, deliveredCargo);

			movingTrucks->enqueue(truckPtr);

			if (truckPtr->isEmpty()) {

				truckPtr->incrementActiveTime(currTime);

			}
		}
		else {

			truckPtr->returnStats(currTime);

			if (truckPtr->needsCheckup())
				moveToCheckup(truckPtr, currTime);
			else
				moveTruckToWaiting(truckPtr);
		}
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
			
		autoPromote(currTime);

		startDelivery(currTime);
		

		completeDelivery(currTime);

		returnFromCheckup(currTime);


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

	delete normalNightTrucks;
	normalNightTrucks = nullptr;

	delete specialNightTrucks;
	specialNightTrucks = nullptr;

	delete VIPNightTrucks;
	VIPNightTrucks = nullptr;

}
