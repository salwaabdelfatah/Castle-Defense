#ifndef HEALER_H
#define HEALER_H
#include "Enemy.h"
class Healer :public Enemy 
{
public:
	Healer(int _id, RegionType _region, int _arrivaltime, double _health, int _power, int _reloadedperiod);
	void Move(int _time);
	void Act(int _time);
	double HealAmount();
	~Healer();

};
#endif