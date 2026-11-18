#ifndef FIGHTER_H
#define FIGHTER_H
#include "Enemy.h"
class Fighter:public Enemy 
{
public:
	Fighter(int _id, RegionType _region, int _arrivaltime, double _health, int _power, int _reloadedperiod);
	void Move(int _time);
	void Attack();
	 ~Fighter();
};
#endif