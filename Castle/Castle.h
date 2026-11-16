#pragma once
#include "../Defs.h"
#include "../Tower/Tower.h"
class Castle
{
private:
    Tower towers[4];     // index = region (REGION_A = 0 ... REGION_D = 3)

public:
    //Gives each tower its id and region (A..D) and the same
    //starting values read from the first line of the input file (TH N TP).
    void Init(double _towerHealth, int _maxTargets, double _towerPower);

    //Returns the tower that guards the given region.
    Tower& GetTower(RegionType region);
    const Tower& GetTower(RegionType region) const;

    //True when all four towers are destroyed (the game is lost).
    bool AllTowersDestroyed() const;
};