#include "MaintenanceTrucks.h"

bool MaintenanceTrucks::dequeue(Truck* truckPtr)
{
    bool dequeued = PriorityQueue<Truck*>::dequeue(truckPtr);
    if (dequeued && truckPtr->needsMaintenance())
        truckPtr->setSpeed(truckPtr->getSpeed() / 2);
    
    return dequeued;
}
