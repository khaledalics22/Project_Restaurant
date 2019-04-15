#include "PromotionEvent.h"
#include "..\Rest\Restaurant.h"

PromotionEvent::PromotionEvent(int eTime, int oID, double ExMon):Event(eTime, oID)
{
	ExtraMoney = ExMon;
}

void PromotionEvent::Execute(Restaurant* pRest)
{ 
	pRest->PromoteOrder(OrderID,ExtraMoney);          //call Promote fn  in class restaurant

}

PromotionEvent::~PromotionEvent(void)
{
}
