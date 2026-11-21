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

// Names provided in GUI.h / GUI.cpp must use.
#define NoOfRegions 4
#define MaxDistance 60
#define MinDistance 2
#define MaxVerticalEnemies 15
#define MaxEnemyCount 300

enum REGION
{
    A_REG,
    B_REG,
    C_REG,
    D_REG
};

struct Point
{
    int x;
    int y;
    Point(int a = 0, int b = 0)
    {
        x = a;
        y = b;
    }
};


RegionType NextRegion(RegionType region);

#endif
