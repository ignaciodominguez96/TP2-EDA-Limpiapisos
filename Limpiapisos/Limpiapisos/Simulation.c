#include <stdlib.h>
#include <math.h>
#include "Simulation.h"

simulation_t * create_Simulation(unsigned int cant_robots, unsigned int height, unsigned int width, unsigned int mode, allegroStruct_t* usrAllegro)
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
				newSim->usrAllegro = usrAllegro;
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
	while (!(is_clear_Floor(simulation->floor))) //	Cada vez que hay un "tick" tiene que pasar lo siguiente:
	{
		for (unsigned int i = 0; i < simulation->cant_robots; i++)
		{
			robot_t* tempRobot = simulation->robots + i;	// Se agarra un robot de los que existan
			if(simulation->tickcount == 0)
				wash_Tile(get_tile(simulation->floor, (int)floor(get_Robot_posx(tempRobot)), (int)floor(get_Robot_posy(tempRobot))));
			act_Robot(tempRobot, get_width_Floor(simulation->floor), get_height_Floor(simulation->floor));	//	El robot se mueve o cambia de direccion
			wash_Tile(get_tile(simulation->floor, (int)floor(get_Robot_posx(tempRobot)), (int)floor(get_Robot_posy(tempRobot))));	// Se limpia la baldosa donde este el robot, se haya movido o no
		}
		/*draw_floor(simulation->usrAllegro->display, simulation->floor); //corregir la doble entrada
		draw_robots(simulation->usrAllegro->display, simulation);
		al_clean_file(simulation->usrAllegro->display, simulation->floor);*/

		(simulation->tickcount)++;

		//al_rest(0.1); //usar def
	}

	return 0;
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
