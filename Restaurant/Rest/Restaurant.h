#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Events\Event.h"
#include "..\Generic_DS\List.h"
#include "..\Generic_DS\PriorityQueue.h"
#include "Motorcycle.h"
#include "Order.h"

// it is the maestro of the project
class Restaurant  
{	
private:
	GUI *pGUI;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file
	List<Order*> Norm_Ord_A;    //List of norm orders
	List<Order*> Norm_Ord_B;
	List<Order*> Norm_Ord_C;
	List<Order*> Norm_Ord_D;

	Queue<Order*>Frz_Ord_A;     //Queue of Frozen orders
	Queue<Order*>Frz_Ord_B;
	Queue<Order*>Frz_Ord_C;
	Queue<Order*>Frz_Ord_D;

	Priority_Queue<Order*>VIP_ord_A;	//priority queue of vip orders
	Priority_Queue<Order*>VIP_ord_B;
	Priority_Queue<Order*>VIP_ord_C;
	Priority_Queue<Order*>VIP_ord_D;

	Queue<Motorcycle*> Norm_Mtr_A;		//queue of all normal motors
	Queue<Motorcycle*> Norm_Mtr_B;
	Queue<Motorcycle*> Norm_Mtr_C;
	Queue<Motorcycle*> Norm_Mtr_D;

	Queue<Motorcycle*> Froz_Mtr_A;     //queue for all frozen motors
	Queue<Motorcycle*> Froz_Mtr_B;
	Queue<Motorcycle*> Froz_Mtr_C;
	Queue<Motorcycle*> Froz_Mtr_D;

	Queue<Motorcycle*> VIP_Mtr_A;    //queue for all VIP motors
	Queue<Motorcycle*> VIP_Mtr_B;
	Queue<Motorcycle*> VIP_Mtr_C;
	Queue<Motorcycle*> VIP_Mtr_D;
	/// ==> 
	//	DEMO-related members. Should be removed in phases 1&2
	Queue<Order*> DEMO_Queue;	//Important: This is just for demo
	/// ==>
	
	int AutoPromLim;
	int EventsNum;
	//
	// TODO: Add More Data Members As Needed
	//time step ::

public:
	
	Restaurant();
	~Restaurant();
	void AddEvent(Event* pE);	//adds a new event to the queue of events
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();

	/// ==> 
	///  DEMO-related functions. Should be removed in phases 1&2
	void Just_A_Demo();	//just to show a demo and should be removed in phase1 1 & 2
	void AddtoDemoQueue(Order* po);	//adds an order to the demo queue
	Order* getDemoOrder();			//return the front order from demo queue
	/// ==> 


	//
	// TODO: Add More Member Functions As Needed
	//
	void MODE_INTR_FN();
	void AddOrders(Order* po);
	void ReadData();
	void CancelOrder(int id);
};

#endif