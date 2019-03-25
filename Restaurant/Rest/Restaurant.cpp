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
		
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:

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
	{Motorcycle m(j,TYPE_NRM,SN,A_REG); Norm_Mtr_A.enqueue(m); j++;}

	for(int i=0;i<NumMotNB;i++)
	{Motorcycle m(j,TYPE_NRM,SN,B_REG); Norm_Mtr_B.enqueue(m); j++;}

	for(int i=0;i<NumMotNC;i++)
	{Motorcycle m(j,TYPE_NRM,SN,C_REG); Norm_Mtr_C.enqueue(m); j++;}
	
	for(int i=0;i<NumMotND;i++)
	{Motorcycle m(j,TYPE_NRM,SN,D_REG); Norm_Mtr_D.enqueue(m); j++;}
	
//filling all frozen motors
	for(int i=0;i<NumMotFA;i++)
	{Motorcycle m(j,TYPE_FROZ,SF,A_REG); Froz_Mtr_A.enqueue(m); j++;}

	for(int i=0;i<NumMotFB;i++)
	{Motorcycle m(j,TYPE_FROZ,SF,B_REG); Froz_Mtr_B.enqueue(m); j++;}

	for(int i=0;i<NumMotFC;i++)
	{Motorcycle m(j,TYPE_FROZ,SF,C_REG); Froz_Mtr_C.enqueue(m); j++;}
	
	for(int i=0;i<NumMotFD;i++)
	{Motorcycle m(j,TYPE_FROZ,SF,D_REG); Froz_Mtr_D.enqueue(m); j++;}

//filling all VIP motors
	for(int i=0;i<NumMotVA;i++)
	{Motorcycle m(j,TYPE_VIP,SV,A_REG); VIP_Mtr_A.enqueue(m); j++;}

	for(int i=0;i<NumMotVB;i++)
	{Motorcycle m(j,TYPE_VIP,SV,B_REG); VIP_Mtr_B.enqueue(m); j++;}

	for(int i=0;i<NumMotVC;i++)
	{Motorcycle m(j,TYPE_VIP,SV,C_REG); VIP_Mtr_C.enqueue(m); j++;}
	
	for(int i=0;i<NumMotVD;i++)
	{Motorcycle m(j,TYPE_VIP,SV,D_REG); VIP_Mtr_D.enqueue(m); j++;}

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
	 if(reg=="A") { Order o(id,TYPE_NRM,A_REG,dst,mon); Norm_Ord_A.InsertEnd(o); ArrivalEvent ariv(TS,id,TYPE_NRM,A_REG); EventsQueue.enqueue(&ariv); }
else if(reg=="B") { Order o(id,TYPE_NRM,B_REG,dst,mon); Norm_Ord_B.InsertEnd(o); ArrivalEvent ariv(TS,id,TYPE_NRM,B_REG); EventsQueue.enqueue(&ariv);}
else if(reg=="C") { Order o(id,TYPE_NRM,C_REG,dst,mon); Norm_Ord_C.InsertEnd(o); ArrivalEvent ariv(TS,id,TYPE_NRM,C_REG); EventsQueue.enqueue(&ariv);}
else if(reg=="D") { Order o(id,TYPE_NRM,D_REG,dst,mon); Norm_Ord_D.InsertEnd(o); ArrivalEvent ariv(TS,id,TYPE_NRM,D_REG); EventsQueue.enqueue(&ariv);}	 
	 
	 }
	 else if(typ=="F") 
	 {
     if(reg=="A") { Order o(id,TYPE_FROZ,A_REG,dst,mon); Frz_Ord_A.enqueue(o); ArrivalEvent ariv(TS,id,TYPE_FROZ,A_REG); EventsQueue.enqueue(&ariv);}
else if(reg=="B") { Order o(id,TYPE_FROZ,B_REG,dst,mon); Frz_Ord_B.enqueue(o); ArrivalEvent ariv(TS,id,TYPE_FROZ,B_REG); EventsQueue.enqueue(&ariv);}
else if(reg=="C") { Order o(id,TYPE_FROZ,C_REG,dst,mon); Frz_Ord_C.enqueue(o); ArrivalEvent ariv(TS,id,TYPE_FROZ,C_REG); EventsQueue.enqueue(&ariv);}
else if(reg=="D") { Order o(id,TYPE_FROZ,D_REG,dst,mon); Frz_Ord_D.enqueue(o); ArrivalEvent ariv(TS,id,TYPE_FROZ,D_REG); EventsQueue.enqueue(&ariv);}		 
	 }
	 else if(typ=="V") 
	 {
     int prio=100*(mon/(dst*TS));
     if(reg=="A") { Order o(id,TYPE_VIP,A_REG,dst,mon); VIP_ord_A.enqueue(o,prio); ArrivalEvent ariv(TS,id,TYPE_VIP,A_REG); EventsQueue.enqueue(&ariv);}
else if(reg=="B") { Order o(id,TYPE_VIP,B_REG,dst,mon); VIP_ord_B.enqueue(o,prio); ArrivalEvent ariv(TS,id,TYPE_VIP,B_REG); EventsQueue.enqueue(&ariv);}
else if(reg=="C") { Order o(id,TYPE_VIP,C_REG,dst,mon); VIP_ord_C.enqueue(o,prio); ArrivalEvent ariv(TS,id,TYPE_VIP,C_REG); EventsQueue.enqueue(&ariv);}
else if(reg=="D") { Order o(id,TYPE_VIP,D_REG,dst,mon); VIP_ord_D.enqueue(o,prio); ArrivalEvent ariv(TS,id,TYPE_VIP,D_REG); EventsQueue.enqueue(&ariv);}     
	 }
 
}
if(s=="P")
     {
		 int ts,id; double exmon; infile>>ts; infile>>id; infile>>exmon;  PromotionEvent pe(ts,id,exmon); EventsQueue.enqueue(&pe);
	 }
else if(s=="X")
     {
		 int ts,id; infile>>ts; infile>>id; CancellationEvent ce(ts,id); EventsQueue.enqueue(&ce);
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