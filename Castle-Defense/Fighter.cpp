#include "Fighter.h"
Fighter::Fighter(int _id, RegionType _region, int _arrivaltime, double _health, int _power, int _reloadedperiod)
    : Enemy(_id, FIGHTER, _region, _arrivaltime, _health, _power, _reloadedperiod)
{
}

Fighter::~Fighter()
{
}

void Fighter::Move(int _time) {
    MoveOneStep(_time);
}

double Fighter::Act(int _time)
{
    if(!CanAct(_time))
        return 0;
    ScheduleNextAction(_time);
    //DET Equation it means the Damage The Enemy Can Cause To The Tower
    double k = (Health < 0.5 * OriginalHealth) ? 0.5 : 1.0;
    double DET = (k * Power) / Distance;
    return DET;
}