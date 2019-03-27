#include <cstdlib>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"
#include "..\Events\PromotionEvent.h"
#include "..\Events\CancellationEvent.h"

Restaurant::Restaurant() 
{
	pGUI = NULL;
}

void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();
	ReadData();
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		MODE_INTR_FN();	
		break;
	case MODE_STEP:
		break;
	case MODE_SLNT:
		break;
	case MODE_DEMO:
		Just_A_Demo();

	};

}



//////////////////////////////////  Event handling functions   /////////////////////////////
void Restaurant::AddEvent(Event* pE)	//adds a new event to the queue of events
{
	EventsQueue.enqueue(pE);
}

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event *pE;
	while( EventsQueue.peekFront(pE) )	//as long as there are more events
	{
		if(pE->getEventTime() > CurrentTimeStep )	//no more events at current time
			return;

		pE->Execute(this);
		EventsQueue.dequeue(pE);	//remove event from the queue
		delete pE;		//deallocate event object from memory
	}

}


Restaurant::~Restaurant()
{
		delete pGUI;
}

void Restaurant::ReadData()
{
	ifstream infile;
	infile.open("InputFile.txt");
//receiving speeds	
	int SN,SF,SV;
	infile>>SN; infile>>SF; infile>>SV;
//receiving number of all motors for all regions
	int NumMotNA,NumMotFA,NumMotVA;
	infile>>NumMotNA; infile>>NumMotFA; infile>>NumMotVA;

	int NumMotNB,NumMotFB,NumMotVB;
	infile>>NumMotNB; infile>>NumMotFB; infile>>NumMotVB;

	int NumMotNC,NumMotFC,NumMotVC;
	infile>>NumMotNC; infile>>NumMotFC; infile>>NumMotVC;

	int NumMotND,NumMotFD,NumMotVD;
	infile>>NumMotND; infile>>NumMotFD; infile>>NumMotVD;
	
	int j=0; //motors ID counter

//filling all normal motors
	for(int i=0;i<NumMotNA;i++)
	{
		Motorcycle* m = new Motorcycle(j,TYPE_NRM,SN,A_REG); 
		Norm_Mtr_A.enqueue(m); 
		j++;
	}

	for(int i=0;i<NumMotNB;i++)
	{
		Motorcycle* m = new Motorcycle(j,TYPE_NRM,SN,B_REG);
		Norm_Mtr_B.enqueue(m);
		j++;
	}

	for(int i=0;i<NumMotNC;i++)
	{
		Motorcycle* m = new Motorcycle(j,TYPE_NRM,SN,C_REG); 
		Norm_Mtr_C.enqueue(m);
		j++;
	}
	
	for(int i=0;i<NumMotND;i++)
	{
		Motorcycle* m = new Motorcycle(j,TYPE_NRM,SN,D_REG);
		Norm_Mtr_D.enqueue(m);
		j++;
	}
	
//filling all frozen motors
	for(int i=0;i<NumMotFA;i++)
	{
		Motorcycle* m = new Motorcycle(j,TYPE_FROZ,SF,A_REG); 
		Froz_Mtr_A.enqueue(m); 
		j++;
	}

	for(int i=0;i<NumMotFB;i++)
	{
		Motorcycle* m = new Motorcycle(j,TYPE_FROZ,SF,B_REG);
		Froz_Mtr_B.enqueue(m); 
		j++;
	}

	for(int i=0;i<NumMotFC;i++)
	{
		Motorcycle* m = new Motorcycle(j,TYPE_FROZ,SF,C_REG);
		Froz_Mtr_C.enqueue(m); 
		j++;
	}
	
	for(int i=0;i<NumMotFD;i++)
	{ 
		Motorcycle* m = new Motorcycle(j,TYPE_FROZ,SF,D_REG); 
		Froz_Mtr_D.enqueue(m);
		j++;
	}

//filling all VIP motors
	for(int i=0;i<NumMotVA;i++)
	{
		Motorcycle* m = new Motorcycle(j,TYPE_VIP,SV,A_REG);
		VIP_Mtr_A.enqueue(m); 
		j++;
	}

	for(int i=0;i<NumMotVB;i++)
	{
		Motorcycle* m = new Motorcycle(j,TYPE_VIP,SV,B_REG);
		VIP_Mtr_B.enqueue(m);
		j++;
	}

	for(int i=0;i<NumMotVC;i++)
	{
		Motorcycle* m = new Motorcycle(j,TYPE_VIP,SV,C_REG);
		VIP_Mtr_C.enqueue(m); 
		j++;
	}
	
	for(int i=0;i<NumMotVD;i++)
	{
		Motorcycle* m = new Motorcycle(j,TYPE_VIP,SV,D_REG);
		VIP_Mtr_D.enqueue(m);
		j++;
	}

//receiving Auto promomotion Limit,events Number
	infile>>AutoPromLim;
	infile>>EventsNum;
	string s;
//receiving orders and events
while(infile>>s)
 {
if(s=="R")
{
	 
	 int TS; infile>>TS;
	 string typ; infile>>typ;
	 int id,dst,mon; string reg;
	 infile>>id; infile>>dst; infile>>mon; infile>>reg;
	 
	if(typ=="N") 
	{
		if(reg=="A") 
		{ 
		
			Event* newEvent = new ArrivalEvent(TS, id, dst, mon,TYPE_NRM,A_REG); 
			EventsQueue.enqueue(newEvent); 
		}
		else if(reg=="B")
		{ 
			Event* newEvent = new ArrivalEvent(TS, id, dst, mon,TYPE_NRM,B_REG); 
			EventsQueue.enqueue(newEvent);
		}
		else if(reg=="C")
		{ 
			Event* newEvent = new ArrivalEvent(TS, id, dst, mon,TYPE_NRM,C_REG); 
			EventsQueue.enqueue(newEvent);
		}
		else if(reg=="D")
		{ 
			Event* newEvent = new ArrivalEvent(TS, id, dst, mon,TYPE_NRM,D_REG); 
			EventsQueue.enqueue(newEvent);
		}
	}
	else if(typ=="F") 
	{
		if(reg=="A") 
		{ 
		
			Event* newEvent = new ArrivalEvent(TS, id, dst, mon,TYPE_FROZ,A_REG); 
			EventsQueue.enqueue(newEvent); 
		}
		else if(reg=="B")
		{ 
			Event* newEvent = new ArrivalEvent(TS, id, dst, mon,TYPE_FROZ,B_REG); 
			EventsQueue.enqueue(newEvent);
		}
		else if(reg=="C")
		{ 
			Event* newEvent = new ArrivalEvent(TS, id, dst, mon,TYPE_FROZ,C_REG); 
			EventsQueue.enqueue(newEvent);
		}
		else if(reg=="D")
		{ 
			Event* newEvent = new ArrivalEvent(TS, id, dst, mon,TYPE_FROZ,D_REG); 
			EventsQueue.enqueue(newEvent);
		}		 
	}
	else if(typ=="V") 
	{
		if(reg=="A") 
		{ 
			Event* newEvent = new ArrivalEvent(TS, id, dst, mon,TYPE_VIP,A_REG); 
			EventsQueue.enqueue(newEvent); 
		}
		else if(reg=="B")
		{ 
			Event* newEvent = new ArrivalEvent(TS, id, dst, mon,TYPE_VIP,B_REG); 
			EventsQueue.enqueue(newEvent);
		}
		else if(reg=="C")
		{ 
			Event* newEvent = new ArrivalEvent(TS, id, dst, mon,TYPE_VIP,C_REG); 
			EventsQueue.enqueue(newEvent);
		}
		else if(reg=="D")
		{ 
			Event* newEvent = new ArrivalEvent(TS, id, dst, mon,TYPE_VIP,D_REG); 
			EventsQueue.enqueue(newEvent);
		}
	}
if(s=="P")
     {
		 int ts,id;
		 double exmon;
		 infile>>ts;
		 infile>>id; 
		 infile>>exmon; 
		 Event* newEvent = new PromotionEvent(ts,id,exmon); 
		 EventsQueue.enqueue(newEvent);
	 }
else if(s=="X")
     {
		 int ts,id; 
		 infile>>ts; 
		 infile>>id; 
		 Event* newEvent = new CancellationEvent(ts,id); 
		 EventsQueue.enqueue(newEvent);
     }

 }

}
}



