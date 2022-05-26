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

	in_out->printMessage("Enter input file name, appended by .txt: ");
	string fileName = in_out->getFileName();

	ifstream inputFile(fileName);

	in_out->printMessage("Enter output file name, appended by .txt: ");
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
	int nTrucks, sTrucks, vTrucks, totalTrucksCount;
	float totalTruckUtilization, avgUtilization;
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
	outFile << "Auto-Promoted Cargos: " << (float)autoPromoted / (nCount + autoPromoted) * 100 << " %";
	outFile << "\nTrucks: " << totalTrucksCount << " [N: " << nTrucks << ", S: " << sTrucks << ", V: " << vTrucks << "]\n";
	outFile << "\nAvg Active Time = " << (float)Truck::getTotalActiveTime().getTotalHours() / (tSIM.getTotalHours() * totalTrucksCount) * 100; outFile << "%\n";
	
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
	
	avgUtilization = totalTruckUtilization / totalTrucksCount ;

	outFile << "Avg utilization = " << avgUtilization * 100 << "%";
	outFile << "\nFailure Percentage = " << (float)failedTrucks / totalTrucksCount * 100 << "%";
}

bool Company::notEndOfSimulation() {
	return	!EventList->isEmpty() || !waitingNormalCargo->isEmpty() || !waitingSpecialCargo->isEmpty() || !waitingVIPCargo->isEmpty() ||
		!LoadingTrucks->isEmpty() || !movingTrucks->isEmpty() || !normalCheckupTrucks->isEmpty() || !specialCheckupTrucks->isEmpty() ||
		!VIPCheckupTrucks->isEmpty() || !normalMaintenance->isEmpty() || !nightNormalMaintenance->isEmpty() || !specialMaintenance->isEmpty() ||
		!nightSpecialMaintenance->isEmpty() || !VIPMaintenance->isEmpty() || !nightVIPMaintenance->isEmpty();
}
//working hours are 5 pm-11 pm
bool Company::inWorkingHours(Time currTime) 
{
	return currTime.getHours() <= 23 && currTime.getHours() >= 5;
}

void Company::printAll(Time currTime) {
	
	Container<Cargo*>* cargoContainersArr[6] = { waitingNormalCargo , waitingSpecialCargo, waitingVIPCargo,
		                                         normalDeliveredCargo, specialDeliveredCargo, VIPDeliveredCargo };

	Container<Truck*>* truckContainersArr[17] = { LoadingTrucks, waitingNormalTrucks, normalNightTrucks, waitingSpecialTrucks, specialNightTrucks, waitingVIPTrucks, VIPNightTrucks,
												  movingTrucks, normalCheckupTrucks, specialCheckupTrucks, VIPCheckupTrucks,
												  normalMaintenance,nightNormalMaintenance, specialMaintenance, nightSpecialMaintenance, VIPMaintenance, nightVIPMaintenance };

	in_out->print(currTime, EventList, cargoContainersArr, truckContainersArr);
}
//Events at off hours are neglected
//Events that comes before working hours and  its load time finishes during the offhours are assinged to night Trucks.

void Company::executeCurrEvents(Time currTime) {

	if (!inWorkingHours(currTime)) return;

	Event* frontEvent;

	while (EventList->peek(frontEvent) && currTime >= frontEvent->getEventTime()) {
		EventList->dequeue(frontEvent);

		if (!(frontEvent->getEventTime() == currTime))
			frontEvent->setEventTime(currTime);

		frontEvent->Execute();
		delete frontEvent;
		frontEvent = nullptr;
	}
}


void Company::moveTruckToLoading(Container<Truck*>* truckContainer, Truck* truckPtr) {
	
	truckContainer->dequeue(truckPtr); // dequeue the truck at the head of pQ (lowest capacity)
	truckPtr->setPriorityToMoveTime(); // only One list for Loading (contains the 3 types of trucks)
	truckPtr->setCargoType();          // move time = currTime+ sum of load times of its cargos
	LoadingTrucks->enqueue(truckPtr);  // the least moveTime ->   will load quickly
	                                   // the highest movetime -> will load in long time
	                                   // Priority = MoveTime * -1 ->truck that have least moveTime Has higher Priority

}

