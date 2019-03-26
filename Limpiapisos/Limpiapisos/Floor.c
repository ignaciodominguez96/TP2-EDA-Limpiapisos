#pragma once

#include <stdlib.h>
#include "Floor.h"


floor_t *
create_Floor(unsigned int height, unsigned int width)
{
	floor_t * floor = NULL;

	floor = (floor_t *) malloc(sizeof(floor_t));

	if (floor != NULL)
	{
		floor->height = height;
		floor->width = width;
		floor->tiles = NULL;
		floor->tiles = (tile_t *)malloc(sizeof(tile_t)*height*width);

		if (floor->tiles != NULL)
		{
			for (unsigned int i = 0; i < (height*width); i++)
			{
				mess_Tile( floor->tiles + i);
			}

		}
		else
		{
			free(floor);
			floor = NULL;
		}

	}

	return floor;

}

unsigned int
get_height_Floor(floor_t * floor)
{
	return floor->height;
}

unsigned int
get_width_Floor(floor_t * floor)
{
	return floor->width;
}

tile_t * get_tile(floor_t* floor, int posx, int posy)
{
	return ((floor->tiles) + posy*(get_width_Floor(floor)) + posx);
}

bool
is_clear_Floor(floor_t * floor)
{
	bool is_clear = true;
	unsigned int height = get_height_Floor(floor);
	unsigned int width = get_width_Floor(floor);

	for (unsigned int i = 0; i < (height*width); i++)
	{
		bool aux = is_dirty_Tile(floor->tiles + i);

		if (aux == true)
		{
			is_clear = false;
			i = height * width;
		}

	}

	return is_clear;
}

void
destroy_Floor(floor_t * floor)
{
	free(floor->tiles);
	floor->tiles = NULL;
	free(floor);
	floor = NULL;

}
