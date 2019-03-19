

#include "Farm.h"

// Initialize the
void Farm_init(farm_t *farm)
{
    int i;
    // Farm starts with  full money
    farm->Money = 3;
    farm->MonthsPassed = 0;
    farm->DaysPassed = 0;

    // Remains Zero Until Planting
    farm->CropHealth = 0;
    farm->Difficulty = 'E';

    for(i=0; i<5; i++)
    {
        farm->Plots[i].Age = 0;
        farm->Plots[i].Health = 0;
        farm->Plots[i].Hydration = 0;
    }
}

