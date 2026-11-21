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

int Enemy::GetID() const { return Id; }
EnemyType Enemy::GetType() const { return Type; }
RegionType Enemy::GetRegion() const { return Region; }
int Enemy::GetArrivalTime() const { return ArrivalTime; }
double Enemy::GetHealth() const { return Health; }
double Enemy::GetOriginalHealth() const { return OriginalHealth; }
int Enemy::GetPower() const { return Power; }
int Enemy::GetReloadedPeriod() const { return ReloadPeriod; }
int Enemy::GetDistance() const { return Distance; }
EnemyState Enemy::GetState() const { return State; }
int Enemy::GetFirstShotTime() const { return FirstShotTime; }
int Enemy::GetKillTime() const { return KillTime; }
int Enemy::GetFrozenUntil() const { return FrozenUntil; }

color Enemy::GetColor() const
{
	if (Type == HEALER)
		return ORANGERED;
	if (Type == FREEZER)
		return DEEPSKYBLUE;
	return DARKBLUE;
}
void Enemy::MoveOneStep(int _time)
{
	if (State == FROZEN)
		return;

	if (Distance <= MIN_DISTANCE)
		return;

	bool weak = Health < 0.5 * OriginalHealth;
	int elapsed = _time - ArrivalTime;
	if (weak && elapsed % 2 != 0)
		return;

	Distance--;
}