////////////////////////////////////////////////////////////////////////////////
/// ==> 
///  DEMO-related functions. Should be removed in phases 1&2

//This is just a demo function for project introductory phase
//It should be removed starting phase 1
void Restaurant::Just_A_Demo()
{
	
	//
	// THIS IS JUST A DEMO FUNCTION
	// IT SHOULD BE REMOVED IN PHASE 1 AND PHASE 2
	
	int EventCnt;	
	Order* pOrd;
	Event* pEv;
	srand(time(NULL));

	pGUI->PrintMessage("Just a Demo. Enter EVENTS Count(next phases should read I/P filename):");
	EventCnt = atoi(pGUI->GetString().c_str());	//get user input as a string then convert to integer

	pGUI->UpdateInterface();

	pGUI->PrintMessage("Generating orders randomly... In next phases, orders should be loaded from a file");
		
	int EvTime = 0;
	
	//Create Random events
	//All generated event will be "ArrivalEvents" for the demo
	for(int i=0; i<EventCnt; i++)
	{
		int O_id = i+1;
		
		//Rendomize order type
		int OType;
		if(i<EventCnt*0.2)	//let 1st 20% of orders be VIP (just for sake of demo)
			OType = TYPE_VIP;
		else if(i<EventCnt*0.5)	
			OType = TYPE_FROZ;	//let next 30% be Frozen
		else
			OType = TYPE_NRM;	//let the rest be normal

		
		int reg = rand()% REG_CNT;	//randomize region


		//Randomize event time
		EvTime += rand()%4;
		pEv = new ArrivalEvent(EvTime,O_id,(ORD_TYPE)OType,(REGION)reg);
		AddEvent(pEv);

	}	

	int CurrentTimeStep = 1;
	//as long as events queue is not empty yet
	while(!EventsQueue.isEmpty())
	{
		//print current timestep
		char timestep[10];
		itoa(CurrentTimeStep,timestep,10);	
		pGUI->PrintMessage(timestep);


		ExecuteEvents(CurrentTimeStep);	//execute all events at current time step
		//The above line may add new orders to the DEMO_Queue

		//Let's draw all arrived orders by passing them to the GUI to draw

		while(DEMO_Queue.dequeue(pOrd))
		{
			pGUI->AddOrderForDrawing(pOrd);
			pGUI->UpdateInterface();
		}
		Sleep(1000);
		CurrentTimeStep++;	//advance timestep
	}


	pGUI->PrintMessage("generation done, click to END program");
	pGUI->waitForClick();

	
}
////////////////

