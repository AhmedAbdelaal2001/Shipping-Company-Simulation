#include "Company.h"
#include "Preparation.h"
#include "Promotion.h"
#include "Cancellation.h"
#include <fstream>

Company::Company() {
	

	UI input;
	
	string fileName = input.getFileName();

	ifstream inputFile(fileName);

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
		deliveredCargo = new Queue<Cargo*>;

	}
}

CrossLinkedList<Cargo*>* Company::getWaitingNormalCargo() const {
	return waitingNormalCargo;
}

Queue<Cargo*>* Company::getWaitingSpecialCargo() const {
	return waitingSpecialCargo;
}

PriorityQueue<Cargo*>* Company::getWaitingVIPCargo() const {
	return waitingVIPCargo;
}

Queue<Event*>* Company::getEventList() const {
	return EventList;
}

void Company::saveToFile() {
	
	ofstream outFile("Output.txt");
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
	outFile << "Auto-promoted Cargos: " << percentProm << "%" << endl;



}

bool Company::notTerminated() {
	return !EventList->isEmpty() || !waitingNormalCargo->isEmpty() || !waitingSpecialCargo->isEmpty() || !waitingVIPCargo->isEmpty();
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
				deliveredCargo->enqueue(delivered);
				delivered->setDeliveryTime(currTime);
				delivered->setWaitingTime(currTime - delivered->getPrepTime());
			}

			if (waitingSpecialCargo->dequeue(delivered)) {
				deliveredCargo->enqueue(delivered);
				delivered->setDeliveryTime(currTime);
				delivered->setWaitingTime(currTime - delivered->getPrepTime());
			}

			if (waitingVIPCargo->dequeue(delivered)) {
				deliveredCargo->enqueue(delivered);
				delivered->setDeliveryTime(currTime);
				delivered->setWaitingTime(currTime - delivered->getPrepTime());
			}
		}

	}
	saveToFile();
}
