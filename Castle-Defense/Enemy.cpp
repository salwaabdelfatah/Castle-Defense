#include "Enemy.h"

Enemy::Enemy(int _id, EnemyType _type, RegionType _region, int _arrivaltime, double _health, int _power, int _reloadedperiod)
{
	Id = _id;
	Type = _type;
	Region = _region;
	ArrivalTime = _arrivaltime;
	Health = _health;
	OriginalHealth = _health;
	Power = _power;
	ReloadPeriod = _reloadedperiod;
	Distance = START_DISTANCE;
	State = INACTIVE;
	FirstShotTime = -1;
	KillTime = -1;
	FrozenUntil = -1;
	NextActionTime = _arrivaltime; //First Action happens at arrival 
}

Enemy::~Enemy()
{
}

bool Enemy::IsActive(int _time)
{
	return ArrivalTime <= _time && Health > 0;
}

void Enemy::SetID(int _id) { Id = _id; }
void Enemy::SetType(EnemyType _type) { Type = _type; }
void Enemy::SetRegion(RegionType _region) { Region = _region; }
void Enemy::SetArrivalTime(int _arrivaltime) { ArrivalTime = _arrivaltime; }
void Enemy::SetHealth(double _health) { Health = _health; }
void Enemy::SetPower(int _power) { Power = _power; }
void Enemy::SetReloadedPeriod(int _reloadedperiod) { ReloadPeriod = _reloadedperiod; }
void Enemy::SetDistance(int _distance) { Distance = _distance; }
void Enemy::SetState(EnemyState _state) { State = _state; }
void Enemy::SetFirstShotTime(int _time) { FirstShotTime = _time; }
void Enemy::SetKillTime(int _time) { KillTime = _time; }
void Enemy::SetFrozenUntil(int _time) { FrozenUntil = _time; }

int Enemy::GetID() { return Id; }
EnemyType Enemy::GetType() { return Type; }
RegionType Enemy::GetRegion() { return Region; }
int Enemy::GetArrivalTime() { return ArrivalTime; }
double Enemy::GetHealth() { return Health; }
double Enemy::GetOriginalHealth() { return OriginalHealth; }
int Enemy::GetPower() { return Power; }
int Enemy::GetReloadedPeriod() { return ReloadPeriod; }
int Enemy::GetDistance() { return Distance; }
EnemyState Enemy::GetState() { return State; }
int Enemy::GetFirstShotTime() { return FirstShotTime; }
int Enemy::GetKillTime() { return KillTime; }
int Enemy::GetFrozenUntil() { return FrozenUntil; }
bool Enemy::IsFrozen(int _time)
{
	return State==FROZEN && _time<FrozenUntil; //it means the enmey is still frozen for period of time 
}

void Enemy::MoveOneStep(int _time)
{
	if (IsFrozen(_time))
		return;

	if (Distance <= MIN_DISTANCE)
		return;

	bool weak = Health < 0.5 * OriginalHealth;
	int elapsed = _time - ArrivalTime; // move 1 meter after 2 time step 
	if (weak && elapsed % 2 != 0)
		return;

	Distance--;
}

void Enemy::SetNextActionTime(int _time) { NextActionTime = _time; }
int  Enemy::GetNextActionTime() { return NextActionTime; }
bool Enemy::CanAct(int _time)
{
	if (!IsActive(_time))
		return false;
	if (IsFrozen(_time))
		return false;
	return _time >= NextActionTime; // if the enemy is in its reload period after it attacks or throw ice on a tower 
}
void Enemy::ScheduleNextAction(int _time)
{
	NextActionTime = _time+ ReloadPeriod +1; // when the enemy can attack again ? after its reload period pass 
}