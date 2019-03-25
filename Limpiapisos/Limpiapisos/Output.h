#pragma once

#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdbool.h>

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_color.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_image.h>

#include "Simulation.h"
#include "Images.h"

#define TIME_BTW_UPDATES 0.1 //seg



typedef struct
{

	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_DISPLAY *display;
	ALLEGRO_TIMER *timer;

}allegroStruct_t;


allegroStruct_t* allegro_setup(allegroStruct_t* usrAllegro);
void allegro_destroy(allegroStruct_t* usrAllegro);
void update_tiles_Output(floor_t * floor, image_tiles_t * images_tiles);
void update_robots_Output(robot_t* robots, unsigned int cant_robots, ALLEGRO_BITMAP* image_robot);
void update_display_Output(simulation_t* simulation, images_t* images);
bool print_histogram_Output(ALLEGRO_DISPLAY* display, unsigned int cant_simulations, unsigned long* tick_per_simulation);



#endif //OUTPUT_H