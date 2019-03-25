
#ifndef ALLEGRO_H
#define ALLEGRO_H

#include	<stdio.h>
#include	"Floor.h"
#include	"Simulation.h"

void draw_floor(ALLEGRO_DISPLAY *display, floor_t * floor);
void draw_robots(ALLEGRO_DISPLAY *display, simulation_t * simulation);
void al_clean_file(ALLEGRO_DISPLAY * display, floor_t * floor);

#endif
