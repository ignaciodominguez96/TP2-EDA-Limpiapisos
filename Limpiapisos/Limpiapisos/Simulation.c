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


				if (mode == MODE_1)
				{
					images_t * images = create_images();

					if (images != NULL)
					{
						newSim->images = images;
					}
					else
					{
						free(tempFloor);
						tempFloor = NULL;
						free(tempRobot);
						tempRobot = NULL;
						free(newSim);
						newSim = NULL;
					}
				}
				else
				{
					newSim->images = NULL;
				}
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

		if (simulation->mode == MODE_1)
		{
			update_display_Output(simulation->floor, simulation->robots, simulation->cant_robots, simulation->images);
			al_flip_display();
			al_rest(1 / FPS);

		}
		
		(simulation->tickcount)++;

		
	}

	return 0;
}


unsigned int get_tickcount_Simulation(simulation_t * simulation)
{
	return simulation->tickcount;
}


void	destroy_Simulation(simulation_t * simulation)
{
	destroy_Floor(simulation->floor);

	destroy_Robots(simulation->robots);

	if (simulation->mode == 1)
	{
		destroy_images(simulation->images);
	}

	free(simulation);
	simulation = NULL;
	


}
