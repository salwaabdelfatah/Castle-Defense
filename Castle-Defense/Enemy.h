#ifndef ENEMY_H
#define ENEMY_H
#include "Defs.h"
class Enemy 
{
protected:
	int Id;
	EnemyType Type;
	RegionType Region;
	int ArrivalTime;
	double Health;
	double OriginalHealth;
	int	Power;
	int	ReloadPeriod;
	int Distance;
	EnemyState State;
	int FirstShotTime;
	int KillTime;
	int FrozenUntil;
	void MoveOneStep(int _time);
public:
	Enemy(int _id, EnemyType _type, RegionType _region, int _arrivaltime,double _health, int _power, int _reloadedperiod);

	void SetID(int _id);
	void SetType(EnemyType _type);
	void SetRegion(RegionType _region);
	void SetArrivalTime(int _arrivaltime);
	void SetHealth(double _health);
	void SetPower(int _power);
	void SetReloadedPeriod(int _reloadedperiod);
	void SetDistance(int _distance);
	void SetState(EnemyState _state);
	void SetFirstShotTime(int _time);
	void SetKillTime(int _time);
	void SetFrozenUntil(int _time);

	int GetID();
	EnemyType GetType();
	RegionType GetRegion();
	int GetArrivalTime();
	double GetHealth();
	double GetOriginalHealth();
	int GetPower();
	int GetReloadedPeriod();
	int GetDistance();
	EnemyState GetState();
	int GetFirstShotTime();
	int GetKillTime();
	int GetFrozenUntil();

	bool IsActive(int _time);

	virtual void Move(int _time) = 0;
	virtual void Attack() = 0;

	virtual ~Enemy();

 };
#endif