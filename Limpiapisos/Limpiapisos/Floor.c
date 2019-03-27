#pragma once

#include <stdlib.h>
#include "Floor.h"


//Funcion que crea la estructura piso, guardando en memoria la misma
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
		bool * tiles = (bool *)malloc(sizeof(bool)*(height*width*2));

		if (tiles != NULL)
		{
			for (unsigned int i = 0; i < (height*width); i++)
			{
				mess_Tile(tiles + i);
			}

			floor->tiles = tiles;
		}
		else
		{
			free(floor);
			floor = NULL;
		}

	}

	return floor;

}

//Se obtiene el alto del piso que se le pasa por parametros
unsigned int
get_height_Floor(floor_t * floor)
{
	return floor->height;
}

//Se obtiene el ancho del piso que se le pasa por parametros
unsigned int
get_width_Floor(floor_t * floor)
{
	return floor->width;
}

//Se obtiene la baldosa que se encuentra en la posicion x y posicion y (posx y posy) del piso que se le pasa por parametros
bool * get_tile(floor_t* floor, int posx, int posy)
{
	bool * tile = NULL;
	
	tile = ((floor->tiles) + posy * (get_width_Floor(floor)) + posx);
	

	return tile;

	
}

//Devuelve un bool que indica si el piso que se le pasa por parametros esta limpio o no
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

//Funcion que destruye la estructura piso que se le pasa por parametros, liberando la memoria guardada para la estructura
void
destroy_Floor(floor_t * floor)
{
	if(floor->tiles != NULL)
		free(floor->tiles);
	floor->tiles = NULL;
	if (floor != NULL)
		free(floor);
	floor = NULL;

}
