#ifndef ENEMY_H
#define ENEMY_H
#include "../Castle-Defense/Defs.h"
#include "../CMUgraphicsLib/colors.h"
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
	int NextActionTime;   //first time step at which this enemy may act
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
	void SetNextActionTime(int _time);
	int  GetNextActionTime();

	int GetID() const;
	EnemyType GetType() const;
	RegionType GetRegion() const;
	int GetArrivalTime() const;
	double GetHealth() const;
	double GetOriginalHealth() const;
	int GetPower() const;
	int GetReloadedPeriod() const;
	int GetDistance() const;
	EnemyState GetState() const;
	int GetFirstShotTime() const;
	int GetKillTime() const;
	int GetFrozenUntil() const;
	color GetColor() const;

	bool IsActive(int _time);
	bool IsFrozen(int _time);

	virtual void Move(int _time) =0;
	virtual void Act(int _time) =0;   //each enemy type defines its own action
	bool CanAct(int _time);
	void ScheduleNextAction(int _time);
	virtual ~Enemy();

 };
#endif