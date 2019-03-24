#ifndef __MOTORCYCLE_H_
#define __MOTORCYCLE_H_


#include "..\Defs.h"

#pragma once
class Motorcycle	
{
	int ID;
	ORD_TYPE type;	//for each order type there is a corresponding motorcycle type 
	int speed;		//meters it can move in one clock tick (in one timestep)
	REGION	region;	//region of the motorcycle
	STATUS	status;	//idle or in-service

public:
	Motorcycle();
	Motorcycle(int id, ORD_TYPE t, int Speed, REGION RE,STATUS s=IDLE);

	int GetSpeed() const;
	void SetSpeed(int s);

	ORD_TYPE GetType() const;
	void SetType(ORD_TYPE t);

	int GetID() const;
	void SetID(int id);

	REGION GetRegion() const;
	void SetRegion(REGION r);

	void SetStatus(STATUS s);
	bool IsAvailable() const;

	virtual ~Motorcycle();
};

#endif