void Company::loadCargo(Container<Cargo*>* cargoContainer, Truck* truckPtr, Time currTime) {
	
	Cargo* loading = nullptr;
	
	Time offSet(0, 5);
	Time endOfDay(0, 23);
	
	int remainingHours;

	if (truckPtr->isEmpty())
		truckPtr->setMoveTime(currTime);

	cargoContainer->dequeue(loading);
	loading->setPriorityToDistance();
	loading->setWaitingTime(currTime);

	remainingHours = endOfDay.getHours() - currTime.getHours();

	if (!truckPtr->WorksAtNight() && remainingHours < loading->getLoadTime().getTotalHours())	truckPtr->setMoveTime(truckPtr->getMoveTime() + offSet);
	
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
	
	// handling failed trucks that are returning to waiting
	if (truckPtr->ifFailed()) {
		truckPtr->resetFailureFlag();		// to indicate that it is no longer a failed truck
		truckPtr->setSpeed(truckPtr->getSpeed() * 3);		// boosting its speed after checkup was completed
	}

	// returning the truck to its approproate list
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

	// setting the time the truck will leave checkup
	truckPtr->setLeaveTime(currTime);

	// handling failure by returning cargos and returning its cargo to waiting
	if (truckPtr->ifFailed()) {
		failedTrucks++;

		Cargo* cargoPtr;
		while (truckPtr->dequeueCargo(cargoPtr)) {
			cargoPtr->computePriority();
			cargoPtr->setType('V');
			waitingVIPCargo->enqueue(cargoPtr);
		}
	}	

	// enqueueing in appropriate list
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

	// setting the time the truck will leave maintenance
	truckPtr->setLeaveTime(currTime);


	// enqueuing the truck in its approproate list and handling day/night trucks
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

	// making the trucks available after maintenance has finished
	do {

		if ((normalMaintenance->peek(nTruck) || nightNormalMaintenance->peek(nTruck)) && nTruck->getLeaveTime() == currTime) {		// checking both night and day lists for trucks that have finished maintenance
			normalMaintenance->peek(nTruck) ? normalMaintenance->dequeue(nTruck) : nightNormalMaintenance->dequeue(nTruck);
			nTruck->resetTotalMovedDistance();	
			moveTruckToWaiting(nTruck);		
		}
		else
			nTruck = nullptr;		// indicates that there aren't any normal trucks that have finished maintenance

		if ((specialMaintenance->peek(sTruck) || nightSpecialMaintenance->peek(sTruck)) && sTruck->getLeaveTime() == currTime) {
			specialMaintenance->peek(sTruck) ? specialMaintenance->dequeue(sTruck) : nightSpecialMaintenance->dequeue(sTruck);
			sTruck->resetTotalMovedDistance();
			moveTruckToWaiting(sTruck);
		}
		else
			sTruck = nullptr;


		if ((VIPMaintenance->peek(vTruck) || nightVIPMaintenance->peek(vTruck)) && vTruck->getLeaveTime() == currTime) {
			VIPMaintenance->peek(vTruck)? VIPMaintenance->dequeue(vTruck) : nightVIPMaintenance->dequeue(vTruck);
			vTruck->resetTotalMovedDistance();
			moveTruckToWaiting(vTruck);
		}
		else
			vTruck = nullptr;


	} while (nTruck || sTruck || vTruck);

}

