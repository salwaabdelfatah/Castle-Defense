#ifndef DEFS_H
#define DEFS_H



enum RegionType
{
    REGION_A,
    REGION_B,
    REGION_C,
    REGION_D
};

enum EnemyType
{
    FIGHTER = 1,
    HEALER = 2,
    FREEZER = 3
};

enum EnemyState
{
    INACTIVE,
    ACTIVE,
    FROZEN,
    KILLED
};

 const int START_DISTANCE = 60;
 const int MIN_DISTANCE = 2;
 const int MAX_KILLS_PER_STEP = 4;
 const int HEALER_PERCENT_MAX = 20;


RegionType NextRegion(RegionType region);

#endif
