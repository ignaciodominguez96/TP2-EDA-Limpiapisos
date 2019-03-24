#pragma once

#include <stdlib.h>
#include <time.h>

#include "Simulation.h"
#include "parser.h"
#include "Callback.h"
#include "UserData.h"
#include "Random.h"

#define HISTOGRAM_SIZE 500
#define CONDICION_DE_STOP (((histogram[robot_count-2])-(histogram[robot_count-1])) < 0.1)


int
main(int argc, char * argv[])
{
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
  ALLEGRO_DISPLAY *display = NULL;
  ALLEGRO_TIMER *timer;

  if(!al_init())//inicio allegro
  {
      printf("Could not initialize Allegro!\n");
      return -1;
  }


  display = al_create_display(960, 800);
  if(!display)//inicio display
  {
      printf("Could not initialize Display!.\n");
      return -1;
  }

  event_queue = al_create_event_queue();
  if(!event_queue)//inicio cola de eventos
  {
      printf("Could not initialize event queue!.\n");
      al_destroy_display(display);
      return -1;
  }

  timer = al_create_timer(1/FPS);
  if(!timer)//inicio timer IMPORTANTE FUNCIONA  A 60 FPS
  {
      printf("Failed to create timer!\n");
      al_destroy_event_queue(event_queue);
      al_destroy_display(display);
      return -1;
  }

  al_set_window_title(display, "Limpiapisos");

  al_register_event_source(event_queue, al_get_display_event_source(display));
  al_register_event_source(event_queue, al_get_timer_event_source(timer));

  al_start_timer(timer);

	randomize(); //genera una nueva seed para rand

	userData_t* myData = createUserData();

	if (myData != NULL)
	{
		if (parseCmdline(argc, argv, parseCallBack, myData) == 4 && isDataFull(myData)) //Igualado a la cantidad de opciones requeridas. En modo2 podrian ser 3
		{

			if (getUserData(myData, MODE) == MODE_1)
			{
				simulation_t * simulation = create_Simulation(getUserData(myData, ROBOTC), getUserData(myData, HEIGHT),
					getUserData(myData, WIDTH), MODE_1); //llenar parametros

				if (simulation != NULL)
				{
					simulate_Simulation(simulation);
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

	}

	al_destroy_display(display);
  al_destroy_event_queue(event_queue);
  al_destroy_timer(timer);
	destroyUserData(myData);
	return 0;
}
