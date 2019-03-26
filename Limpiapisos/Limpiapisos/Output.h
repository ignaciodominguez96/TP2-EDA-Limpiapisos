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

//#include "Simulation.h"
#include "Images.h"
#include "Floor.h"
#include "Robot.h"

#define FPS 5.0

typedef struct
{

	ALLEGRO_DISPLAY *display;
	/*ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_TIMER *timer;*/

}allegroStruct_t;



allegroStruct_t* allegro_setup(allegroStruct_t* usrAllegro, unsigned int height, unsigned int width);
void allegro_destroy(allegroStruct_t* usrAllegro);
void display_TickCount(unsigned int height, unsigned int width, unsigned int tickCount);
void update_display_Output(floor_t * floor, robot_t * robots, unsigned int cant_robots, images_t* images);
bool print_histogram_Output(ALLEGRO_DISPLAY* display, unsigned int cant_simulations, unsigned long* tick_per_simulation);



#endif //OUTPUT_H