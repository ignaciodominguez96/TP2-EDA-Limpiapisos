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


void update_tiles_Output(floor_t * floor, image_tiles_t * images_tiles);
void update_robots_Output(robot_t* robots, unsigned int cant_robots, ALLEGRO_BITMAP* image_robot);
void update_display_Output(simulation_t* simulation, images_t* images);




#endif //OUTPUT_H