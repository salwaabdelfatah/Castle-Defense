#include "Freezer.h"
Freezer::Freezer(int _id, RegionType _region, int _arrivaltime, double _health, int _power, int _reloadedperiod)
	: Enemy(_id, FREZEER, _region, _arrivaltime, _health, _power, _reloadedperiod)
{
}

Freezer::~Freezer()
{
}

void Freezer::Move(){}

void Freezer::Attack()
{
	// Phase 2: throw ice on the tower
}