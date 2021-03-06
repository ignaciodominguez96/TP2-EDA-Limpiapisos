#pragma once

#include	"Images.h"
#include	"Dimension.h"


ALLEGRO_BITMAP *
resize_image(char* image_name, int resize_x, int resize_y);



images_t * 
create_images(void)
{
	images_t* images = (images_t *)malloc(sizeof(images_t));
	image_tiles_t * images_tiles = (image_tiles_t*)malloc(sizeof(image_tiles_t));

	if (images == NULL || images_tiles == NULL)
	{
		return NULL;
	}

	ALLEGRO_BITMAP* image_tile_clean = resize_image(ROOT_IMAGE_TILE_CLEAN, UNITY_TILE, UNITY_TILE);

	if (image_tile_clean == NULL)
	{
		free(images);
		free(images_tiles);

		return NULL;
	}

	ALLEGRO_BITMAP* image_tile_dirty = resize_image(ROOT_IMAGE_TILE_DIRTY, UNITY_TILE, UNITY_TILE);

	if (image_tile_dirty == NULL)
	{
		free(images);
		free(images_tiles);
		free(image_tile_clean);

		return NULL;
	}

	ALLEGRO_BITMAP* image_robot = resize_image(ROOT_IMAGE_ROBOT, UNITY_ROBOT, UNITY_ROBOT);

	if (image_robot == NULL)
	{
		free(images);
		free(images_tiles);
		free(image_tile_clean);
		free(image_tile_dirty);

		return NULL;
	}

	
	images_tiles->image_tile_clean = image_tile_clean;
	images_tiles->image_tile_dirty = image_tile_dirty;
	images->images_tiles = images_tiles;
	images->image_robot = image_robot;


	return images;
	
}


void 
destroy_images(images_t * images)
{
	al_destroy_bitmap((images->images_tiles)->image_tile_clean);
	al_destroy_bitmap((images->images_tiles)->image_tile_dirty);
	al_destroy_bitmap(images->image_robot);
	free(images);
	images = NULL;
}


ALLEGRO_BITMAP * 
resize_image(char* image_name, int resize_x, int resize_y)
{
	ALLEGRO_BITMAP * image_to_resize = NULL;
	ALLEGRO_BITMAP * actual_bitmap = NULL;
	ALLEGRO_BITMAP * resized_image = NULL;

	actual_bitmap = al_get_target_bitmap(); //salva el target original para no perderlo

	image_to_resize = al_load_bitmap(image_name);

	if (image_to_resize == NULL)
	{
		return NULL;
	}

	resized_image = al_create_bitmap(resize_x, resize_y);
	
	if (resized_image == NULL)
	{
		al_destroy_bitmap(image_to_resize);
		return NULL;


	}

	al_set_target_bitmap(resized_image);
	al_draw_scaled_bitmap(image_to_resize, 0, 0,
						 al_get_bitmap_width(image_to_resize), al_get_bitmap_height(image_to_resize), 0, 0,
						 resize_x, resize_y, 0);

	al_set_target_bitmap(actual_bitmap); //vuelve al target original
	al_destroy_bitmap(image_to_resize);
	return resized_image;
}