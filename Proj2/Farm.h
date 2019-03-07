#ifndef FARM_H_
#define FARM_H_


// Plot struct
typedef struct {
//	plotState State;
	int Age;
	int Health;
	int Hydration;

	// add more members if you need
} plot_t;


// Farm struct represents the collection of all of the plots and the properties of the farm
typedef struct {
//	plot_t Plots[NUMPLOTS];
	int Money;
	int MonthsPassed;
	int DaysPassed;
	int CropHealth;

	// add more members if you need

} farm_t;

// Initialize the farm struct
void Farm_init(farm_t *farm);

// declare farm manipulation and plot manipulation functions here and then, implement them in farm.c




#endif
