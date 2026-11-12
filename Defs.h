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
    FREZEER = 3
};

enum EnemyState
{
    INACTIVE,
    ACTIVE,
    FROZEN,
    KILLED
};

extern const int START_DISTANCE = 60;
extern const int MIN_DISTANCE = 2;
extern const int MAX_KILLS_PER_STEP = 4;
extern const int HEALER_PERCENT_MAX = 20;


RegionType NextRegion(RegionType region);

#endif
