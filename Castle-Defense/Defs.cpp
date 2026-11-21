#include "Defs.h"

RegionType NextRegion(RegionType region)
{
    switch (region)
    {
    case REGION_A: 
        return REGION_B;
    case REGION_B: 
        return REGION_C;
    case REGION_C: 
        return REGION_D;
    case REGION_D: 
        return REGION_A;
    default:       
        return REGION_A;
    }
}