#ifndef FREEZER_H
#define FREEZER_H
#include "Enemy.h"
class Freezer : public Enemy
{
public:
	Freezer(int _id, RegionType _region, int _arrivaltime, double _health, int _power, int _reloadedperiod);
	void Move(int _time);
	double Act(int _time);
	double IceAmount();
	virtual ~Freezer();
};
#endif