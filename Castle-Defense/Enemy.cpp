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
	ReloadPeriod =_reloadedperiod;
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
	return ArrivalTime<=_time && Health>0;
}

void Enemy::SetID(int _id) { Id = _id;}
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
void Enemy:: Move(int _time) {
	if (State == FROZEN) {
		return;
	}
	if (Distance <= MIN_DISTANCE) {
		return;
	}
	bool weak = Health < 0.5 * OriginalHealth;
	int time = _time - ArrivalTime;
	if (weak && (time % 2 != 0)) {
		return;
	}
	Distance--; 

}