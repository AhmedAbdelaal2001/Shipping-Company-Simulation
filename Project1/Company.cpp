#include "Company.h"
#include "Preparation.h"
#include "Promotion.h"
#include "Cancellation.h"
#include <fstream>

Company::Company() {

	in_out = new UI(this);
	isLoadingNormal = isLoadingSpecial = isLoadingVIP = false;
	autoPromoted = failedTrucks = 0;
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

		int truckCount, speed, capacity, checkup, autoProm, MaxW, eventsCount, id, days, hours, journeysBeforeCheckup, maintenanceD, maintenanceDistance;
		Time n_CheckupD, s_CheckupD, v_CheckupD, n_MaintenanceD, s_MaintenanceD, v_MaintenanceD;
		char type, shiftTime, event_Type;
		Event* p_event;

		inputFile >> truckCount;

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

		movingTrucks = new PriorityQueue<Truck*>(truckCount);

		LoadingTrucks = new PriorityQueue<Truck*>(3);

		VIPMaintenance = new MaintenanceTrucks;
		specialMaintenance = new MaintenanceTrucks;
		normalMaintenance = new MaintenanceTrucks;

		nightVIPMaintenance = new MaintenanceTrucks;
		nightSpecialMaintenance = new MaintenanceTrucks;
		nightNormalMaintenance = new MaintenanceTrucks;

		/*inputFile >> n_Speed >> s_Speed >> v_Speed;

		inputFile >> n_Capacity >> s_Capacity >> v_Capacity;*/

		inputFile >> journeysBeforeCheckup;

		inputFile >> checkup;
		n_CheckupD.setHours(checkup);

		inputFile >> checkup;
		s_CheckupD.setHours(checkup);

		inputFile >> checkup;
		v_CheckupD.setHours(checkup);

		inputFile >> maintenanceDistance;

		inputFile >> maintenanceD;
		n_MaintenanceD.setHours(maintenanceD);

		inputFile >> maintenanceD;
		s_MaintenanceD.setHours(maintenanceD);

		inputFile >> maintenanceD;
		v_MaintenanceD.setHours(maintenanceD);

		Truck* TruckPtr;
		for (int i = 0; i < truckCount; i++)
		{
			inputFile >> type >> speed >> capacity >> shiftTime;

			switch (type) {
			case 'N': 
				TruckPtr = new Truck(type, capacity, n_CheckupD, speed, journeysBeforeCheckup, shiftTime, n_MaintenanceD, maintenanceDistance);
				shiftTime == 'N'? normalNightTrucks->enqueue(TruckPtr) : waitingNormalTrucks->enqueue(TruckPtr); 
				break;
			case 'S': 
				TruckPtr = new Truck(type, capacity, s_CheckupD, speed, journeysBeforeCheckup, shiftTime, s_MaintenanceD, maintenanceDistance);
				shiftTime == 'N' ? specialNightTrucks->enqueue(TruckPtr) : waitingSpecialTrucks->enqueue(TruckPtr); 
				break;
			case 'V': 
				TruckPtr = new Truck(type, capacity, v_CheckupD, speed, journeysBeforeCheckup, shiftTime, v_MaintenanceD, maintenanceDistance);
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

Cargo* Company::firstDelivered(Cargo* nCargo, Cargo* sCargo, Cargo* vCargo) {

	Time minTime(INT_MAX);
	Cargo* firstOut = nullptr;

	if (nCargo && minTime >= nCargo->getDeliveryTime()) {
		firstOut = nCargo;
		minTime = nCargo->getDeliveryTime();
	}

	if (sCargo && minTime >= sCargo->getDeliveryTime()) {
		firstOut = sCargo;
		minTime = sCargo->getDeliveryTime();
	}

	if (vCargo && minTime >= vCargo->getDeliveryTime()) {
		firstOut = vCargo;
		minTime = vCargo->getDeliveryTime();
	}

	return firstOut;
}

void Company::saveToFile(Time tSIM) {
	int nCount, sCount, vCount, totalCargoCount;
	int nTrucks, sTrucks, vTrucks, totalTrucksCount, totalTruckUtilization, avgUtilization;
	Time totalWait, avgWait;
	Cargo* nCargo, * sCargo, * vCargo;
	nCargo = sCargo = vCargo = nullptr;
	Truck * nTruck, * sTruck, * vTruck;
	ofstream outFile(outFileName);
	
	outFile << "CDT\t\tID\t\tPT\t\tWT\t\tTID\n";

	nCount = normalDeliveredCargo->getCount();
	sCount = specialDeliveredCargo->getCount();
	vCount = VIPDeliveredCargo->getCount();
	totalCargoCount = nCount + sCount + vCount;

	nTrucks = waitingNormalTrucks->getCount() + normalNightTrucks->getCount();
	sTrucks = waitingSpecialTrucks->getCount() + specialNightTrucks->getCount();
	vTrucks = waitingVIPTrucks->getCount() + VIPNightTrucks->getCount();
	totalTrucksCount = nTrucks + sTrucks + vTrucks;

	do {
		if (normalDeliveredCargo->peek(nCargo)) {}
		else nCargo = nullptr;

		if (specialDeliveredCargo->peek(sCargo)) {}
		else sCargo = nullptr;

		if (VIPDeliveredCargo->peek(vCargo)) {}
		else vCargo = nullptr;


		Cargo* cargoPtr = firstDelivered(nCargo, sCargo, vCargo);

		if (cargoPtr) {
			switch (cargoPtr->getType()) {
			case 'N': normalDeliveredCargo->dequeue(cargoPtr); break;
			case 'S': specialDeliveredCargo->dequeue(cargoPtr); break;
			case 'V': VIPDeliveredCargo->dequeue(cargoPtr); break;
			}
			totalWait = totalWait + cargoPtr->getWaitingTime();
			outFile << cargoPtr->getDeliveryTime() << "\t\t" << cargoPtr->getId() << "\t\t" << cargoPtr->getPrepTime() << "\t\t" << cargoPtr->getWaitingTime() << "\t\t" << cargoPtr->getTruckID() << "\n";
		}
		// delete cargo
		delete cargoPtr;
		cargoPtr = nullptr;
	} while (nCargo || sCargo || vCargo);
	
	avgWait.setHours(totalWait.getTotalHours() / totalCargoCount);

	outFile << "\nCargos: " << totalCargoCount << " [N: " << nCount << ", S: " << sCount << ", V: " << vCount << "]\n";
	outFile << "Cargo Avg Wait = " << avgWait << "\n";
	outFile << "Auto-Promoted Cargos: " << (float)autoPromoted / nCount * 100 << " %";
	outFile << "\nTrucks: " << totalTrucksCount << " [N: " << nTrucks << ", S: " << sTrucks << ", V: " << vTrucks << "]\n";
	outFile << "\nAvg Active Time = " << (float)Truck::getTotalActiveTime().getTotalHours() / tSIM.getTotalHours() * 100; outFile << "%\n";
	
	totalTruckUtilization = 0;
	
	do {
		if (waitingNormalTrucks->dequeue(nTruck)) {
			totalTruckUtilization += nTruck->calcUtilization(tSIM);
			delete nTruck;
			nTruck = waitingNormalTrucks->peek(nTruck) ? nTruck : nullptr;
		}
		
		
		if (waitingSpecialTrucks->dequeue(sTruck)) {
			totalTruckUtilization += sTruck->calcUtilization(tSIM);
			delete sTruck;
			sTruck = waitingSpecialTrucks->peek(sTruck) ? sTruck : nullptr;
		}
	

		if (waitingVIPTrucks->dequeue(vTruck)) {
			totalTruckUtilization += vTruck->calcUtilization(tSIM);
			delete vTruck;
			vTruck = waitingVIPTrucks->peek(vTruck) ? vTruck : nullptr;
		}
		

	} while (nTruck || sTruck || vTruck);
	
	avgUtilization = totalTruckUtilization / totalTrucksCount;

	outFile << "Avg utilization = " << avgUtilization;
}

bool Company::notEndOfSimulation() {
	return	!EventList->isEmpty() || !waitingNormalCargo->isEmpty() || !waitingSpecialCargo->isEmpty() || !waitingVIPCargo->isEmpty() ||
		!LoadingTrucks->isEmpty() || !movingTrucks->isEmpty() || !normalCheckupTrucks->isEmpty() || !specialCheckupTrucks->isEmpty() ||
		!VIPCheckupTrucks->isEmpty() || !normalMaintenance->isEmpty() || !nightNormalMaintenance->isEmpty() || !specialMaintenance->isEmpty() ||
		!nightSpecialMaintenance->isEmpty() || !VIPMaintenance->isEmpty() || !nightVIPMaintenance->isEmpty();
}

bool Company::inWorkingHours(Time currTime)
{
	return currTime.getHours() <= 23 && currTime.getHours() >= 5;
}

void Company::printAll(Time currTime) {
	in_out->print(currTime, waitingNormalTrucks, normalNightTrucks, waitingSpecialTrucks, specialNightTrucks, waitingVIPTrucks, 
		          VIPNightTrucks, normalCheckupTrucks, specialCheckupTrucks, VIPCheckupTrucks, movingTrucks, waitingNormalCargo, 
				  waitingSpecialCargo, waitingVIPCargo, EventList, normalDeliveredCargo, specialDeliveredCargo, VIPDeliveredCargo,
		          LoadingTrucks, normalMaintenance, specialMaintenance, VIPMaintenance, nightVIPMaintenance, nightSpecialMaintenance,
		          nightNormalMaintenance);
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
	truckPtr->setCargoType();
	LoadingTrucks->enqueue(truckPtr);

}

void Company::loadCargo(Container<Cargo*>* cargoContainer, Truck* truckPtr, Time currTime) {
	Cargo* loading = nullptr;
	
	if (truckPtr->isEmpty())
		truckPtr->setMoveTime(currTime);

	cargoContainer->dequeue(loading);
	loading->setPriorityToDistance();
	loading->setWaitingTime(currTime);
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
	
	if (truckPtr->ifFailed()) {
		truckPtr->resetFailureFlag();
		truckPtr->setSpeed(truckPtr->getSpeed() * 3);
	}

	switch (truckPtr->getType()) {

	case 'N':
		truckPtr->WorksAtNight()? normalNightTrucks->enqueue(truckPtr) : waitingNormalTrucks->enqueue(truckPtr);
		break;

	case 'S':
		truckPtr->WorksAtNight() ? specialNightTrucks->enqueue(truckPtr) : waitingSpecialTrucks->enqueue(truckPtr);
		break;

	case 'V':
		truckPtr->WorksAtNight() ? VIPNightTrucks->enqueue(truckPtr) : waitingVIPTrucks->enqueue(truckPtr);
		break;
	}
}

void Company::moveToCheckup(Truck* truckPtr, Time currTime) {

	truckPtr->setLeaveTime(currTime);

	if (truckPtr->ifFailed()) {
		failedTrucks++;

		Cargo* cargoPtr;
		while (truckPtr->dequeueCargo(cargoPtr)) {
			cargoPtr->computePriority();
			cargoPtr->setType('V');
			waitingVIPCargo->enqueue(cargoPtr);
		}
	}	

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

void Company::moveToMaintenance(Truck* truckPtr, Time currTime)
{
	truckPtr->setLeaveTime(currTime);

	switch (truckPtr->getType()) {

	case 'N':
		truckPtr->WorksAtNight() ? nightNormalMaintenance->enqueue(truckPtr) : normalMaintenance->enqueue(truckPtr);
		break;

	case 'S':
		truckPtr->WorksAtNight() ? nightSpecialMaintenance->enqueue(truckPtr) : specialMaintenance->enqueue(truckPtr);
		break;

	case 'V':
		truckPtr->WorksAtNight() ? nightVIPMaintenance->enqueue(truckPtr) : VIPMaintenance->enqueue(truckPtr);
		break;
	}
}

void Company::returnFromMaintenance(Time currTime)
{
	Truck* nTruck, * sTruck, * vTruck;

	nTruck = sTruck = vTruck = nullptr;

	do {

		if ((normalMaintenance->peek(nTruck) || nightNormalMaintenance->peek(nTruck)) && nTruck->getLeaveTime() == currTime) {
			normalMaintenance->peek(nTruck) ? normalMaintenance->dequeue(nTruck) : nightNormalMaintenance->dequeue(nTruck);
			nTruck->resetTotalMovedDistance();
			moveTruckToWaiting(nTruck);
		}
		else
			nTruck = nullptr;

		if ((specialMaintenance->peek(sTruck) || nightSpecialMaintenance->peek(sTruck)) && sTruck->getLeaveTime() == currTime) {
			specialMaintenance->peek(sTruck) ? specialMaintenance->dequeue(sTruck) : nightSpecialMaintenance->dequeue(sTruck);
			sTruck->resetTotalMovedDistance();
			moveTruckToWaiting(sTruck);
		}
		else
			sTruck = nullptr;


		if ((VIPMaintenance->peek(vTruck) || nightVIPMaintenance->peek(vTruck)) && vTruck->getLeaveTime() == currTime) {
			VIPMaintenance->peek(vTruck)? VIPMaintenance->dequeue(vTruck) : nightVIPMaintenance->peek(vTruck);
			vTruck->resetTotalMovedDistance();
			moveTruckToWaiting(vTruck);
		}
		else
			vTruck = nullptr;


	} while (nTruck || sTruck || vTruck);

	/*nTruck = sTruck = vTruck = nullptr;

	do {

		if (nightNormalMaintenance->peek(nTruck) && nTruck->getLeaveTime() == currTime) {
			nTruck->resetTotalMovedDistance();
			nightNormalMaintenance->dequeue(nTruck);
			moveTruckToWaiting(nTruck);
		}
		else
			nTruck = nullptr;

		if (nightSpecialMaintenance->peek(sTruck) && sTruck->getLeaveTime() == currTime) {
			sTruck->resetTotalMovedDistance();
			nightSpecialMaintenance->dequeue(sTruck);
			moveTruckToWaiting(sTruck);
		}
		else
			sTruck = nullptr;


		if (nightVIPMaintenance->peek(vTruck) && vTruck->getLeaveTime() == currTime) {
			vTruck->resetTotalMovedDistance();
			nightVIPMaintenance->dequeue(vTruck);
			moveTruckToWaiting(vTruck);
		}
		else
			vTruck = nullptr;


	} while (nTruck || sTruck || vTruck);*/
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

	Container<Truck*>* truckContainerArr[12] = { waitingVIPTrucks, VIPNightTrucks, waitingNormalTrucks, normalNightTrucks, 
												waitingSpecialTrucks, specialNightTrucks, VIPMaintenance, nightVIPMaintenance,
												normalMaintenance, nightNormalMaintenance, specialMaintenance, nightSpecialMaintenance };
	isLoadingVIP = assignCargo(cargoContainer, truckContainerArr, 8, currTime);	
}

void Company::assignSpecial(Time currTime, Container<Cargo*>* cargoContainer) {
	if (isLoadingSpecial) return;

	Container<Truck*>* truckContainerArr[4] = { waitingSpecialTrucks, specialNightTrucks, specialMaintenance, nightSpecialMaintenance };
	isLoadingSpecial = assignCargo(cargoContainer, truckContainerArr, 4, currTime);
}

void Company::assignNormal(Time currTime, Container<Cargo*>* cargoContainer) {
	if (isLoadingNormal) return;

	Container<Truck*>* truckContainerArr[8] = { waitingNormalTrucks, normalNightTrucks,  waitingVIPTrucks, VIPNightTrucks, normalMaintenance, nightNormalMaintenance, VIPMaintenance, nightVIPMaintenance };

	isLoadingNormal = assignCargo(cargoContainer, truckContainerArr, 8, currTime);
}

void Company::autoPromote(Time currTime) {
	Cargo* promotedCargoPtr = nullptr;

	while (waitingNormalCargo->peek(promotedCargoPtr) && promotedCargoPtr->calcWait(currTime) >= autoP) {
		
		waitingNormalCargo->dequeue(promotedCargoPtr);
		promotedCargoPtr->setType('V');
		promotedCargoPtr->updatePriority(0);
		waitingVIPCargo->enqueue(promotedCargoPtr);
		autoPromoted++;

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
	int randomNum;

	

	while (movingTrucks->peek(truckPtr) && -1 * truckPtr->getPriority() == currTime.getTotalHours()) {

		movingTrucks->dequeue(truckPtr);

		if (!truckPtr->ifFailed() && truckPtr->dequeueCargo(deliveredCargo)) {

			moveCargoToDelivered(deliveredCargo);

			if (truckPtr->isEmpty() || truckPtr->deliveryFailure()) {

				truckPtr->incrementActiveTime(currTime);
			}

			truckPtr->deliveryStats(currTime, deliveredCargo);

			movingTrucks->enqueue(truckPtr);

		}
		else {

			truckPtr->returnStats(currTime);

			if (truckPtr->ifFailed() || truckPtr->needsCheckup())
				moveToCheckup(truckPtr, currTime);
			else if (truckPtr->needsMaintenance())
				moveToMaintenance(truckPtr, currTime);
			else
				moveTruckToWaiting(truckPtr);
		}
	}
}

void Company::Simulate() {
	Time currTime(1, 1);

	if (in_out->getMode() == "Silent")
		in_out->printMessage("Silent Mode\nSimulations Starts...");


	while (notEndOfSimulation()) {

		
		executeCurrEvents(currTime);

		assignVIP(currTime, waitingVIPCargo);
		assignSpecial(currTime, waitingSpecialCargo);
		assignNormal(currTime, waitingNormalCargo);
			
		autoPromote(currTime);

		startDelivery(currTime);

		completeDelivery(currTime);

		returnFromCheckup(currTime);

		returnFromMaintenance(currTime);


		if (in_out->getMode() != "Silent")
			printAll(currTime);

		++currTime;
	}

	if (in_out->getMode() == "Silent") {
		in_out->printMessage("Simulations ends, Output file created");
	}

	saveToFile(currTime);
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