void Restaurant::AddtoDemoQueue(Order *pOrd)
{
	DEMO_Queue.enqueue(pOrd);
}

Order* Restaurant::getDemoOrder()
{
	Order* pOrd;
	DEMO_Queue.dequeue(pOrd);
	return pOrd;

}


/// ==> end of DEMO-related function

void Restaurant::MODE_INTR_FN()
{
	Order* pOrd;
	int current_time_step=1;
	while(!EventsQueue.isEmpty())
	{
		char timestep[10];
		itoa(current_time_step,timestep,10);	
		pGUI->PrintMessage(timestep);

		ExecuteEvents(current_time_step);

		//vip order  for all areas
		int priority; 
		for  (int i=0; i<VIP_ord_A.getCount();i++)
		{
			VIP_ord_A.dequeue(pOrd,priority);
			pGUI->AddOrderForDrawing(pOrd);
			VIP_ord_A.enqueue(pOrd,priority);

		}
		for  (int i=0; i<VIP_ord_B.getCount();i++)
		{
			VIP_ord_B.dequeue(pOrd,priority);
			pGUI->AddOrderForDrawing(pOrd);
			VIP_ord_B.enqueue(pOrd,priority);

		}
		for  (int i=0; i<VIP_ord_C.getCount();i++)
		{
			VIP_ord_C.dequeue(pOrd,priority);
			pGUI->AddOrderForDrawing(pOrd);
			VIP_ord_C.enqueue(pOrd,priority);

		}
		for  (int i=0; i<VIP_ord_D.getCount();i++)
		{
			VIP_ord_D.dequeue(pOrd,priority);
			pGUI->AddOrderForDrawing(pOrd);
			VIP_ord_D.enqueue(pOrd,priority);

		}

		//frozen order  for all areas
		for  (int i=0; i<Frz_Ord_A.getCount();i++)
		{
			Frz_Ord_A.dequeue(pOrd);
			pGUI->AddOrderForDrawing(pOrd);
			Frz_Ord_A.enqueue(pOrd);

		}
		for  (int i=0; i<Frz_Ord_B.getCount();i++)
		{
			Frz_Ord_B.dequeue(pOrd);
			pGUI->AddOrderForDrawing(pOrd);
			Frz_Ord_B.enqueue(pOrd);

		}
		for  (int i=0; i<Frz_Ord_C.getCount();i++)
		{
			Frz_Ord_C.dequeue(pOrd);
			pGUI->AddOrderForDrawing(pOrd);
			Frz_Ord_C.enqueue(pOrd);

		}
		for  (int i=0; i<Frz_Ord_D.getCount();i++)
		{
			Frz_Ord_D.dequeue(pOrd);
			pGUI->AddOrderForDrawing(pOrd);
			Frz_Ord_D.enqueue(pOrd);

		}


		//normal orders for all areas
		for  (int i=0; i<Norm_Ord_A.getCount();i++)
		{
			Norm_Ord_A.GetFirst(pOrd);
			pGUI->AddOrderForDrawing(pOrd);
			Norm_Ord_A.InsertEnd(pOrd);

		}
		for  (int i=0; i<Norm_Ord_B.getCount();i++)
		{
			Norm_Ord_B.GetFirst(pOrd);
			pGUI->AddOrderForDrawing(pOrd);
			Norm_Ord_B.InsertEnd(pOrd);

		}
		for  (int i=0; i<Norm_Ord_C.getCount();i++)
		{
			Norm_Ord_C.GetFirst(pOrd);
			pGUI->AddOrderForDrawing(pOrd);
			Norm_Ord_C.InsertEnd(pOrd);


		}
		for  (int i=0; i<Norm_Ord_D.getCount();i++)
		{
			Norm_Ord_D.GetFirst(pOrd);
			pGUI->AddOrderForDrawing(pOrd);
			Norm_Ord_D.InsertEnd(pOrd);

		}
/*		
		pGUI->PrintMessage("Number of Active Orders in Region A = ",1);
		int count=VIP_ord_A.getCount()+Norm_Ord_A.getCount()+Frz_Ord_A.getCount();
		itoa(count,timestep,10);	
		pGUI->PrintMessage(timestep,1,40);
		pGUI->PrintMessage("\nNumber of Active Orders in Region B = ",2);
		count=VIP_ord_B.getCount()+Norm_Ord_B.getCount()+Frz_Ord_B.getCount();
		itoa(count,timestep,10);	
		pGUI->PrintMessage(timestep,2,40);

		pGUI->PrintMessage("\nNumber of Active Orders in Region C = ",3);
		count=VIP_ord_C.getCount()+Norm_Ord_C.getCount()+Frz_Ord_C.getCount();
		itoa(count,timestep,10);	
		pGUI->PrintMessage(timestep,3,40);

		pGUI->PrintMessage("\nNumber of Active Orders in Region D = ",4);
		count=VIP_ord_D.getCount()+Norm_Ord_D.getCount()+Frz_Ord_D.getCount();
		itoa(count,timestep,10);	
		pGUI->PrintMessage(timestep,4,40);
*/
		pGUI->UpdateInterface();
		pGUI->ResetDrawingList();
		pGUI->waitForClick(); 
	
		current_time_step++;
	}


}

