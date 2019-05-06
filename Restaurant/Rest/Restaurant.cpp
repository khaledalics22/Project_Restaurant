#include <cstdlib>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
using namespace std;

#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"
#include "..\Events\PromotionEvent.h"
#include "..\Events\CancellationEvent.h"

Restaurant::Restaurant() 
{
	pGUI = NULL;
}
PROG_MODE Restaurant::Readinput()
{

	PROG_MODE 	input; 
	do
	{
		input = pGUI->readinput();
	}while (input!=0&&input!=1); 
	return input; 
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
		MODE_STEP_FN();
		break;
	case MODE_SLNT:
		break;
	//case MODE_DEMO:
		//Just_A_Demo();

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
	deleteMotorcycle(Norm_Mtr_A);	
	deleteMotorcycle(Norm_Mtr_B);
	deleteMotorcycle(Norm_Mtr_C);
	deleteMotorcycle(Norm_Mtr_D);
		
	deleteMotorcycle(Froz_Mtr_A);
	deleteMotorcycle(Froz_Mtr_B);
	deleteMotorcycle(Froz_Mtr_C);
	deleteMotorcycle(Froz_Mtr_D);

	deleteMotorcycle(VIP_Mtr_A);
	deleteMotorcycle(VIP_Mtr_B);
	deleteMotorcycle(VIP_Mtr_C);
	deleteMotorcycle(VIP_Mtr_D);
	delete pGUI;
}

