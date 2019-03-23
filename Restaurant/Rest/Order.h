#ifndef __ORDER_H_
#define __ORDER_H_

#include "..\Defs.h"

class Order
{

protected:
	int ID;         //Each order has a unique ID (from 1 --> 999 )
	ORD_TYPE type;		//order type: Normal, Frozen, VIP
	REGION Region;  //Region of this order
	int Distance;	//The distance (in meters) between the order location and the resturant 
	STATE state;    //shows whether the order is active or not         
	double totalMoney;	//Total order money
	bool InService;	//shows whether the order is in service or waiting
	bool serviced;     // shows whether the order is serviced to the customer or not
	int ArrTime, ServTime, FinishTime, WaitingTime, AssigningTime;	//arrival, service start, and finish times
	
public:
	Order(int ID, ORD_TYPE r_Type, REGION r_region, int dis, double cost);

	void SetID(int id);
	int GetID();

	void SetType(ORD_TYPE T);
	int GetType() const;

	void SetRegion(REGION R);
	REGION GetRegion() const;

	void SetDistance(int d);
	int GetDistance() const;

	void SetMoney(double money);
	double GetMoney() const;

	int GetArrTime() const;
	void SetArrTime(int A);

	int GetServTime() const;
	void SetServTime(int S);

	int GetFinishTime() const;
	void SetFinishTime(int F);

	void promote();					//promotes normal orders to VIP

	bool IsActive(void) const;
	void setState(STATE s);

	void SetInservice(bool i);
	bool IsInService() const;

	bool IsServiced() const;
	void SetServiced(bool i);
	
	void SetWaitingTime(int arrival, int assigning);
	int GetWaitingTime() const;

	virtual ~Order();
};

#endif