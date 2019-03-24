#include "Order.h"

Order::Order(int id, ORD_TYPE r_Type, REGION r_region, int dis, double cost)
{

	SetID(id);	//1<ID<999
	SetType(r_Type);
	SetRegion(r_region);	
	SetDistance(dis);
	SetMoney(cost);
	SetInservice(false);
	SetServiced(false);
}

Order::Order(int id, ORD_TYPE r_Type, REGION r_region)
{

	SetID(id);	//1<ID<999
	SetType(r_Type);
	SetRegion(r_region);	
	SetInservice(false);
	SetServiced(false);
}
Order::Order()
{
}
Order::~Order()
{
}

int Order::GetID()
{
	return ID;
}

void Order::SetID(int id)
{
	ID = (id>0&&id<1000)?id:0;
}

void Order::SetType(ORD_TYPE T)
{
	type = T;
}
int Order::GetType() const
{
	return type;
}

void Order::SetRegion(REGION R)
{
	Region = R;
}

REGION Order::GetRegion() const
{
	return Region;
}

void Order::SetDistance(int d)
{
	Distance = d>0?d:0;
}

int Order::GetDistance() const
{
	return Distance;
}

void Order::SetMoney(double money)
{
	totalMoney = money>=0 ? money : 0;
}

double Order::GetMoney() const
{
	return totalMoney;
}

int Order::GetArrTime() const
{
	return ArrTime;
}

void Order::SetArrTime(int A)
{
	ArrTime = A>=0 ? A : 0;
}

int Order::GetServTime() const
{
	return ServTime;
}
	
void Order::SetServTime(int S)
{
	ServTime = S>0 ? S:0;
}

int Order::GetFinishTime() const
{
	return FinishTime;
}

void Order::SetFinishTime(int F)
{
	FinishTime = F>0 ? F:0;
}

void Order::promote()     //not completed yet
{
	if(type == TYPE_NRM && InService == false)
		type = TYPE_VIP;
	return;
}

bool Order::IsActive(void) const
{
	if(state == ACTIVE)
		return true;
	else 
		return false;
}

void Order::SetInservice(bool i)
{
	InService = i;
}

bool Order::IsInService() const
{
	return InService;
}

bool Order::IsServiced() const
{
	return serviced;
}

void Order::SetServiced(bool i)
{
	serviced = i;
}


void Order::setState(STATE s)
{
	state = s;
}

void Order::SetWaitingTime(int arrival, int assigning)
{
	WaitingTime = assigning - arrival;
}

int Order::GetWaitingTime() const
{
	return WaitingTime;
}