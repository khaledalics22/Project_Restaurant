#include "Motorcycle.h"


Motorcycle::Motorcycle()
{
}
Motorcycle::Motorcycle(int id, ORD_TYPE t, int Speed, REGION RE,STATUS s)
{
	SetID(id);
	SetType(t);
	SetSpeed(Speed);
	SetRegion(RE);
}

int Motorcycle::GetSpeed() const
{
	return speed;
}

void Motorcycle::SetSpeed(int s)
{
	speed = s>0? s:0;
}

ORD_TYPE Motorcycle::GetType() const
{
	return type;
}

void Motorcycle::SetType(ORD_TYPE t)
{
	type = t;
}

int Motorcycle::GetID() const
{
	return ID;
}

void Motorcycle::SetID(int id)
{
	ID = id;
}

REGION Motorcycle::GetRegion() const
{
	return region;
}

void Motorcycle::SetRegion(REGION r)
{
	region = r;
}


void Motorcycle::SetStatus(STATUS s)
{
	status = s;
}

bool Motorcycle::IsAvailable(void) const
{
	if(status == IDLE)
		return true;
	else
		return false;
}


Motorcycle::~Motorcycle()
{
}
