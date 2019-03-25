#pragma once

#include <stdlib.h>
#include <time.h>

#include "Simulation.h"
#include "parser.h"
#include "Callback.h"
#include "UserData.h"
#include "Random.h"
#include "allegro.h"

#define HISTOGRAM_SIZE 500
#define CONDICION_DE_STOP (((histogram[robot_count-2])-(histogram[robot_count-1])) < 0.1)


int
main(int argc, char * argv[])
{
	int end = 1;

	randomize(); //genera una nueva seed para rand

	allegroStruct_t* myAllegro = allegro_setup(myAllegro);

	

	if (myAllegro != NULL)
	{

		userData_t* myData = createUserData();

		if (myData != NULL)
		{
			if ((parseCmdLine(argc, argv, parseCallBack, myData) == 4) && isDataFull(myData)) //Igualado a la cantidad de opciones requeridas. En modo2 podrian ser 3
			{

				if (getUserData(myData, MODE) == MODE_1)
				{
					simulation_t * simulation = create_Simulation(getUserData(myData, ROBOTC), getUserData(myData, HEIGHT),
						getUserData(myData, WIDTH), MODE_1); //llenar parametros



					#error "para mi hay que dimensionar aca...multiplicar por una unidad"

					ALLEGRO_DISPLAY * display = al_create_display(myData->width, myData->height);

					if (simulation != NULL)
					{
						while (end)	//Esto deberia estar dentro de simulate_simulation si no me equivoco!!
						{
							simulate_Simulation(simulation);
							draw_floor(display, simulation->floor);
							draw_robots(display, simulation);
							al_clean_file(display, simulation->floor);
							if(is_clear_Floor(simulation->floor))
							{
									end = 0;
							}
							usleep (1000);
						}

					//	get_tickcount_Simulation(simulation); //mostrar por pantalla o como se desea el tickcount
						destroy_Simulation(simulation);
					}
				}
				else if (getUserData(myData, MODE) == MODE_2)
				{
					unsigned int robot_count;
					double histogram[HISTOGRAM_SIZE];

					for (robot_count = 1; CONDICION_DE_STOP; robot_count++) //creo que esta relacionado CONDICION_STOP con el 0.1 entre n y n+1
					{

						double tickcount_sum = 0.0;

						for (unsigned int i = 0; i < CANT_SIMULATIONS_MODE_2; i++)
						{
							simulation_t * simulation = create_Simulation(robot_count, getUserData(myData, HEIGHT), getUserData(myData, WIDTH), MODE_2);

							simulate_Simulation(simulation);
							tickcount_sum += get_tickcount_Simulation(simulation);
							destroy_Simulation(simulation);

						}

						histogram[robot_count-1] = tickcount_sum / CANT_SIMULATIONS_MODE_2; //ver como hacer la estructura para ir pusheando histogram

					}

					//show(histogram);
				}

			}

			destroyUserData(myData);
		}

		allegro_destroy(myAllegro);
	}

	return 0;
}
