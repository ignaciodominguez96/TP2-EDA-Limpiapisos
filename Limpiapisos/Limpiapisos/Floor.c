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
		floor->tiles = (tile_t *)malloc(sizeof(tile_t)*height*width);
		
		if (floor->tiles != NULL)
		{
			for (int i = 0; i < height*width; i++)
			{
				mess_Tile((floor->tiles)[i]);
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