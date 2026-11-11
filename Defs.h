#ifndef DEFS_H
#define DEFS_H



enum Region
{
    region_A,
    region_B,
    region_C,
    region_D
};

enum EnemyType
{
    Fighter,
    Healer,
    Freezer
};

enum EnemyState
{
    Inactive,
    Active,
    Frozen,
    Killed
};

extern const int Start_Distance = 60;
extern const int Min_Distance = 2;
extern const int Max_Kills_Per_Step = 4;
extern const int Healer_Percent_Max = 20;


Region NextRegion(Region region);

#endif
