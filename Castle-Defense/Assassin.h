#ifndef ASSASSIN_H
#define ASSASSIN_H
#include "Enemy.h"

class Assassin : public Enemy
{
public:
	Assassin(int _id, RegionType _region, int _arrivalTime, double _health, int _power, int _reloadPeriod);
	virtual ~Assassin();

	void Move(int _time);
	double Act(int _time);
	bool IsHidden(int _time);   // true while the assassin is hidden from towers
};

#endif
