//#include "Drawing.h"
#include "Rest\Restaurant.h"
#include "GUI\GUI.h"
int main()
{
	bool go=true; 
	while (go)
	{
	Restaurant* pRest = new Restaurant;
	pRest->RunSimulation();
	//Sleep(2000);
	PROG_MODE input=pRest->Readinput();
	go=(input==0)?true:false; 
	delete pRest; 
	if (input == 1)
	break; 
	}
	return 0;
}
