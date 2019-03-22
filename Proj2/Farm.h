#ifndef FARM_H_
#define FARM_H_


// Plot struct
typedef struct
{
//  plotState State;
    int Age;
    int Health;
    int Hydration;

} plot_t;

//Farm Struct
typedef struct
{
    plot_t Plots[6];

    int Money;

    int MonthsPassed;
    int DaysPassed;

    int CropHealth;//Average crop health

    char Difficulty;//The difficulty level

} farm_t;

// Initialize the farm struct
void Farm_init(farm_t *farm);

#endif
