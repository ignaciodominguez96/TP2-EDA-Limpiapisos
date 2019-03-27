/*************************************************************************************************

	main.c
						Limpiapisos

	Este programa simula un piso siendo limpiado por robots. El mismo dispone de dos modos:
	***********************************************************************************************
	MODO 1:
	El usuario debe ingresar por linea de comandos los siguientes datos para condicionar
	la ejecucion del programa:

	- El modo. Para iniciar el modo uno es necesario ingresar -mode 1
	- La cantidad de robots. Esta cantidad se mantendra fija a lo largo de la simulacion
	y debe ser ingresada de la siguiente manera: -robots x donde 'x' es una cantidad positiva.
	- El alto del piso. El mismo debe ser un numero positivo con un maximo de 70.
	Debe ser ingresado como -height x
	- El ancho del piso. El mismo debe ser un numero positivo con un maximo de 100.
	Debe ser ingresado como -width x

	En este modo se mostrara una simulacion en pantalla en tiempo real, concluyendo cuando
	todas las baldosas esten limpias, cuando mostrara el tiempo que ha pasado desde el inicio.
	Es necesario ingresar un 'enter' desde la consola para finalizar el programa.
	***********************************************************************************************
	MODO 2:

	Para utilizar el modo 2 es necesario ingresar TODAS las opciones al igual que el modo 1.
	En este modo, se haran 1000 simulaciones con una cantidad incremental de robots (comenzando
	en 1) y se obtendra el promedio de tiempo tardado en limpiar el piso para cada cantidad.
	El proceso concluye cuando la diferencia de tiempo entre una cantidad de robots y la siguiente
	es menor a 0.1, en cuyo caso se mostrara por pantalla un histograma con todos los valores
	obtenidos, habiendo obtenido de esta forma la "cantidad ideal" de robots para limpiar un piso
	con las dimensiones determinadas por el usuario.
	Es necesario ingresar un 'enter' desde la consola para finalizar el programa.
	************************************************************************************************/




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
#include "Dimension.h"

#define HISTOGRAM_SIZE 500
#define CONDICION_DE_STOP ((robot_count > 2) && ((histogram[robot_count-2])-(histogram[robot_count-1])) < 0.1)


int
main(int argc, char * argv[])
{

	randomize(); //genera una nueva seed para rand

	
	userData_t* myData = createUserData();

	if (myData != NULL)
	{
		if ((parseCmdLine(argc, argv, parseCallBack, myData) == 4) && isDataFull(myData)) //Igualado a la cantidad de opciones requeridas.
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
						
					al_resize_display(myAllegro->display, SCREEN_WIDTH_HISTOGRAM, SCREEN_HEIGHT_HISTOGRAM);
					print_histogram_Output(robot_count - 1, histogram, myAllegro->display, "Robots", "Tiempo");
					al_set_new_window_position(0.0, 0.0);
					al_flip_display();
					getchar();				//permite visualizar el histograma y recibir un 'enter' para terminar el programa

				}

				allegro_destroy(myAllegro);

			}


			destroyUserData(myData);
		}

		else
		{

			if(!(isDataFull(myData)))
			{
				destroyUserData(myData);
				printf("Input Error: One or more necessary options haven't been entered\n");
				getchar();
			}
			else
			{
				destroyUserData(myData);
				printf("Input Error: The number of options entered must be equal to four\n");
				getchar();
			}
		}

	}


	return 0;
}
