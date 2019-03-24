#pragma once
#include "Event.h"
class PromotionEvent : public Event
{
	double ExtraMoney;
public:
	PromotionEvent(int eTime, int oID, double ExMon);
	virtual void Execute(Restaurant *pRest);
	~PromotionEvent(void);
};

