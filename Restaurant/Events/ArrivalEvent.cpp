#include "ArrivalEvent.h"
#include "..\Rest\Restaurant.h"


ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType, REGION reg):Event(eTime, oID)
{
	OrdType = oType;
	OrdRegion = reg;
}

ArrivalEvent::ArrivalEvent(int eTime, int oID, int oDistance, double oMoney, ORD_TYPE oType, REGION reg):Event(eTime, oID)
{
	OrdType = oType;
	OrdRegion = reg;
	OrdMoney = oMoney;
	OrdDistance = oDistance;
}
void ArrivalEvent::Execute(Restaurant* pRest)
{
	//This function should create and order and and fills its data 
	// Then adds it to normal, frozen, or VIP order lists that you will create in phase1
	
	Order* pOrd = new Order(OrderID,OrdType,OrdRegion, OrdDistance, OrdMoney, EventTime);
	pRest->AddOrders(pOrd);

	///For the sake of demo, this function will just create an order and add it to DemoQueue
	///Remove the next code lines in phase 1&2
	/*Order* pOrd = new Order(OrderID,OrdType,OrdRegion);
	pRest->AddtoDemoQueue(pOrd)*/;
}
