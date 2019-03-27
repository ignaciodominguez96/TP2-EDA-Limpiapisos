#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "Simulation.h"
#include "parser.h"
#include "Callback.h"
#include "UserData.h"
#include "Random.h"
#include "Output.h"

#define HISTOGRAM_SIZE 500
#define CONDICION_DE_STOP ((robot_count > 2) && ((histogram[robot_count-2])-(histogram[robot_count-1])) < 0.1)


int
main(int argc, char * argv[])
{

	randomize(); //genera una nueva seed para rand

	
	userData_t* myData = createUserData();

	if (myData != NULL)
	{
		if ((parseCmdLine(argc, argv, parseCallBack, myData) == 4) && isDataFull(myData)) //Igualado a la cantidad de opciones requeridas. En modo2 podrian ser 3
		{
			allegroStruct_t* myAllegro = NULL;
			myAllegro = allegro_setup(myAllegro, myData->height, myData->width);

			if (myAllegro != NULL)
			{
				if (getUserData(myData, MODE) == MODE_1)
				{
					unsigned int tickCount = 0;
					simulation_t * simulation = create_Simulation(getUserData(myData, ROBOTC), getUserData(myData, HEIGHT),
						getUserData(myData, WIDTH), MODE_1, myAllegro); //llenar parametros



					if (simulation != NULL)
					{
						simulate_Simulation(simulation);
						tickCount = get_tickcount_Simulation(simulation); //mostrar por pantalla o como se desea el tickcount
						printf("%d\n", tickCount);
						display_TickCount(get_height_Floor(simulation->floor),get_width_Floor(simulation->floor), tickCount);	//tira error el set target backbuffer
						getchar();
						destroy_Simulation(simulation);
					}

				}
				else if (getUserData(myData, MODE) == MODE_2)
				{
					unsigned int robot_count = 0;
					double histogram[HISTOGRAM_SIZE];
					bool mode_2_finish = false;
					simulation_t * simulation = NULL;


					for (robot_count = 1; mode_2_finish == false; robot_count++) //creo que esta relacionado CONDICION_STOP con el 0.1 entre n y n+1
					{
						
						double tickcount_sum = 0.0;

						for (unsigned int i = 0; i < CANT_SIMULATIONS_MODE_2; i++)
						{
							 simulation = create_Simulation(robot_count, getUserData(myData, HEIGHT), getUserData(myData, WIDTH), MODE_2,
								myAllegro);


							if (simulation != NULL)
							{
								simulate_Simulation(simulation);
								tickcount_sum += (double) get_tickcount_Simulation(simulation);
								destroy_Simulation(simulation);
							}
							else
							{
								printf("Una sim dio null");
								getchar();
							}

						}

						histogram[robot_count - 1] = (tickcount_sum / CANT_SIMULATIONS_MODE_2); //ver como hacer la estructura para ir pusheando histogram

						if (robot_count < 497)
						{
							if (robot_count >= 2)
							{
								if (histogram[robot_count - 2] - histogram[robot_count - 1] >= 0.1)
								{
									mode_2_finish = false;
								}
								else
								{
									mode_2_finish = true;
								}
							}
						}
						else
						{
							mode_2_finish = true;
						}

					}
					bool can_i_print = false;
						
					al_resize_display(myAllegro->display, 1600.0, 1200.0);
					print_histogram_Output(robot_count - 1, histogram, myAllegro->display, "Robots", "Tiempo");
					al_set_new_window_position(0.0, 0.0);
					al_flip_display();
					getchar();

				}

				allegro_destroy(myAllegro);

			}


			destroyUserData(myData);
		}

	}


	return 0;
}
