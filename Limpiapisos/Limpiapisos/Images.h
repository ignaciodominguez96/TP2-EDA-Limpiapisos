#pragma once


#ifndef IMAGES_H
#define IMAGES_H


#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

#define ROOT_IMAGE_TILE_CLEAN "../Imagenes/limpio2.png"
#define ROOT_IMAGE_TILE_DIRTY "../Imagenes/dirtytile.png"
#define ROOT_IMAGE_ROBOT "../Imagenes/robot.png"



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