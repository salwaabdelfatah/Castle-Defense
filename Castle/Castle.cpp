#include "Castle.h"
void Castle::Init(double _towerHealth, int _maxTargets, double _towerPower)
{
    for (int i = 0; i < 4; i++)
    {
        // The tower id and its region are the same number (A = 0 ... D = 3).
        towers[i].Init(i, static_cast<RegionType>(i), _towerHealth, _maxTargets, _towerPower);
    }
}

Tower& Castle::GetTower(RegionType region)
{
    return towers[region];
}


const Tower& Castle::GetTower(RegionType region) const
{
    return towers[region];
}

// 
bool Castle::AllTowersDestroyed() const 
{
    for (int i = 0; i < 4; i++)
    {
        if (!towers[i].IsDestroyed())
            return false;
    }
    return true;
}