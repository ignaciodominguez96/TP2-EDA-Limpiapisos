#pragma once


#ifndef IMAGES_H
#define IMAGES_H


#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

//#define ROOT_IMAGE_TILE_CLEAN "limpio.png"
//#define ROOT_IMAGE_TILE_DIRTY "sucio.png"
#define ROOT_IMAGE_TILE_CLEAN "drakeyes.jpg"
#define ROOT_IMAGE_TILE_DIRTY "drakeno.jpg"
#define ROOT_IMAGE_ROBOT "robot.png"



typedef struct
{
	ALLEGRO_BITMAP* image_tile_clean;
	ALLEGRO_BITMAP* image_tile_dirty;
}image_tiles_t;


typedef struct
{
	image_tiles_t * images_tiles;
	ALLEGRO_BITMAP* image_robot;

}images_t;





images_t * create_images(void);
void destroy_images(images_t * images);



#endif //IMAGES_H