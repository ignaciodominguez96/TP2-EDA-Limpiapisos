/*
#ifndef ALLEGRO_H
#define ALLEGRO_H

#include	<stdio.h>
#include	"Floor.h"
#include	"Simulation.h"
#include "allegro5/allegro5.h"

#define FPS (60)

typedef struct
{

	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_DISPLAY *display;
	ALLEGRO_TIMER *timer;

}allegroStruct_t;

allegroStruct_t* allegro_setup(allegroStruct_t* usrAllegro);
void allegro_destroy(allegroStruct_t* usrAllegro);
void draw_floor(ALLEGRO_DISPLAY *display, floor_t * floor);
void draw_robots(ALLEGRO_DISPLAY *display, simulation_t * simulation);
void al_clean_file(ALLEGRO_DISPLAY * display, floor_t * floor);

#endif
*/