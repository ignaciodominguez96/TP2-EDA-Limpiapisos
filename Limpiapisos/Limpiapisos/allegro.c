#include <stdio.h>
#include "Simulation.h"
#include "Floor.h"
#include "Robot.h"
#include "Tile.h"
#include "allegro.h"

allegroStruct_t* allegro_setup(allegroStruct_t* usrAllegro)
{
	usrAllegro->event_queue = NULL;
	usrAllegro->display = NULL;
	usrAllegro->timer = NULL;

	if (!al_init())//inicio allegro
	{
		printf("Could not initialize Allegro!\n");
		return NULL;
	}


	usrAllegro->display = al_create_display(960, 800);
	if (!(usrAllegro->display))//inicio display
	{
		printf("Could not initialize Display!.\n");
		return NULL;
	}

	usrAllegro->event_queue = al_create_event_queue();
	if (!(usrAllegro->event_queue))//inicio cola de eventos
	{
		printf("Could not initialize event queue!.\n");
		al_destroy_display(usrAllegro->display);
		return NULL;
	}

	usrAllegro->timer = al_create_timer(1 / FPS); //FIJARSE POR QUE NO LO RECONOCE (y si conviene 60, esto parece copiado de otro prog)
	if (!(usrAllegro->timer))//inicio timer IMPORTANTE FUNCIONA  A 60 FPS
	{
		printf("Failed to create timer!\n");
		al_destroy_event_queue(usrAllegro->event_queue);
		al_destroy_display(usrAllegro->display);
		return NULL;
	}

	al_set_window_title(usrAllegro->display, "Limpiapisos");

	al_register_event_source(usrAllegro->event_queue, al_get_display_event_source(usrAllegro->display));
	al_register_event_source(usrAllegro->event_queue, al_get_timer_event_source(usrAllegro->timer));

	al_start_timer(usrAllegro->timer);

	return usrAllegro;

}

void allegro_destroy(allegroStruct_t* usrAllegro)
{
	al_destroy_display(usrAllegro->display);
	al_destroy_event_queue(usrAllegro->event_queue);
	al_destroy_timer(usrAllegro->timer);
	usrAllegro = NULL;
}

void draw_floor(ALLEGRO_DISPLAY *display, floor_t * floor)
{
    ALLEGRO_BITMAP *Lines;

    Lines = al_create_bitmap(800,5);


    al_clear_to_color(al_map_rgb(211, 211, 211)); //Set Background to gray


    al_set_target_bitmap(Lines);
    al_clear_to_color(al_map_rgb(255,255,255));



    al_set_target_bitmap(al_get_backbuffer(display)); //Importante setea la pantalla como lugar a dibujar



    //First 6 lanes
    for (int i = 0; i < 800; i += 800/(floor->height))
    {
        for (int j = 0; j < 960; j += 960/(floor->width))
        {
            al_draw_bitmap(Lines, j, i, 0);
        }
    }

    al_destroy_bitmap(Lines);
}


void draw_robots(ALLEGRO_DISPLAY *display, simulation_t * simulation)
{
  ALLEGRO_BITMAP * Robot;

  Robot = al_create_bitmap(30, 30);


    al_set_target_bitmap(Robot);
    al_clear_to_color(al_map_rgb(0, 0, 255));
    al_set_target_bitmap(al_get_backbuffer(display));

    for(unsigned int i=0 ; i < simulation->cant_robots; i++)
    {
      al_draw_bitmap(Robot, (((simulation->robots)+i)->pos).x, (((simulation->robots) + i)->pos).y, 0);
    }

}


void al_clean_file(ALLEGRO_DISPLAY * display, floor_t * floor)
{
  ALLEGRO_BITMAP * cleantile;

  cleantile = al_create_bitmap((960/floor->width), (800/floor->height));

  unsigned int height = floor->height;
  unsigned int width = floor->width;

	al_set_target_bitmap(cleantile);
	al_clear_to_color(al_map_rgb(255, 255, 255));
	al_set_target_bitmap(al_get_backbuffer(display));

  for(unsigned int i=0; i < (height*width); i++)
  {
    if (floor -> tiles +1)
    {
      al_draw_bitmap(cleantile, 960/floor->width * (floor->width % i), 800/floor->height * (floor->width/i), 0);
    }
  }


}
