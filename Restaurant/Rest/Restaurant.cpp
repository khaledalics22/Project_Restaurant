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


void Restaurant::MODE_INTR_FN()
{
	int current_time_step=1;
	char timestep[10];
	while(isOpen())
	{
		itoa(current_time_step,timestep,10);	
		if(!EventsQueue.isEmpty())
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
	itoa(current_time_step,timestep,10);	
	PrintToStatusBar(timestep);
	pGUI->UpdateInterface();
		GetOutPutFile(); 
}

void Restaurant::MODE_STEP_FN()
{
		int current_time_step=1;
	char timestep[10];
	while(isOpen())
	{
		itoa(current_time_step,timestep,10);	
		if(!EventsQueue.isEmpty())
	    	ExecuteEvents(current_time_step);
		ReturnMotorcycle(current_time_step);
		AutoPromotion(current_time_step);
		PrintGUI();
		PrintToStatusBar(timestep);
		pGUI->UpdateInterface();
		pGUI->ResetDrawingList();
		AssignToMotorcycle(current_time_step);

	Sleep(1000);
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

	while(isOpen())
	{
		itoa(current_time_step,timestep,10);	
		if (!EventsQueue.isEmpty())
			ExecuteEvents(current_time_step);
		PrintGUI();
		ReturnMotorcycle(current_time_step);
		AutoPromotion(current_time_step);
		AssignToMotorcycle(current_time_step);
		PrintToStatusBar(timestep);
		current_time_step++;
	}
	GetOutPutFile(); 

}

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

	deleteMotorcycle(Serving_Mtr);

	DeleteOrdersList(Norm_Ord_A);
	DeleteOrdersList(Norm_Ord_B);
	DeleteOrdersList(Norm_Ord_C);
	DeleteOrdersList(Norm_Ord_D);

	DeleteOrdersQueue(Frz_Ord_A);
	DeleteOrdersQueue(Frz_Ord_B);
	DeleteOrdersQueue(Frz_Ord_C);
	DeleteOrdersQueue(Frz_Ord_D);

	DeleteOrdersPrio(VIP_ord_A);
	DeleteOrdersPrio(VIP_ord_B);
	DeleteOrdersPrio(VIP_ord_C);
	DeleteOrdersPrio(VIP_ord_D);


	DeleteOrdersQueue(DEMO_Queue);
	DeleteOrdersPrio(Served_Ord);
	
	delete pGUI;
}

void Restaurant::ReadData()
{
	ifstream infile;
	infile.open("InputFile6.txt");

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
	int x;
	Motorcycle* m = NULL;
	while (toDelete.dequeue(m,x))
	{
		delete m;
	}
	toDelete.Clear();
}
void Restaurant:: DeleteOrdersList(List<Order*>& l)
{
	Order *ord=NULL;
	while(l.GetFirst(ord))
	{delete ord;}
	l.Clear();
}
void Restaurant::DeleteOrdersQueue(Queue<Order*>& q)
{
	Order *ord=NULL;
	while(q.dequeue(ord))
		{delete ord;}
	q.Clear();
}
void Restaurant::DeleteOrdersPrio(Priority_Queue<Order*>& p)
{
	Order *ord=NULL;
	int x;
	while(p.dequeue(ord,x))
	{delete ord;}
	p.Clear();
}


void Restaurant::AutoPromotion(int time_step)
{
	int t;
	bool flag = true;
	Order* ord;

	while(Norm_Ord_A.IsEmpty() && flag)
	{
		if(Norm_Ord_A.GetFirst(ord))
		{
			t = ord->GetArrTime();
			if(time_step - t >= AutoPromLim)
				PromoteOrder(ord->GetID(), 0);
			else
			{
				Norm_Ord_A.InsertBeg(ord);
				flag = false;
			}
		}
		else
			flag = false;
	}

	flag = true;
	while(Norm_Ord_B.IsEmpty() && flag)
	{
		if(Norm_Ord_B.GetFirst(ord))
		{
			t = ord->GetArrTime();
			if(time_step - t >= AutoPromLim)
				PromoteOrder(ord->GetID(), 0);
			else
			{
				Norm_Ord_B.InsertBeg(ord);
				flag = false;
			}
		}
		else
			flag = false;
	}

	flag = true;
	while(Norm_Ord_C.IsEmpty() && flag)
	{
		if(Norm_Ord_C.GetFirst(ord))
		{
			t = ord->GetArrTime();
			if(time_step - t >= AutoPromLim)
				PromoteOrder(ord->GetID(), 0);
			else
			{
				Norm_Ord_C.InsertBeg(ord);
				flag = false;
			}
		}
		else
			flag = false;
	}

	flag = true;
	while(Norm_Ord_D.IsEmpty() && flag)
	{
		if(Norm_Ord_D.GetFirst(ord))
		{
			t = ord->GetArrTime();
			if(time_step - t >= AutoPromLim)
				PromoteOrder(ord->GetID(), 0);
			else
			{
				Norm_Ord_D.InsertBeg(ord);
				flag = false;
			}
		}
		else
			flag = false;
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


bool Restaurant::isOpen()
{
	return !Norm_Ord_A.IsEmpty()||!Norm_Ord_B.IsEmpty()||!Norm_Ord_C.IsEmpty()||!Norm_Ord_D.IsEmpty()||
		!Frz_Ord_A.isEmpty()||!Frz_Ord_B.isEmpty()||!Frz_Ord_C.isEmpty()||!Frz_Ord_D.isEmpty()||
		!VIP_ord_A.isEmpty()||!VIP_ord_B.isEmpty()||!VIP_ord_C.isEmpty()||!VIP_ord_D.isEmpty()||
		!EventsQueue.isEmpty() || !Serving_Mtr.isEmpty();
}

void Restaurant ::GetOutPutFile()
{
	outFile.open("OUTPUT.txt");

	outFile<<"FT      "<<"ID      "<<"AT      "<<"WT      "<<"ST      "<<endl;
		
	Order *ord;
	int FinTime;

	int CountRegA=0, CountMotA=Norm_Mtr_A.getCount()+Froz_Mtr_A.getCount()+VIP_Mtr_A.getCount();
	int CountRegB=0, CountMotB=Norm_Mtr_B.getCount()+Froz_Mtr_B.getCount()+VIP_Mtr_B.getCount();
	int CountRegC=0, CountMotC=Norm_Mtr_C.getCount()+Froz_Mtr_C.getCount()+VIP_Mtr_C.getCount();
	int CountRegD=0, CountMotD=Norm_Mtr_D.getCount()+Froz_Mtr_D.getCount()+VIP_Mtr_D.getCount();
	
	int CountNrmA=0,CountFrzA=0,CountVIPA=0;
	int CountNrmB=0,CountFrzB=0,CountVIPB=0;
	int CountNrmC=0,CountFrzC=0,CountVIPC=0;
	int CountNrmD=0,CountFrzD=0,CountVIPD=0;

	double TotWaitA=0,TotServA=0;
	double TotWaitB=0,TotServB=0;
	double TotWaitC=0,TotServC=0;
	double TotWaitD=0,TotServD=0;

	double CountWaitA=0,CountServA=0;
	double CountWaitB=0,CountServB=0;
	double CountWaitC=0,CountServC=0;
	double CountWaitD=0,CountServD=0;

	double avgWaitA,avgWaitB,avgWaitC,avgWaitD;
	double avgServA,avgServB,avgServC,avgServD;
	
	
	while(!(Served_Ord.isEmpty()))
	{
		Served_Ord.dequeue(ord,FinTime);


		     if(ord->GetRegion()==A_REG) 
		{
			if(ord->GetType()==TYPE_NRM)  CountNrmA++;
	   else if(ord->GetType()==TYPE_FROZ) CountFrzA++;
	   else if(ord->GetType()==TYPE_VIP)  CountVIPA++;

			if(ord->GetWaitingTime()!=0)
			{CountWaitA++; TotWaitA+=ord->GetWaitingTime();}
			CountServA++;  TotServA+=ord->GetServTime();
			CountRegA++;
		}

		else if(ord->GetRegion()==B_REG) 
		{
			if(ord->GetType()==TYPE_NRM)  CountNrmB++;
	   else if(ord->GetType()==TYPE_FROZ) CountFrzB++;
	   else if(ord->GetType()==TYPE_VIP)  CountVIPB++;

			if(ord->GetWaitingTime()!=0)
			{CountWaitB++;TotWaitB+=ord->GetWaitingTime();}
			CountServB++; TotServB+=ord->GetServTime();
			CountRegB++;
		}

		else if(ord->GetRegion()==C_REG) 
		{
			if(ord->GetType()==TYPE_NRM)  CountNrmC++;
	   else if(ord->GetType()==TYPE_FROZ) CountFrzC++;
	   else if(ord->GetType()==TYPE_VIP)  CountVIPC++;

			if(ord->GetWaitingTime()!=0)
			{CountWaitC++; TotWaitC+=ord->GetWaitingTime();}
			CountServC++;  TotServC+=ord->GetServTime();
			CountRegC++;
		}

		else if(ord->GetRegion()==D_REG) 
		{
			if(ord->GetType()==TYPE_NRM)  CountNrmD++;
	   else if(ord->GetType()==TYPE_FROZ) CountFrzD++;
	   else if(ord->GetType()==TYPE_VIP)  CountVIPD++;

			if(ord->GetWaitingTime()!=0)
			{CountWaitD++; TotWaitD+=ord->GetWaitingTime();}
			CountServD++;  TotServD+=ord->GetServTime();
			CountRegD++;
		}

	  outFile<<to_string((ord->GetFinishTime()))<<"       "<<to_string(ord->GetID())<<
		"       "<<to_string(ord->GetArrTime())<<"       "<<to_string(ord->GetWaitingTime())<<
		"       "<<to_string(ord->GetServTime())<<endl;
	  delete ord;
	}

	outFile<<"......................."<<endl;
	outFile<<"......................."<<endl;



	outFile<<"Region A:"<<endl;
	outFile<<"     Orders:"<<to_string(CountRegA)<<"		[Norm:"<<to_string(CountNrmA)<<",Froz:"<<to_string(CountFrzA)<<",VIP:"<<to_string(CountVIPA)<<"]"<<endl;
	outFile<<"     Motors:"<<to_string(CountMotA)<<"	        [Norm:"<<to_string(Norm_Mtr_A.getCount())<<",Froz:"<<to_string(Froz_Mtr_A.getCount())<<",VIP:"<<to_string(VIP_Mtr_A.getCount())<<"]"<<endl;
	
	avgServA=TotServA/CountServA;
	if(CountWaitA!=0)
		avgWaitA=TotWaitA/CountWaitA;
	else avgWaitA=0;
	outFile<<"     Avg Wait ="<<to_string(avgWaitA)<<" , Avg Serv ="<<to_string(avgServA)<<endl;



	outFile<<"Region B:"<<endl;
	outFile<<"     Orders:"<<to_string(CountRegB)<<"		[Norm:"<<to_string(CountNrmB)<<",Froz:"<<to_string(CountFrzB)<<",VIP:"<<to_string(CountVIPB)<<"]"<<endl;
	outFile<<"     Motors:"<<to_string(CountMotB)<<"	        [Norm:"<<to_string(Norm_Mtr_B.getCount())<<",Froz:"<<to_string(Froz_Mtr_B.getCount())<<",VIP:"<<to_string(VIP_Mtr_B.getCount())<<"]"<<endl;
	
	avgServB=TotServB/CountServB;
	if(CountWaitB!=0)
		avgWaitB=TotWaitB/CountWaitB;
	else avgWaitB=0;
	outFile<<"     Avg Wait ="<<to_string(avgWaitB)<<" , Avg Serv ="<<to_string(avgServB)<<endl;

	outFile<<"Region C:"<<endl;
	outFile<<"     Orders:"<<to_string(CountRegC)<<"		[Norm:"<<to_string(CountNrmC)<<",Froz:"<<to_string(CountFrzC)<<",VIP:"<<to_string(CountVIPC)<<"]"<<endl;
	outFile<<"     Motors:"<<to_string(CountMotC)<<"	        [Norm:"<<to_string(Norm_Mtr_C.getCount())<<",Froz:"<<to_string(Froz_Mtr_C.getCount())<<",VIP:"<<to_string(VIP_Mtr_C.getCount())<<"]"<<endl;
	
	avgServC=TotServC/CountServC;
	if(CountWaitC!=0)
		avgWaitC=TotWaitC/CountWaitC;
	else avgWaitC=0;
	outFile<<"     Avg Wait ="<<to_string(avgWaitC)<<" , Avg Serv ="<<to_string(avgServC)<<endl;

	outFile<<"Region D:"<<endl;
	outFile<<"     Orders:"<<to_string(CountRegD)<<"		[Norm:"<<to_string(CountNrmD)<<",Froz:"<<to_string(CountFrzD)<<",VIP:"<<to_string(CountVIPD)<<"]"<<endl;
	outFile<<"     Motors:"<<to_string(CountMotD)<<"	        [Norm:"<<to_string(Norm_Mtr_D.getCount())<<",Froz:"<<to_string(Froz_Mtr_D.getCount())<<",VIP:"<<to_string(VIP_Mtr_D.getCount())<<"]"<<endl;
	
	avgServD=TotServD/CountServD;
	if(CountWaitD!=0)
		avgWaitD=TotWaitD/CountWaitD;
	else avgWaitD=0;
	outFile<<"     Avg Wait ="<<to_string(avgWaitD)<<" , Avg Serv ="<<to_string(avgServD)<<endl;


	outFile<<endl<<"Restaurant:"<<endl;
	outFile<<"     Orders:"<<to_string(CountRegA+CountRegB+CountRegC+CountRegD)<<"		[Norm:"<<to_string(CountNrmA+CountNrmB+CountNrmC+CountNrmD)<<",Froz:"<<to_string(CountFrzA+CountFrzB+CountFrzC+CountFrzD)<<",VIP:"<<to_string(CountVIPA+CountVIPB+CountVIPC+CountVIPD)<<"]"<<endl;
	outFile<<"     Motors:"<<to_string(CountMotA+CountMotB+CountMotC+CountMotD)<<"	        [Norm:"<<to_string(Norm_Mtr_A.getCount()+Norm_Mtr_B.getCount()+Norm_Mtr_C.getCount()+Norm_Mtr_D.getCount())<<",Froz:"<<to_string(Froz_Mtr_A.getCount()+Froz_Mtr_B.getCount()+Froz_Mtr_C.getCount()+Froz_Mtr_D.getCount())<<",VIP:"<<to_string(VIP_Mtr_A.getCount()+VIP_Mtr_B.getCount()+VIP_Mtr_C.getCount()+VIP_Mtr_D.getCount())<<"]"<<endl;
	outFile<<"     Avg Wait ="<<to_string((avgWaitA+avgWaitB+avgWaitC+avgWaitD)/4)<<" , Avg Serv ="<<to_string((avgServA+avgServB+avgServC+avgServD)/4)<<endl;

	outFile.close();
}