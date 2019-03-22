#include <stdlib.h>
#include "Simulation.h"

simulation_t * create_Simulation(unsigned int cant_robots, unsigned int height, unsigned int width, unsigned int mode)
{
	simulation_t* newSim = NULL;
	newSim = (simulation_t*)malloc(sizeof(simulation_t));
	if (newSim != NULL)
	{
		robot_t* tempRobot = create_Robots(width, height, cant_robots);
		if (tempRobot != NULL)
		{
			floor_t* tempFloor = create_Floor(height, width);
			if (tempFloor != NULL)
			{
				newSim->robots = tempRobot;
				newSim->cant_robots = cant_robots;
				newSim->mode = mode;
				newSim->floor = tempFloor;
				newSim->tickcount = 0; //por las dudas se inicializa en 0 para evitar basura del heap
			}
			else
			{
				free(tempRobot);
				tempRobot = NULL;
				free(newSim);
				newSim = NULL;
			}
		}
		else
		{
			free(newSim);
			newSim = NULL;
		}
	}
	
	return newSim;
}
bool	simulate_Simulation(simulation_t * simulation)
{

}
unsigned int get_tickcount_Simulation(simulation_t * simulation)
{
	return simulation->tickcount;
}
void	destroy_Simulation(simulation_t * simulation)
{
	free(simulation->floor);
	simulation->floor = NULL;
	free(simulation->robots);
	simulation->robots = NULL;
	free(simulation);
	simulation = NULL;
}