void Company::returnFromCheckup(Time currTime) {

	Truck* nTruck, *sTruck, *vTruck;

	nTruck = sTruck = vTruck = nullptr;

	// returning trucks that have finished checkup to their appropriate lists
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

void Company::makeTrucksAvailable(Time currTime)
{
	returnFromCheckup(currTime);
	returnFromMaintenance(currTime);
}

bool Company::assignMaxWCargo(Container<Cargo*>* cargoContainer, Truck*& truckPtr, Container<Truck*>* truckContainer, Time currTime) {
	Cargo* loading = nullptr;

	//When uncommented, may result in an infinte loop.
	//if (cargoContainer->peek(loading) && loading->getType() == 'V') return false;

	while (cargoContainer->peek(loading) && loading->calcWait(currTime) >= maxW && !truckPtr->isFull()) {

		loadCargo(cargoContainer, truckPtr, currTime);

	}

	if (truckPtr->isEmpty()) return false;
	else {
		moveTruckToLoading(truckContainer, truckPtr);
		return true;
	}
}

// Calls all functions responsible for assigning and loading trucks, then autoPromotes if needed.
//
// currTime: The current time in the simulation.
void Company::startLoading(Time currTime)
{

	autoPromote(currTime);
	assignVIP(currTime, waitingVIPCargo);
	assignSpecial(currTime, waitingSpecialCargo);
	assignNormal(currTime, waitingNormalCargo);

}

// Picks the truck having the highest priority from the two truck containers provided. If called during off hours, the function will
// only consider the first truck container provided.
//
// currTime: currTime: The current time in the simulation.
// truckContainer1: The first truck container that we wish to look at when choosing the highest priority truck.
// truckContainer2: The second truck container that we wish to look at when choosing the highest priority truck.
// truckPtr: Should point to the truck having the highest priority at the end of the function's execution.
// index: will be 0 if we pick a truck from truckContainer1, and 1 if we pick a truck from truckContainer2
// 
// returns false if no truck is found, and true otherwise.
bool Company::HighestPriorityTruck(Time currTime, Container<Truck*>* truckContainer1, Container<Truck*>* truckContainer2, Truck*& truckPtr,
								   int& index)
{ // 
	if (!inWorkingHours(currTime)) {
		index = 0;
		return truckContainer1->peek(truckPtr);
	}

	Truck* truckPtr1;
	Truck* truckPtr2;

	if (truckContainer1->peek(truckPtr1) && truckContainer2->peek(truckPtr2)) {
		if (*truckPtr1 > truckPtr2) {
			truckPtr = truckPtr1;
			index = 0;
		}
		else {
			truckPtr = truckPtr2;
			index = 1;
		}

		return true;
	}
	else if (truckContainer1->peek(truckPtr1)) {
		truckPtr = truckPtr1;
		index = 0;
		return true;
	}
	else if (truckContainer2->peek(truckPtr2)) {
		truckPtr = truckPtr2;
		index = 1;
		return true;
	}

	return false;
}

// Assigns cargo, if possible, according to the assignment rule. Works for normal, special, and VIP cargo/trucks. Will be called during
// assignNormal, assignSpecial, and assignVIP.
// 
// cargoContainer: the container carrying the cargo that we wish to dequeue from.
// truckContainerArr: an array of truck containers, which contains all truck containers that we can dequeue from for the type of cargo
//					   carried in cargoContainer. The array is ordered according to the assignment rule.
// truckContainersNum: the number of elements in truckContainerArrr.
// currTime: currTime: The current time in the simulation.
// 
// returns true if it manages to assign cargo to any truck, and false otherwise.
bool Company::assignCargo(Container<Cargo*>* cargoContainer, Container<Truck*>** truckContainerArr, int truckContainersNum,
	Time currTime) {
	int index;
	Truck* truckPtr = nullptr;

	index = (inWorkingHours(currTime)) ? 0 : 1;

	for (int i = index; i < truckContainersNum; i += 2) {

		if (HighestPriorityTruck(currTime, truckContainerArr[i], truckContainerArr[i+1], truckPtr, index)) {

			if (cargoContainer->getCount() >= truckPtr->getCapacity()) {
				fillTruckWithCargo(truckPtr, truckContainerArr[i + index], cargoContainer, currTime);
				return true;
			}
			else {
				if (assignMaxWCargo(cargoContainer, truckPtr, truckContainerArr[i + index], currTime)) {
					return true;
				}
				return false;
			}
		}
	}

	return false;
}


// Responsible for assigning VIP cargo, if possible. Will be called during each timestep.
// 
// currTime: The current time in the simulation.
// VIPCargoContainer: The container carrying the VIP cargo that we wish to dequeue from.
void Company::assignVIP(Time currTime, Container<Cargo*>* VIPCargoContainer) {
	if (isLoadingVIP) return;

	Container<Truck*>* truckContainerArr[12] = { waitingVIPTrucks, VIPNightTrucks, waitingNormalTrucks, normalNightTrucks, 
												waitingSpecialTrucks, specialNightTrucks, VIPMaintenance, nightVIPMaintenance,
												normalMaintenance, nightNormalMaintenance, specialMaintenance, nightSpecialMaintenance };
	isLoadingVIP = assignCargo(VIPCargoContainer, truckContainerArr, 8, currTime);	
}
 
// Responsible for assigning special cargo, if possible. Will be called during each timestep.
// 
// currTime: The current time in the simulation.
// specialCargoContainer: The container carrying the special cargo that we wish to dequeue from.
void Company::assignSpecial(Time currTime, Container<Cargo*>* specialCargoContainer) {
	if (isLoadingSpecial) return;

	Container<Truck*>* truckContainerArr[4] = { waitingSpecialTrucks, specialNightTrucks, specialMaintenance, nightSpecialMaintenance };
	isLoadingSpecial = assignCargo(specialCargoContainer, truckContainerArr, 4, currTime);
}
 
// Responsible for assigning normal cargo, if possible. Will be called during each timestep.
// 
// currTime: The current time in the simulation.
// normalCargoContainer: The container carrying the normal cargo that we wish to dequeue from.
void Company::assignNormal(Time currTime, Container<Cargo*>* normalCargoContainer) {
	if (isLoadingNormal) return;

	Container<Truck*>* truckContainerArr[8] = { waitingNormalTrucks, normalNightTrucks,  waitingVIPTrucks, VIPNightTrucks, normalMaintenance, nightNormalMaintenance, VIPMaintenance, nightVIPMaintenance };

	isLoadingNormal = assignCargo(normalCargoContainer, truckContainerArr, 8, currTime);
}
//if a cargo waits than autoP days from its Preparation time , it should be promoted to VIP
void Company::autoPromote(Time currTime) {
	Cargo* promotedCargoPtr = nullptr;
	//while waiting normal list not empty and the cargo's AutoP time exceeds it's autoaP
	while (waitingNormalCargo->peek(promotedCargoPtr) && promotedCargoPtr->calcWait(currTime) >= autoP) {
		
		waitingNormalCargo->dequeue(promotedCargoPtr); //dequeue it from noemal list
		promotedCargoPtr->setType('V'); // change its type to VIP
		promotedCargoPtr->updatePriority(0); //set it's priority (no extra cost)
		waitingVIPCargo->enqueue(promotedCargoPtr);
		autoPromoted++;

	}
}

void Company::startDelivery(Time currTime) {
	Truck* truckPtr = nullptr;
	Cargo* headCargoPtr = nullptr;
	int newPriority;

	    // delivery starts when a truck has finished loading all its cargo and enqueued to loading trucks and it's move time == currTime .

	while (LoadingTrucks->peek(truckPtr) &&  currTime >= truckPtr->getMoveTime()) {		
		
		LoadingTrucks->dequeue(truckPtr);

		// identifying type of cargo the truck is carrying to allow another truck to start loading this type.
		
		if (truckPtr->containsNormal())
			isLoadingNormal = false;                  // used in Assin Normal
		else if (truckPtr->containsSpecial())         // used in Assin Special
			isLoadingSpecial = false;                 // used in Assin VIP
		else if (truckPtr->containsVIP())             // to check that Only One truck of it's type is being loaded.
			isLoadingVIP = false;

		// calculating initial truck moving priority

		truckPtr->setMovingPriority(currTime);        // The truck priority is set according to the distance left to deliver its first cargo.
		movingTrucks->enqueue(truckPtr);              // move it from loading to moving after setting its Priority.

	}
}

void Company::completeDelivery(Time currTime) {

	Truck* truckPtr;
	Cargo* deliveredCargo;


	while (movingTrucks->peek(truckPtr) && -1 * truckPtr->getPriority() == currTime.getTotalHours()) {			// checking if a truck has an event to execute (deliver a cargo/return to company)

		movingTrucks->dequeue(truckPtr);

		// delivering cargo and updating the delivery statistics 
		if (!truckPtr->ifFailed() && truckPtr->dequeueCargo(deliveredCargo)) {

			moveCargoToDelivered(deliveredCargo);

			// if truck is now empty or a failure has occured then its active time has ended and its total active time is incremented
			if (truckPtr->isEmpty() || truckPtr->deliveryFailure()) {

				truckPtr->incrementActiveTime(currTime);
			}

			// updating statistics
			truckPtr->deliveryStats(currTime, deliveredCargo);

			movingTrucks->enqueue(truckPtr);

		}
		// when a truck returns to the company a number of checks are made and returning statistics are updated
		else {

			truckPtr->returnStats(currTime);

			// returning the truck to its suitable list
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

		startLoading(currTime);

		startDelivery(currTime);

		completeDelivery(currTime);

		makeTrucksAvailable(currTime);


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

	delete normalNightTrucks;
	normalNightTrucks = nullptr;
	delete specialNightTrucks;
	specialNightTrucks = nullptr;
	delete VIPNightTrucks;
	VIPNightTrucks = nullptr;

	delete normalCheckupTrucks;
	normalCheckupTrucks = nullptr;
	delete specialCheckupTrucks;
	specialCheckupTrucks = nullptr;
	delete VIPCheckupTrucks;
	VIPCheckupTrucks = nullptr;

	delete normalMaintenance;
	normalMaintenance = nullptr;
	delete specialMaintenance;
	specialMaintenance = nullptr;
	delete VIPMaintenance;
	VIPMaintenance = nullptr;

	delete nightNormalMaintenance;
	nightNormalMaintenance = nullptr;
	delete nightSpecialMaintenance;
	nightSpecialMaintenance = nullptr;
	delete nightVIPMaintenance;
	nightVIPMaintenance = nullptr;

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
