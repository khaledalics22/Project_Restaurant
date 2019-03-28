#include "CancellationEvent.h"
#include "..\Rest\Restaurant.h"

CancellationEvent::CancellationEvent(int eTime, int oID):Event(eTime, oID)
{
}

void CancellationEvent::Execute(Restaurant* pRest)
{
	pRest->CancelOrder(OrderID);
}

CancellationEvent::~CancellationEvent(void)
{
}
