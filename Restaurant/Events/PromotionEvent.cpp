#include "PromotionEvent.h"


PromotionEvent::PromotionEvent(int eTime, int oID, double ExMon):Event(eTime, oID)
{
	ExtraMoney = ExMon;
}

void PromotionEvent::Execute(Restaurant* pRest)
{
}

PromotionEvent::~PromotionEvent(void)
{
}
