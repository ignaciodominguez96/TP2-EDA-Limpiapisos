#pragma once
#ifndef SIMULATION_H
#define SIMULATION_H

#include <stdbool.h>
#include "Robot.h"
#include "Floor.h"
#include "Output.h"

#define	MODE_1	1
#define	MODE_2	2

#define CANT_SIMULATIONS_MODE_2 1000

typedef struct
{
	robot_t	* robots; //en principio lo dejamos comentado hasta ver si hace falta
	unsigned int cant_robots;
	floor_t * floor;
	unsigned int mode;
	unsigned int tickcount;
	allegroStruct_t* usrAllegro;

}simulation_t;

simulation_t * create_Simulation(unsigned int cant_robots, unsigned int height, unsigned int width, unsigned int mode, allegroStruct_t* usrAllegro);
bool	simulate_Simulation(simulation_t * simulation);
unsigned int get_tickcount_Simulation(simulation_t * simulation);
void	destroy_Simulation(simulation_t * simulation);

#endif //SIMULATION_H