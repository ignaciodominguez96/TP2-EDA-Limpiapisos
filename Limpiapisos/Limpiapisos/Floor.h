#pragma once

#ifndef FLOOR_H
#define FLOOR_H

#include	<stdbool.h>
#include	"Tile.h"

typedef struct
{	
	//#error "cambie tiles por bool"
	bool * tiles;
	unsigned int height; 
	unsigned int width;

}floor_t;

floor_t * create_Floor(unsigned int height, unsigned int width);
unsigned int get_height_Floor(floor_t * floor);
unsigned int get_width_Floor(floor_t * floor);
bool * get_tile(floor_t * floor, int posx, int posy);
bool is_clear_Floor(floor_t * floor);
void	destroy_Floor(floor_t * floor);

#endif //FLOOR_H
