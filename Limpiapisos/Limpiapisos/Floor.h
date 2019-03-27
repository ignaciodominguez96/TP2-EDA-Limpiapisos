#pragma once

#ifndef FLOOR_H
#define FLOOR_H

#include	<stdbool.h>
#include	"Tile.h"

/* ESTRUCTURA: Piso  */
typedef struct
{	
	bool * tiles;			//cantidad de baldosas que tiene el piso
	unsigned int height;	//cantidad de baldosas a lo alto 
	unsigned int width;		//cantidad de baldosas a lo ancho

} floor_t;


floor_t * create_Floor(unsigned int height, unsigned int width);
/*
Funcion que crea la estructura piso, guardando en memoria la misma
Se le indica el tamaño del mismo (heigh y width) y a partir de ahi crea las baldosas

Se devuelve un puntero a la memoria que se guardo para dicha estructura, 
el cual se debe destruir cuando no se lo utilice mas

*/

unsigned int get_height_Floor(floor_t * floor);
/*

Se obtiene el alto del piso que se le pasa por parametros

*/


unsigned int get_width_Floor(floor_t * floor);
/*

Se obtiene el ancho del piso que se le pasa por parametros

*/



bool * get_tile(floor_t * floor, int posx, int posy);
/*

Se obtiene la baldosa que se encuentra en la posicion x y posicion y (posx y posy)
del piso que se le pasa por parametros

*/


bool is_clear_Floor(floor_t * floor);

/*

Devuelve un bool que te indica si el piso que se le pasa por parametros esta limpio o no

*/

void	destroy_Floor(floor_t * floor);

/*
Funcion que destruye la estructura piso que se le pasa por parametros, liberando la memoria guardada para
la estructura

*/

#endif //FLOOR_H
