#ifndef VAMPIRE_H
#define VAMPIRE_H
#include "Enemy.h"

class Vampire : public Enemy
{
public:
	Vampire(int _id, RegionType _region, int _arrivalTime, double _health, int _power, int _reloadPeriod);
	virtual ~Vampire();

	void Move(int _time);
	double Act(int _time);   // returns the damage dealt to the tower
};

#endif