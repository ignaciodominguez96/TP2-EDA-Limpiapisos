#pragma once

#include <stdlib.h>
#include <iostream>
#include <time.h>

#include "Simulation.h"
#include "parser.h"
#include "Callback.h"
#include "UserData.h"


int
main(int argc, char * argv[])
{
	time_t t;
	srand((unsigned)time(&t));

	userData_t* myData;

	if (parseCmdline(argc, argv, parseCallBack, myData) == 4 && myData->fullfiled == 4) //Igualado a la cantidad de opciones requeridas. En modo2 podrian ser 3
	{
		intAllegro();

		if (myData->mode == MODE_1)
		{
			simulation_t * simulation = create_Simulation(); //llenar parametros

			if (simulation != NULL)
			{
				simulate_Simulation(simulation);
				cout << get_tickcount_Simulation(simulation); //mostrar por pantalla o como se desea el tickcount
			}
		}
		else if (myData->mode == MODE_2)
		{
			unsigned int robot_count;

			for (robot_count = 1; CONDICION_DE_STOP; robot_count++) //creo que esta relacionado CONDICION_STOP con el 0.1 entre n y n+1
			{

				double tickcount_sum = 0.0;

				for (unsigned int i = 0; i < CANT_SIMULATIONS_MODE_2; i++)
				{
					simulation_t * simulation = create_Simulation(); //llenar parametros (distinto porque tiene robot_count entre otras cosas)
					simulate_Simulation(simulation);
					tickcount_sum += get_tickcount_Simulation(simulation);
					destroy_Simulation(simulation);
					
				}

				histogram(robot_count) = tickcount_sum / CANT_SIMULATIONS_MODE_2; //ver como hacer la estructura para ir pusheando histogram
				
			}

			show(histogram);
		}

	}


}