void Restaurant::ReadData()
{
	ifstream infile;
	infile.open("InputFile.txt");

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
	int ExSpeed; //speed of motors
	//filling all normal motors
	for(int i=0;i<NumMotNA;i++)
	{
		infile>>ExSpeed;
		Motorcycle* m = new Motorcycle(j,TYPE_NRM,ExSpeed,A_REG); 
		Norm_Mtr_A.enqueue(m,ExSpeed); 
		j++;

	}

	for(int i=0;i<NumMotNB;i++)
	{
		infile>>ExSpeed;
		Motorcycle* m = new Motorcycle(j,TYPE_NRM,ExSpeed,B_REG);
		Norm_Mtr_B.enqueue(m,ExSpeed);
		j++;
	
	}
	
	for(int i=0;i<NumMotNC;i++)
	{
		infile>>ExSpeed;
		Motorcycle* m = new Motorcycle(j,TYPE_NRM,ExSpeed,C_REG); 
		Norm_Mtr_C.enqueue(m,ExSpeed);
		j++;

	}

	for(int i=0;i<NumMotND;i++)
	{
		infile>>ExSpeed;
		Motorcycle* m = new Motorcycle(j,TYPE_NRM,ExSpeed,D_REG);
		Norm_Mtr_D.enqueue(m,ExSpeed);
		j++;
	
	}

//filling all frozen motors
	for(int i=0;i<NumMotFA;i++)
	{
		infile>>ExSpeed;
		Motorcycle* m = new Motorcycle(j,TYPE_FROZ,ExSpeed,A_REG); 
		Froz_Mtr_A.enqueue(m,ExSpeed); 
		j++;
	}

	for(int i=0;i<NumMotFB;i++)
	{
		infile>>ExSpeed;
		Motorcycle* m = new Motorcycle(j,TYPE_FROZ,ExSpeed,B_REG);
		Froz_Mtr_B.enqueue(m,ExSpeed); 
		j++;
	}

	for(int i=0;i<NumMotFC;i++)
	{
		infile>>ExSpeed;
		Motorcycle* m = new Motorcycle(j,TYPE_FROZ,ExSpeed,C_REG);
		Froz_Mtr_C.enqueue(m,ExSpeed); 
		j++;
	}

	for(int i=0;i<NumMotFD;i++)
	{ 
		infile>>ExSpeed;
		Motorcycle* m = new Motorcycle(j,TYPE_FROZ,ExSpeed,D_REG); 
		Froz_Mtr_D.enqueue(m,ExSpeed);
		j++;
	}

//filling all VIP motors
	for(int i=0;i<NumMotVA;i++)
	{
		infile>>ExSpeed;
		Motorcycle* m = new Motorcycle(j,TYPE_VIP,ExSpeed,A_REG);
		VIP_Mtr_A.enqueue(m,ExSpeed); 
		j++;

	}

	for(int i=0;i<NumMotVB;i++)
	{
		infile>>ExSpeed;
		Motorcycle* m = new Motorcycle(j,TYPE_VIP,ExSpeed,B_REG);
		VIP_Mtr_B.enqueue(m,ExSpeed);
		j++;
	}

	for(int i=0;i<NumMotVC;i++)
	{
		infile>>ExSpeed;
		Motorcycle* m = new Motorcycle(j,TYPE_VIP,ExSpeed,C_REG);
		VIP_Mtr_C.enqueue(m,ExSpeed); 
		j++;
	}

	for(int i=0;i<NumMotVD;i++)
	{
		infile>>ExSpeed;
		Motorcycle* m = new Motorcycle(j,TYPE_VIP,ExSpeed,D_REG);
		VIP_Mtr_D.enqueue(m,ExSpeed);
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
	}
	else if(s=="P")
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



void Restaurant::MODE_INTR_FN()
{
	int current_time_step=1;
	char timestep[10];
	while(isOpen())
	{
		itoa(current_time_step,timestep,10);	
		ExecuteEvents(current_time_step);
		ReturnMotorcycle(current_time_step);
		AutoPromotion(current_time_step);
		PrintGUI();
		PrintToStatusBar(timestep);
		pGUI->UpdateInterface();
		pGUI->ResetDrawingList();
		AssignToMotorcycle(current_time_step);

		pGUI->waitForClick();
		current_time_step++;
	}

		GetOutPutFile(); 
}

void Restaurant::AddOrders(Order*  po)
{
	switch (po->GetType())
	{
		case TYPE_NRM:
		{
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
		}
		case TYPE_VIP:
		{
			int priority = 100*(po->GetMoney()/(po->GetDistance()*po->GetArrTime()));
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
		{
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
}
void Restaurant::AddMotorcycle(Motorcycle *po, int priority)
{
	switch (po->GetType())
	{
		case TYPE_NRM:
		{
			switch (po->GetRegion())
			{
			case A_REG:
				Norm_Mtr_A.enqueue(po, priority);
				break;
			case B_REG:
				Norm_Mtr_B.enqueue(po, priority);
				break;
			case C_REG:
				Norm_Mtr_C.enqueue(po, priority);
				break;
			case D_REG:
				Norm_Mtr_D.enqueue(po, priority);
				break;
			}
			break;
		}
		case TYPE_FROZ:
		{
			switch (po->GetRegion())
			{
			case A_REG:
				Froz_Mtr_A.enqueue(po, priority);
				break;
			case B_REG:
				Froz_Mtr_B.enqueue(po, priority);
				break;
			case C_REG:
				Froz_Mtr_C.enqueue(po, priority);
				break;
			case D_REG:
				Froz_Mtr_D.enqueue(po, priority);
				break;
			}
			break;
		}
		case TYPE_VIP:
		{
			switch (po->GetRegion())
			{
			case A_REG:
				VIP_Mtr_A.enqueue(po, priority);
				break;
			case B_REG:
				VIP_Mtr_B.enqueue(po, priority);
				break;
			case C_REG:
				VIP_Mtr_C.enqueue(po, priority);
				break;
			case D_REG:
				VIP_Mtr_D.enqueue(po, priority);
				break;
			}
			break;
		}
	}
}

void Restaurant::CancelOrder(int id)
{
	Order* pOrd;
	bool found = false;
	for  (int i=0; i<Norm_Ord_A.getCount();i++)
	{
		Norm_Ord_A.GetFirst(pOrd);
		if(pOrd->GetID() != id)
			Norm_Ord_A.InsertEnd(pOrd);
		else
			found = true;
	}
	
	if(found)
		return;
	
	for  (int i=0; i<Norm_Ord_B.getCount();i++)
	{
		Norm_Ord_B.GetFirst(pOrd);
		if(pOrd->GetID() != id)
			Norm_Ord_B.InsertEnd(pOrd);
		else
			found = true;
	}
	
	if(found)
		return;
	
	for  (int i=0; i<Norm_Ord_C.getCount();i++)
	{
		Norm_Ord_C.GetFirst(pOrd);
		if(pOrd->GetID() != id)
			Norm_Ord_C.InsertEnd(pOrd);
		else
			found = true;
	}

	if(found)
		return;

	for  (int i=0; i<Norm_Ord_D.getCount();i++)
	{
		Norm_Ord_D.GetFirst(pOrd);
		if(pOrd->GetID() != id)
			Norm_Ord_D.InsertEnd(pOrd);
	}
}
void Restaurant::deleteMotorcycle(Priority_Queue<Motorcycle*> &toDelete)
{
	//int x;
	//Motorcycle* m = NULL;
	//while (toDelete.dequeue(m,x))
	//{
//		delete m;
	//}
	toDelete.Clear();
}

void Restaurant::MODE_STEP_FN()
{
	int current_time_step=1;
	char timestep[10];
	while(!EventsQueue.isEmpty())
	{
		itoa(current_time_step,timestep,10);	
		//pGUI->PrintMessage(timestep);

		ExecuteEvents(current_time_step);
		PrintGUI();		
		PrintToStatusBar(timestep);
		pGUI->UpdateInterface();
		pGUI->ResetDrawingList();
		Sleep(1000);
		ReturnMotorcycle(current_time_step);
		AutoPromotion(current_time_step);
		AssignToMotorcycle(current_time_step);

		current_time_step++;
	}
	while (!Norm_Ord_A.IsEmpty()||!Norm_Ord_B.IsEmpty()||!Norm_Ord_C.IsEmpty()||!Norm_Ord_D.IsEmpty()||!Frz_Ord_A.isEmpty()||!Frz_Ord_B.isEmpty()||!Frz_Ord_C.isEmpty()||!Frz_Ord_D.isEmpty()||!VIP_ord_A.isEmpty()||!VIP_ord_B.isEmpty()||!VIP_ord_C.isEmpty()||!VIP_ord_D.isEmpty())
	{
		itoa(current_time_step,timestep,10);	
		PrintGUI();		
		
		PrintToStatusBar(timestep);
		pGUI->UpdateInterface();
		pGUI->ResetDrawingList();
		Sleep(1000);
		ReturnMotorcycle(current_time_step);
		AutoPromotion(current_time_step);
		AssignToMotorcycle(current_time_step);
		current_time_step++;
	}
	itoa(current_time_step,timestep,10);	
	PrintToStatusBar(timestep);
	pGUI->UpdateInterface();
	GetOutPutFile(); 

}
void Restaurant::MODE_SILENT_FN()
{
	int current_time_step=1;
	char timestep[10];

	while(!EventsQueue.isEmpty())
	{
		itoa(current_time_step,timestep,10);	
		ExecuteEvents(current_time_step);
		PrintGUI();
		ReturnMotorcycle(current_time_step);
		AutoPromotion(current_time_step);
		AssignToMotorcycle(current_time_step);
		PrintToStatusBar(timestep);
		current_time_step++;
	}
	while (!Norm_Ord_A.IsEmpty()||!Norm_Ord_B.IsEmpty()||!Norm_Ord_C.IsEmpty()||!Norm_Ord_D.IsEmpty()||!Frz_Ord_A.isEmpty()||!Frz_Ord_B.isEmpty()||!Frz_Ord_C.isEmpty()||!Frz_Ord_D.isEmpty()||!VIP_ord_A.isEmpty()||!VIP_ord_B.isEmpty()||!VIP_ord_C.isEmpty()||!VIP_ord_D.isEmpty())
	{
		itoa(current_time_step,timestep,10);	
		PrintGUI();		
		ReturnMotorcycle(current_time_step);
		AutoPromotion(current_time_step);
		AssignToMotorcycle(current_time_step);
		PrintToStatusBar(timestep);
	//	pGUI->UpdateInterface();
	//  pGUI->ResetDrawingList();
	//  Sleep(1000);
		current_time_step++;
	}
	//pGUI->UpdateInterface();

	GetOutPutFile(); 

}

void Restaurant::AutoPromotion(int time_step)
{
	int i=1, t;
	bool flag = true;
	Order* ord;
	while(i<=Norm_Ord_A.getCount() && flag)
	{
		if(Norm_Ord_A.GetFirst(ord))
		{
			t = ord->GetArrTime();
			if(t-time_step >= AutoPromLim)
				PromoteOrder(ord->GetID(), 0);
			else
			{
				Norm_Ord_A.InsertBeg(ord);
				flag = false;
			}
		}
		else
			flag = false;
		i++;
	}

	i=1;
	flag = true;
	while(i<=Norm_Ord_B.getCount() && flag)
	{
		if(Norm_Ord_B.GetFirst(ord))
		{
			t = ord->GetArrTime();
			if(t - time_step >= AutoPromLim)
				PromoteOrder(ord->GetID(), 0);
			else
			{
				Norm_Ord_B.InsertBeg(ord);
				flag = false;
			}
		}
		else
			flag = false;
		i++;
	}

	i=1;
	flag = true;
	while(i<=Norm_Ord_C.getCount() && flag)
	{
		if(Norm_Ord_C.GetFirst(ord))
		{
			t = ord->GetArrTime();
			if(t - time_step >= AutoPromLim)
				PromoteOrder(ord->GetID(), 0);
			else
			{
				Norm_Ord_C.InsertBeg(ord);
				flag = false;
			}
		}
		else
			flag = false;
		i++;
	}

	i=1;
	flag = true;
	while(i<=Norm_Ord_D.getCount() && flag)
	{
		if(Norm_Ord_D.GetFirst(ord))
		{
			t = ord->GetArrTime();
			if(t - time_step >= AutoPromLim)
				PromoteOrder(ord->GetID(), 0);
			else
			{
				Norm_Ord_D.InsertBeg(ord);
				flag = false;
			}
		}
		else
			flag = false;
		i++;
	}
}

void  Restaurant::PromoteOrder (int id,int extramoney)   //takes the money and id to promote   .....called in promotionEvent
{

	Order* Order; 
	for(int i=0; i<Norm_Ord_A.getCount(); i++)     // loop on normal Orders in regioin A
	{
		Norm_Ord_A.GetFirst(Order);
		if(Order->GetID()==id)                  //if found promote or ignore Event
		{
			Order->promote();         // change the type of Order  if not in service
			int money=Order->GetMoney(); 
			Order->SetMoney(money+extramoney);   // set new money
			AddOrders(Order);			//add order to the appropriate List
			if (i==0)break;                     //if found at beginning of the list there is no need to continue
		}
		else
			Norm_Ord_A.InsertEnd(Order);          //if not at the beginnign or not found at all refill the List
			
	}
													//same for all areas
	for(int i=0; i<Norm_Ord_B.getCount(); i++)   
	{
		Norm_Ord_B.GetFirst(Order);
		if(Order->GetID()==id)
		{
			Order->promote();
			int money=Order->GetMoney(); 
			Order->SetMoney(money+extramoney); 
			AddOrders(Order); 
			if (i==0)break; 
		}
		else
			Norm_Ord_B.InsertEnd(Order);
			
	}	
	
	for(int i=0; i<Norm_Ord_C.getCount(); i++)
	{
		Norm_Ord_C.GetFirst(Order);
		if(Order->GetID()==id)
		{
			Order->promote();
			int money=Order->GetMoney(); 
			Order->SetMoney(money+extramoney); 
			AddOrders(Order); 
			if (i==0)break; 
		}
		else
			Norm_Ord_C.InsertEnd(Order);
			
	}	
	
	for(int i=0; i<Norm_Ord_D.getCount(); i++)
	{
		Norm_Ord_D.GetFirst(Order);
		if(Order->GetID()==id)
		{
			Order->promote();
			int money=Order->GetMoney(); 
			Order->SetMoney(money+extramoney); 
			AddOrders(Order); 
			if (i==0)break; 
		}
		else
			Norm_Ord_D.InsertEnd(Order);
			
	}
}

void Restaurant::AssignToMotorcycle(int timestep)
{
	Motorcycle* mtr = NULL;
	Order* ord = NULL;
	int speed, p;
	//Assign Region A
	
	//Assign VIP Orders first
	while(!VIP_Mtr_A.isEmpty() && !VIP_ord_A.isEmpty())
	{
		VIP_Mtr_A.dequeue(mtr, speed);
		VIP_ord_A.dequeue(ord, p);
		ord->SetWaitingTime(timestep-ord->GetArrTime());
		ord->SetServTime(ord->GetDistance()/speed);
		ord->SetFinishTime(ord->GetArrTime() + ord->GetWaitingTime() + ord->GetServTime());
		Serving_Mtr.enqueue(mtr, -(ord->GetFinishTime() + ord->GetServTime()));
		Served_Ord.enqueue(ord, -ord->GetFinishTime());
	}

	while(!Norm_Mtr_A.isEmpty() && !VIP_ord_A.isEmpty())
	{
		Norm_Mtr_A.dequeue(mtr, speed);
		VIP_ord_A.dequeue(ord, p);
		ord->SetWaitingTime(timestep-ord->GetArrTime());
		ord->SetServTime(ord->GetDistance()/speed);
		ord->SetFinishTime(ord->GetArrTime() + ord->GetWaitingTime() + ord->GetServTime());
		Serving_Mtr.enqueue(mtr, -(ord->GetFinishTime() + ord->GetServTime()));
		Served_Ord.enqueue(ord, -ord->GetFinishTime());
	}

	while(!Froz_Mtr_A.isEmpty() && !VIP_ord_A.isEmpty())
	{
		Froz_Mtr_A.dequeue(mtr, speed);
		VIP_ord_A.dequeue(ord, p);
		ord->SetWaitingTime(timestep-ord->GetArrTime());
		ord->SetServTime(ord->GetDistance()/speed);
		ord->SetFinishTime(ord->GetArrTime() + ord->GetWaitingTime() + ord->GetServTime());
		Serving_Mtr.enqueue(mtr, -(ord->GetFinishTime() + ord->GetServTime()));
		Served_Ord.enqueue(ord, -ord->GetFinishTime());
	}

	//Assign Frozen orders
	while(!Froz_Mtr_A.isEmpty() && !Frz_Ord_A.isEmpty())
	{
		Froz_Mtr_A.dequeue(mtr, speed);
		Frz_Ord_A.dequeue(ord);
		ord->SetWaitingTime(timestep-ord->GetArrTime());
		ord->SetServTime(ord->GetDistance()/speed);
		ord->SetFinishTime(ord->GetArrTime() + ord->GetWaitingTime() + ord->GetServTime());
		Serving_Mtr.enqueue(mtr, -(ord->GetFinishTime() + ord->GetServTime()));
		Served_Ord.enqueue(ord, -ord->GetFinishTime());
	}

	//Assign Normal orders
	while(!VIP_Mtr_A.isEmpty() && !Norm_Ord_A.IsEmpty())
	{
		VIP_Mtr_A.dequeue(mtr, speed);
		Norm_Ord_A.GetFirst(ord);
		ord->SetWaitingTime(timestep-ord->GetArrTime());
		ord->SetServTime(ord->GetDistance()/speed);
		ord->SetFinishTime(ord->GetArrTime() + ord->GetWaitingTime() + ord->GetServTime());
		Serving_Mtr.enqueue(mtr, -(ord->GetFinishTime() + ord->GetServTime()));
		Served_Ord.enqueue(ord, -ord->GetFinishTime());
	}

	while(!Norm_Mtr_A.isEmpty() && !Norm_Ord_A.IsEmpty())
	{
		Norm_Mtr_A.dequeue(mtr, speed);
		Norm_Ord_A.GetFirst(ord);
		ord->SetWaitingTime(timestep-ord->GetArrTime());
		ord->SetServTime(ord->GetDistance()/speed);
		ord->SetFinishTime(ord->GetArrTime() + ord->GetWaitingTime() + ord->GetServTime());
		Serving_Mtr.enqueue(mtr, -(ord->GetFinishTime() + ord->GetServTime()));
		Served_Ord.enqueue(ord, -ord->GetFinishTime());
	}



	//Assign Region B
	
	//Assign VIP Orders first
	while(!VIP_Mtr_B.isEmpty() && !VIP_ord_B.isEmpty())
	{
		VIP_Mtr_B.dequeue(mtr, speed);
		VIP_ord_B.dequeue(ord, p);
		ord->SetWaitingTime(timestep-ord->GetArrTime());
		ord->SetServTime(ord->GetDistance()/speed);
		ord->SetFinishTime(ord->GetArrTime() + ord->GetWaitingTime() + ord->GetServTime());
		Serving_Mtr.enqueue(mtr, -(ord->GetFinishTime() + ord->GetServTime()));
		Served_Ord.enqueue(ord, -ord->GetFinishTime());
	}

	while(!Norm_Mtr_B.isEmpty() && !VIP_ord_B.isEmpty())
	{
		Norm_Mtr_B.dequeue(mtr, speed);
		VIP_ord_B.dequeue(ord, p);
		ord->SetWaitingTime(timestep-ord->GetArrTime());
		ord->SetServTime(ord->GetDistance()/speed);
		ord->SetFinishTime(ord->GetArrTime() + ord->GetWaitingTime() + ord->GetServTime());
		Serving_Mtr.enqueue(mtr, -(ord->GetFinishTime() + ord->GetServTime()));
		Served_Ord.enqueue(ord, -ord->GetFinishTime());
	}

	while(!Froz_Mtr_B.isEmpty() && !VIP_ord_B.isEmpty())
	{
		Froz_Mtr_B.dequeue(mtr, speed);
		VIP_ord_B.dequeue(ord, p);
		ord->SetWaitingTime(timestep-ord->GetArrTime());
		ord->SetServTime(ord->GetDistance()/speed);
		ord->SetFinishTime(ord->GetArrTime() + ord->GetWaitingTime() + ord->GetServTime());
		Serving_Mtr.enqueue(mtr, -(ord->GetFinishTime() + ord->GetServTime()));
		Served_Ord.enqueue(ord, -ord->GetFinishTime());
	}

	//Assign Frozen orders
	while(!Froz_Mtr_B.isEmpty() && !Frz_Ord_B.isEmpty())
	{
		Froz_Mtr_B.dequeue(mtr, speed);
		Frz_Ord_B.dequeue(ord);
		ord->SetWaitingTime(timestep-ord->GetArrTime());
		ord->SetServTime(ord->GetDistance()/speed);
		ord->SetFinishTime(ord->GetArrTime() + ord->GetWaitingTime() + ord->GetServTime());
		Serving_Mtr.enqueue(mtr, -(ord->GetFinishTime() + ord->GetServTime()));
		Served_Ord.enqueue(ord, -ord->GetFinishTime());
	}

	//Assign Normal orders
	while(!VIP_Mtr_B.isEmpty() && !Norm_Ord_B.IsEmpty())
	{
		VIP_Mtr_B.dequeue(mtr, speed);
		Norm_Ord_B.GetFirst(ord);
		ord->SetWaitingTime(timestep-ord->GetArrTime());
		ord->SetServTime(ord->GetDistance()/speed);
		ord->SetFinishTime(ord->GetArrTime() + ord->GetWaitingTime() + ord->GetServTime());
		Serving_Mtr.enqueue(mtr, -(ord->GetFinishTime() + ord->GetServTime()));
		Served_Ord.enqueue(ord, -ord->GetFinishTime());
	}

	while(!Norm_Mtr_B.isEmpty() && !Norm_Ord_B.IsEmpty())
	{
		Norm_Mtr_B.dequeue(mtr, speed);
		Norm_Ord_B.GetFirst(ord);
		ord->SetWaitingTime(timestep-ord->GetArrTime());
		ord->SetServTime(ord->GetDistance()/speed);
		ord->SetFinishTime(ord->GetArrTime() + ord->GetWaitingTime() + ord->GetServTime());
		Serving_Mtr.enqueue(mtr, -(ord->GetFinishTime() + ord->GetServTime()));
		Served_Ord.enqueue(ord, -ord->GetFinishTime());
	}


	//Assign Region C
	
	//Assign VIP Orders first
	while(!VIP_Mtr_C.isEmpty() && !VIP_ord_C.isEmpty())
	{
		VIP_Mtr_C.dequeue(mtr, speed);
		VIP_ord_C.dequeue(ord, p);
		ord->SetWaitingTime(timestep-ord->GetArrTime());
		ord->SetServTime(ord->GetDistance()/speed);
		ord->SetFinishTime(ord->GetArrTime() + ord->GetWaitingTime() + ord->GetServTime());
		Serving_Mtr.enqueue(mtr, -(ord->GetFinishTime() + ord->GetServTime()));
		Served_Ord.enqueue(ord, -ord->GetFinishTime());
	}

	while(!Norm_Mtr_C.isEmpty() && !VIP_ord_C.isEmpty())
	{
		Norm_Mtr_C.dequeue(mtr, speed);
		VIP_ord_C.dequeue(ord, p);
		ord->SetWaitingTime(timestep-ord->GetArrTime());
		ord->SetServTime(ord->GetDistance()/speed);
		ord->SetFinishTime(ord->GetArrTime() + ord->GetWaitingTime() + ord->GetServTime());
		Serving_Mtr.enqueue(mtr, -(ord->GetFinishTime() + ord->GetServTime()));
		Served_Ord.enqueue(ord, -ord->GetFinishTime());
	}

	while(!Froz_Mtr_C.isEmpty() && !VIP_ord_C.isEmpty())
	{
		Froz_Mtr_C.dequeue(mtr, speed);
		VIP_ord_C.dequeue(ord, p);
		ord->SetWaitingTime(timestep-ord->GetArrTime());
		ord->SetServTime(ord->GetDistance()/speed);
		ord->SetFinishTime(ord->GetArrTime() + ord->GetWaitingTime() + ord->GetServTime());
		Serving_Mtr.enqueue(mtr, -(ord->GetFinishTime() + ord->GetServTime()));
		Served_Ord.enqueue(ord, -ord->GetFinishTime());
	}

	//Assign Frozen orders
	while(!Froz_Mtr_C.isEmpty() && !Frz_Ord_C.isEmpty())
	{
		Froz_Mtr_C.dequeue(mtr, speed);
		Frz_Ord_C.dequeue(ord);
		ord->SetWaitingTime(timestep-ord->GetArrTime());
		ord->SetServTime(ord->GetDistance()/speed);
		ord->SetFinishTime(ord->GetArrTime() + ord->GetWaitingTime() + ord->GetServTime());
		Serving_Mtr.enqueue(mtr, -(ord->GetFinishTime() + ord->GetServTime()));
		Served_Ord.enqueue(ord, -ord->GetFinishTime());
	}

	//Assign Normal orders
	while(!VIP_Mtr_C.isEmpty() && !Norm_Ord_C.IsEmpty())
	{
		VIP_Mtr_C.dequeue(mtr, speed);
		Norm_Ord_C.GetFirst(ord);
		ord->SetWaitingTime(timestep-ord->GetArrTime());
		ord->SetServTime(ord->GetDistance()/speed);
		ord->SetFinishTime(ord->GetArrTime() + ord->GetWaitingTime() + ord->GetServTime());
		Serving_Mtr.enqueue(mtr, -(ord->GetFinishTime() + ord->GetServTime()));
		Served_Ord.enqueue(ord, -ord->GetFinishTime());
	}

	while(!Norm_Mtr_C.isEmpty() && !Norm_Ord_C.IsEmpty())
	{
		Norm_Mtr_C.dequeue(mtr, speed);
		Norm_Ord_C.GetFirst(ord);
		ord->SetWaitingTime(timestep-ord->GetArrTime());
		ord->SetServTime(ord->GetDistance()/speed);
		ord->SetFinishTime(ord->GetArrTime() + ord->GetWaitingTime() + ord->GetServTime());
		Serving_Mtr.enqueue(mtr, -(ord->GetFinishTime() + ord->GetServTime()));
		Served_Ord.enqueue(ord, -ord->GetFinishTime());
	}


	//Assign Region D
	
	//Assign VIP Orders first
	while(!VIP_Mtr_D.isEmpty() && !VIP_ord_D.isEmpty())
	{
		VIP_Mtr_D.dequeue(mtr, speed);
		VIP_ord_D.dequeue(ord, p);
		ord->SetWaitingTime(timestep-ord->GetArrTime());
		ord->SetServTime(ord->GetDistance()/speed);
		ord->SetFinishTime(ord->GetArrTime() + ord->GetWaitingTime() + ord->GetServTime());
		Serving_Mtr.enqueue(mtr, -(ord->GetFinishTime() + ord->GetServTime()));
		Served_Ord.enqueue(ord, -ord->GetFinishTime());
	}

	while(!Norm_Mtr_D.isEmpty() && !VIP_ord_D.isEmpty())
	{
		Norm_Mtr_D.dequeue(mtr, speed);
		VIP_ord_D.dequeue(ord, p);
		ord->SetWaitingTime(timestep-ord->GetArrTime());
		ord->SetServTime(ord->GetDistance()/speed);
		ord->SetFinishTime(ord->GetArrTime() + ord->GetWaitingTime() + ord->GetServTime());
		Serving_Mtr.enqueue(mtr, -(ord->GetFinishTime() + ord->GetServTime()));
		Served_Ord.enqueue(ord, -ord->GetFinishTime());
	}

	while(!Froz_Mtr_D.isEmpty() && !VIP_ord_D.isEmpty())
	{
		Froz_Mtr_D.dequeue(mtr, speed);
		VIP_ord_D.dequeue(ord, p);
		ord->SetWaitingTime(timestep-ord->GetArrTime());
		ord->SetServTime(ord->GetDistance()/speed);
		ord->SetFinishTime(ord->GetArrTime() + ord->GetWaitingTime() + ord->GetServTime());
		Serving_Mtr.enqueue(mtr, -(ord->GetFinishTime() + ord->GetServTime()));
		Served_Ord.enqueue(ord, -ord->GetFinishTime());
	}

	//Assign Frozen orders
	while(!Froz_Mtr_D.isEmpty() && !Frz_Ord_D.isEmpty())
	{
		Froz_Mtr_D.dequeue(mtr, speed);
		Frz_Ord_D.dequeue(ord);
		ord->SetWaitingTime(timestep-ord->GetArrTime());
		ord->SetServTime(ord->GetDistance()/speed);
		ord->SetFinishTime(ord->GetArrTime() + ord->GetWaitingTime() + ord->GetServTime());
		Serving_Mtr.enqueue(mtr, -(ord->GetFinishTime() + ord->GetServTime()));
		Served_Ord.enqueue(ord, -ord->GetFinishTime());
	}

	//Assign Normal orders
	while(!VIP_Mtr_D.isEmpty() && !Norm_Ord_D.IsEmpty())
	{
		VIP_Mtr_D.dequeue(mtr, speed);
		Norm_Ord_D.GetFirst(ord);
		ord->SetWaitingTime(timestep-ord->GetArrTime());
		ord->SetServTime(ord->GetDistance()/speed);
		ord->SetFinishTime(ord->GetArrTime() + ord->GetWaitingTime() + ord->GetServTime());
		Serving_Mtr.enqueue(mtr, -(ord->GetFinishTime() + ord->GetServTime()));
		Served_Ord.enqueue(ord, -ord->GetFinishTime());
	}

	while(!Norm_Mtr_D.isEmpty() && !Norm_Ord_D.IsEmpty())
	{
		Norm_Mtr_D.dequeue(mtr, speed);
		Norm_Ord_D.GetFirst(ord);
		ord->SetWaitingTime(timestep-ord->GetArrTime());
		ord->SetServTime(ord->GetDistance()/speed);
		ord->SetFinishTime(ord->GetArrTime() + ord->GetWaitingTime() + ord->GetServTime());
		Serving_Mtr.enqueue(mtr, -(ord->GetFinishTime() + ord->GetServTime()));
		Served_Ord.enqueue(ord, -ord->GetFinishTime());
	}
}
void Restaurant::ReturnMotorcycle(int timestep)
{
	Motorcycle* mtr = NULL;
	int time;
	while (Serving_Mtr.peekFront(mtr, time))
	{
		if(-time == timestep)
		{
			Serving_Mtr.dequeue(mtr, time);
			AddMotorcycle(mtr, mtr->GetSpeed());
		}
		else
			break;
	}

}

void Restaurant::PrintToStatusBar(char* timestep)
{
	string S1, S2, S3, S4; 
	S1 ="Region A:     Orders: VIP "+ to_string(VIP_ord_A.getCount()) 
			+ "     Frozen " + to_string(Frz_Ord_A.getCount()) 
			+ "     Normal " +  to_string(Norm_Ord_A.getCount())
			+ "        Motors:   VIP "+ to_string(VIP_Mtr_A.getCount())
			+ "     Frozen " + to_string(Froz_Mtr_A.getCount())
			+ "     Normal " +  to_string(Norm_Mtr_A.getCount());

	S2 ="Region B:     Orders: VIP "+ to_string(VIP_ord_B.getCount()) 
			+ "     Frozen " + to_string(Frz_Ord_B.getCount()) 
			+ "     Normal " +  to_string(Norm_Ord_B.getCount())
			+ "        Motors:   VIP "+ to_string(VIP_Mtr_B.getCount())
			+ "     Frozen " + to_string(Froz_Mtr_B.getCount())
			+ "     Normal " +  to_string(Norm_Mtr_B.getCount());
		
	S3 ="Region C:     Orders: VIP "+ to_string(VIP_ord_C.getCount()) 
			+ "     Frozen " + to_string(Frz_Ord_C.getCount()) 
			+ "     Normal " +  to_string(Norm_Ord_C.getCount())
			+ "        Motors:   VIP " + to_string(VIP_Mtr_C.getCount())
			+ "     Frozen " + to_string(Froz_Mtr_C.getCount())
			+ "     Normal " +  to_string(Norm_Mtr_C.getCount());
		
	S4 ="Region D:     Orders: VIP "+ to_string(VIP_ord_D.getCount()) 
			+ "     Frozen " + to_string(Frz_Ord_D.getCount()) 
			+ "     Normal " +  to_string(Norm_Ord_D.getCount())
			+ "        Motors:   VIP "+ to_string(VIP_Mtr_D.getCount())
			+ "     Frozen " + to_string(Froz_Mtr_D.getCount())
			+ "     Normal " +  to_string(Norm_Mtr_D.getCount());
	pGUI->PrintMessage(timestep, S1, S2, S3, S4);
}

void Restaurant::PrintGUI()
{
	Order* pOrd;
	//vip order  for all areas
	int priority; 
	Priority_Queue<Order*> temp;
	while(VIP_ord_A.dequeue(pOrd,priority))
	{
		pGUI->AddOrderForDrawing(pOrd);
		temp.enqueue(pOrd,priority);

	}
	while(temp.dequeue(pOrd, priority))
	{
		VIP_ord_A.enqueue(pOrd,priority);
	}


	while(VIP_ord_B.dequeue(pOrd,priority))
	{
		pGUI->AddOrderForDrawing(pOrd);
		temp.enqueue(pOrd,priority);

	}
	while(temp.dequeue(pOrd, priority))
	{
		VIP_ord_B.enqueue(pOrd,priority);
	}


	while(VIP_ord_C.dequeue(pOrd,priority))
	{
		pGUI->AddOrderForDrawing(pOrd);
		temp.enqueue(pOrd,priority);

	}
	while(temp.dequeue(pOrd, priority))
	{
		VIP_ord_C.enqueue(pOrd,priority);
	}


	while(VIP_ord_D.dequeue(pOrd,priority))
	{
		pGUI->AddOrderForDrawing(pOrd);
		temp.enqueue(pOrd,priority);

	}
	while(temp.dequeue(pOrd, priority))
	{
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
}


void Restaurant ::GetOutPutFile()
{
	outFile.open("OUTPUT.txt");

	outFile<<"FT   "<<"ID   "<<"AT   "<<"WT   "<<"ST   "<<endl;
	
	Queue<Order*>SubServed;
	Order *ord;
	int FinTime;

	double TotWaitA=0,TotServA=0;
	double TotWaitB=0,TotServB=0;
	double TotWaitC=0,TotServC=0;
	double TotWaitD=0,TotServD=0;

	double CountWaitA=0,CountServA=0;
	double CountWaitB=0,CountServB=0;
	double CountWaitC=0,CountServC=0;
	double CountWaitD=0,CountServD=0;

	while(!(Served_Ord.isEmpty()))
	{
		Served_Ord.dequeue(ord,FinTime);
		
		     if(ord->GetRegion()==A_REG) 
		{CountWaitA++;CountServA++; TotWaitA+=ord->GetWaitingTime(); TotServA+=ord->GetServTime();}
		else if(ord->GetRegion()==B_REG) 
		{CountWaitB++;CountServB++; TotWaitB+=ord->GetWaitingTime(); TotServB+=ord->GetServTime();}
		else if(ord->GetRegion()==C_REG) 
		{CountWaitC++;CountServC++; TotWaitC+=ord->GetWaitingTime(); TotServC+=ord->GetServTime();}
		else if(ord->GetRegion()==D_REG) 
		{CountWaitD++;CountServD++; TotWaitD+=ord->GetWaitingTime(); TotServD+=ord->GetServTime();}
		

	  outFile<<to_string((ord->GetFinishTime()))<<"   "<<to_string(ord->GetID())<<
		"   "<<to_string(ord->GetArrTime())<<"   "<<to_string(ord->GetWaitingTime())<<
		"   "<<to_string(ord->GetServTime())<<endl;
		SubServed.enqueue(ord);
	}

	outFile<<"......................."<<endl;
	outFile<<"......................."<<endl;

	int totA=VIP_ord_A.getCount()+Frz_Ord_A.getCount()+Norm_Ord_A.getCount();
	int totB=VIP_ord_B.getCount()+Frz_Ord_B.getCount()+Norm_Ord_B.getCount();
	int totC=VIP_ord_C.getCount()+Frz_Ord_C.getCount()+Norm_Ord_C.getCount();
	int totD=VIP_ord_D.getCount()+Frz_Ord_D.getCount()+Norm_Ord_D.getCount();
  
  int tmotA=Norm_Mtr_A.getCount()+Froz_Mtr_A.getCount()+VIP_Mtr_A.getCount();
  int tmotB=Norm_Mtr_B.getCount()+Froz_Mtr_B.getCount()+VIP_Mtr_B.getCount();
  int tmotC=Norm_Mtr_C.getCount()+Froz_Mtr_C.getCount()+VIP_Mtr_C.getCount();
  int tmotD=Norm_Mtr_D.getCount()+Froz_Mtr_D.getCount()+VIP_Mtr_D.getCount();

	outFile<<"Region A:"<<endl;
	outFile<<"     Orders:"<<to_string(totA)<<"		[Norm:"<<to_string(Norm_Ord_A.getCount())<<",Froz:"<<to_string(Frz_Ord_A.getCount())<<",VIP:"<<to_string(VIP_ord_A.getCount())<<"]"<<endl;
	outFile<<"     Motors:"<<to_string(tmotA)<<"	 [Norm:"<<to_string(Norm_Mtr_A.getCount())<<",Froz:"<<to_string(Froz_Mtr_A.getCount())<<",VIP:"<<to_string(VIP_Mtr_A.getCount())<<"]"<<endl;
	if(CountServA!=0 && CountWaitA!=0)
	outFile<<"     Avg Wait ="<<to_string(TotWaitA/CountWaitA)<<" , Avg Serv ="<<to_string(TotServA/CountServA)<<endl;


	outFile<<"Region B:"<<endl;
	outFile<<"     Orders:"<<to_string(totB)<<"		[Norm:"<<to_string(Norm_Ord_B.getCount())<<",Froz:"<<to_string(Frz_Ord_B.getCount())<<",VIP:"<<to_string(VIP_ord_B.getCount())<<"]"<<endl;
	outFile<<"     Motors:"<<to_string(tmotB)<<"	 [Norm:"<<to_string(Norm_Mtr_B.getCount())<<",Froz:"<<to_string(Froz_Mtr_B.getCount())<<",VIP:"<<to_string(VIP_Mtr_B.getCount())<<"]"<<endl;
	if(CountServB!=0 && CountWaitB!=0)
	outFile<<"     Avg Wait ="<<to_string(TotWaitB/CountWaitB)<<" , Avg Serv ="<<to_string(TotServB/CountServB)<<endl;


	outFile<<"Region C:"<<endl;
	outFile<<"     Orders:"<<to_string(totC)<<"		[Norm:"<<to_string(Norm_Ord_C.getCount())<<",Froz:"<<to_string(Frz_Ord_C.getCount())<<",VIP:"<<to_string(VIP_ord_C.getCount())<<"]"<<endl;
	outFile<<"     Motors:"<<to_string(tmotC)<<"	 [Norm:"<<to_string(Norm_Mtr_C.getCount())<<",Froz:"<<to_string(Froz_Mtr_C.getCount())<<",VIP:"<<to_string(VIP_Mtr_C.getCount())<<"]"<<endl;
	if(CountServC!=0 && CountWaitC!=0)
	outFile<<"     Avg Wait ="<<to_string(TotWaitC/CountWaitC)<<" , Avg Serv ="<<to_string(TotServC/CountServC)<<endl;


	outFile<<"Region D:"<<endl;
	outFile<<"     Orders:"<<to_string(totD)<<"		[Norm:"<<to_string(Norm_Ord_D.getCount())<<",Froz:"<<to_string(Frz_Ord_D.getCount())<<",VIP:"<<to_string(VIP_ord_D.getCount())<<"]"<<endl;
	outFile<<"     Motors:"<<to_string(tmotD)<<"	 [Norm:"<<to_string(Norm_Mtr_D.getCount())<<",Froz:"<<to_string(Froz_Mtr_D.getCount())<<",VIP:"<<to_string(VIP_Mtr_D.getCount())<<"]"<<endl;
	if(CountServD!=0 && CountWaitD!=0)
	outFile<<"     Avg Wait ="<<to_string(TotWaitD/CountWaitD)<<" , Avg Serv ="<<to_string(TotServD/CountServD)<<endl;

	while(!SubServed.isEmpty())
	{
		SubServed.dequeue(ord);
		Served_Ord.enqueue(ord,-1*(ord->GetWaitingTime()));
	}
	outFile.close();
}

bool Restaurant::isOpen()
{
	return !Norm_Ord_A.IsEmpty()||!Norm_Ord_B.IsEmpty()||!Norm_Ord_C.IsEmpty()||!Norm_Ord_D.IsEmpty()||
		!Frz_Ord_A.isEmpty()||!Frz_Ord_B.isEmpty()||!Frz_Ord_C.isEmpty()||!Frz_Ord_D.isEmpty()||
		!VIP_ord_A.isEmpty()||!VIP_ord_B.isEmpty()||!VIP_ord_C.isEmpty()||!VIP_ord_D.isEmpty()||
		!EventsQueue.isEmpty() || !Serving_Mtr.isEmpty();
}