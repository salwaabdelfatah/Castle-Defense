#include "Tower.h"
const double Tower::FREEZE_THRESHOLD = 50.0;

Tower::Tower()
    : id(0), region(REGION_A), health(0), power(0), maxTargets(0),
    iceAccumulated(0), frozenFrom(0), frozenUntil(-1), damageTaken(0)
{
}

void Tower::Init(int _id, RegionType _region, double _health, int _maxTargets, double _power)
{
    id = _id;
    region = _region;
    health = _health;
    maxTargets = _maxTargets;
    power = _power;

    iceAccumulated = 0;
    frozenFrom = 0;
    frozenUntil = -1;
    damageTaken = 0;
}
#pragma region getter
int Tower::GetID() const { return id; }

RegionType Tower::GetRegion() const { return region; }

double Tower::GetHealth() const { return health; }

double Tower::GetPower() const { return power; }

int Tower::GetMaxTargets() const { return maxTargets; }

double Tower::GetDamageTaken() const { return damageTaken; }

double Tower::GetIceAccumulated() const { return iceAccumulated; }
#pragma endregion


bool Tower::IsDestroyed() const
{
    return health <= 0;
}
bool Tower::IsFrozen(int currentTime) const
{
    return currentTime >= frozenFrom && currentTime <= frozenUntil;
}

void Tower::TakeDamage(double damage)
{
    if (damage <= 0 || IsDestroyed())
        return;
    //  10        9
    if (damage > health)
        damage = health;


    health -= damage; // 9 - 9 = 0
    damageTaken += damage; // 0 + 9 = 9
}

bool Tower::AddIce(double amount)
{
    if (amount <= 0 || IsDestroyed())
        return false;

    iceAccumulated += amount;

    if (iceAccumulated >= FREEZE_THRESHOLD)
    {
        iceAccumulated = 0;
        return true;
    }
    return false;
}

void Tower::Freeze(int fromStep, int steps)
{
    if (steps <= 0)
        return;

    frozenFrom = fromStep;
    frozenUntil = fromStep + steps - 1;
}
