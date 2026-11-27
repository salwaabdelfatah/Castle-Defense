#ifndef HEALER_H
#define HEALER_H
#include "Enemy.h"
class Healer : public Enemy
{
public:
	Healer(int _id, RegionType _region, int _arrivaltime, double _health, int _power, int _reloadedperiod);
	void Move(int _time);
	double Act(int _time);
	double HealAmount();
	bool CanHeal(Enemy* _target);
	void ApplyHeal(Enemy* _target, double _amount);
	virtual ~Healer();
};
#endif