void Restaurant::AddOrders(Order*  po)
{
	switch (po->GetType())
	{
	case TYPE_NRM:

		switch (po->GetRegion())
		{
		case A_REG:
			Norm_Ord_A.InsertEnd(po);
			break;
		case B_REG:
			Norm_Ord_B.InsertEnd(po);
			break;
		case C_REG:
			Norm_Ord_C.InsertEnd(po);
			break;
		case D_REG:
			Norm_Ord_D.InsertEnd(po);
			break;
		default:
			break;
		}
		break;
	case TYPE_VIP:
		{
			int priority = 1000*(po->GetMoney()/(po->GetDistance()*po->GetArrTime()));
			switch (po->GetRegion())
			{
			case A_REG:
				VIP_ord_A.enqueue(po, priority);
				break;
			case B_REG:
				VIP_ord_B.enqueue(po, priority);
				break;
			case C_REG:
				VIP_ord_C.enqueue(po, priority);
				break;
			case D_REG:
				VIP_ord_D.enqueue(po, priority);
				break;
			default:
				break;
			}
			break;
		}

	case TYPE_FROZ:
		
		switch (po->GetRegion())
		{
		case A_REG:
			Frz_Ord_A.enqueue(po);
			break;
		case B_REG:
			Frz_Ord_B.enqueue(po);
			break;
		case C_REG:
			Frz_Ord_C.enqueue(po);
			break;
		case D_REG:
			Frz_Ord_D.enqueue(po);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}