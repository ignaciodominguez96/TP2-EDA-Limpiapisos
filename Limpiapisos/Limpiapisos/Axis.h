#pragma once

#ifndef AXIS_H

#define AXIS_H

#include <allegro5\allegro_color.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_image.h>


typedef struct {
	unsigned int space_x;    
	unsigned int space_y;
	float max_x;                    
	float max_y;
	float el_scale_x;           
	float el_scale_y;
	unsigned int long_axis_x;        
	unsigned int long_axis_y;
	unsigned int thickness;            
	char * name_axis_x;             
	char * name_axis_y;
	unsigned int cant_x;          
	unsigned int cant_y;
	unsigned int origin_x;           
	unsigned int origin_y;

}axis_t;


axis_t * create_axis(double width, double height, double max_x, double max_y, char * name_var_x, char * name_var_y);
void print_axis(axis_t * axis);

#endif // !AXIS_H

