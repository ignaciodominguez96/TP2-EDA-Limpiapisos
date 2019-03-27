#pragma once


#ifndef IMAGES_H
#define IMAGES_H


#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

#define ROOT_IMAGE_TILE_CLEAN "drakeyes.jpg"			//ruta del archivo de la imagen que se utiliza para la baldosa limpia
#define ROOT_IMAGE_TILE_DIRTY "drakeno.jpg"				//ruta del archivo de la imagen que se utiliza para la baldosa sucia
#define ROOT_IMAGE_ROBOT "robot.png"					//ruta del archivo de la imagen que se utiliza para el robot



/*  ESTRUCTURA: IMAGENES BALDOSAS  */

typedef struct
{
	ALLEGRO_BITMAP* image_tile_clean;				//puntero al bitmap que contiene la imagen para la baldosa limpia
	ALLEGRO_BITMAP* image_tile_dirty;				//puntero al bitmap que contiene la imagen para la baldosa sucia

}image_tiles_t;


/*  ESTRUCTURA: IMAGENES  */

typedef struct
{
	image_tiles_t * images_tiles;				// estructura que contiene los punteros a bitmaps relacionadas con las baldosas
	ALLEGRO_BITMAP* image_robot;				//puntero al bitmap que contiene la imagen para el robot

}images_t;





images_t * create_images(void);

/*
Funcion que crea la estructura imagenes, guardando en memoria la misma (y para las estructuras que contiene: imagenes baldosas)

Se devuelve un puntero a la memoria que se guardo para dicha estructura,
el cual se debe destruir cuando no se lo utilice mas

*/


void destroy_images(images_t * images);
/*


Funcion que destruye la estructura images que se le pasa por parametros, liberando la memoria guardada para
la estructura (y la memoria guardada para las estructuras que contiene la misma)

*/

#endif //IMAGES_H