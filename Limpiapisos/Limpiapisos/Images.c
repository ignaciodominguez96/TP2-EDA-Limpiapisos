#pragma once

#include	"Images.h"
#include	"Dimension.h"


ALLEGRO_BITMAP *
load_image_at_size(char* image_name, int size_x, int size_y);



images_t * 
create_images(void)
{
	images_t* images = malloc(sizeof(images_t));

	if (images == NULL)
	{
		return NULL;
	}

	ALLEGRO_BITMAP* image_tile_clean = load_image_at_size(ROOT_IMAGE_TILE_CLEAN, UNITY_TILE, UNITY_TILE);

	if (image_tile_clean == NULL)
	{
		free(images);

		return NULL;
	}

	ALLEGRO_BITMAP* image_tile_dirty = load_image_at_size(ROOT_IMAGE_TILE_DIRTY, UNITY_TILE, UNITY_TILE);

	if (image_tile_dirty == NULL)
	{
		free(images);
		free(image_tile_clean);

		return NULL;
	}

	ALLEGRO_BITMAP* image_robot = load_image_at_size(ROOT_IMAGE_TILE_CLEAN, UNITY_ROBOT, UNITY_ROBOT);

	if (image_robot == NULL)
	{
		free(images);
		free(image_tile_clean);
		free(image_tile_dirty);

		return NULL;
	}

	
	(images->images_tiles)->image_tile_clean = image_tile_clean;
	(images->images_tiles)->image_tile_dirty = image_tile_dirty;
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
}


ALLEGRO_BITMAP * 
load_image_at_size(char* image_name, int size_x, int size_y)
{
	ALLEGRO_BITMAP * image = NULL;
	ALLEGRO_BITMAP * current_target = NULL;
	ALLEGRO_BITMAP * resized_image = NULL;

	current_target = al_get_target_bitmap(); //salva el target original para no perderlo

	image = al_load_bitmap(image_name);
	if (image == NULL)
	{
		return NULL;
	}

	resized_image = al_create_bitmap(size_x, size_y);
	if (resized_image == NULL)
	{
		al_destroy_bitmap(image);
		return NULL;


	}

	al_set_target_bitmap(resized_image);
	al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image),
		0, 0, size_x, size_y, 0);

	al_set_target_bitmap(current_target); //vuelve al target original
	al_destroy_bitmap(image);
	return resized_image;
}