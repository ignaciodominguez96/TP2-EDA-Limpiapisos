

#include "Axis.h"
#include "Dimension.h"
#include "Colors.h"
#include "Type_fonts.h"



#include <stdlib.h>



#define ABSOLUTE(x) ( ( (x >= 0)? x : (x * (-1)) ) )



axis_t * create_axis (double width, double height, double max_x, double max_y, char * name_var_x, char * name_var_y)
{
	axis_t * axis = (axis_t *) malloc (sizeof(axis_t));
	
	if (axis != NULL)
	{
		axis->max_x = max_x;
		axis->max_y = max_y;
		axis->space_x = width * OFFSET_AXIS;
		axis->space_y = height * OFFSET_AXIS;
		axis->long_axis_x = width - (2 * axis->space_x);
		axis->long_axis_y = height - (2 * axis->space_y);
		axis->name_axis_x = name_var_x;
		axis->name_axis_y = name_var_y;
		axis->el_scale_x = (axis->long_axis_x) / (ABSOLUTE(axis->max_x));
		axis->el_scale_y = (axis->long_axis_y) / (ABSOLUTE(axis->max_y));
		axis->thickness = THICKNESS_AXIS;
		axis->cant_x = (axis->long_axis_x / axis->el_scale_x);
		axis->cant_y = (axis->long_axis_y / axis->el_scale_y);
		axis->origin_x = axis->space_x;
		axis->origin_y = axis->space_y + axis->long_axis_y;
	}


	return axis;
}

void print_axis (axis_t * axis)
{
	ALLEGRO_FONT * font = al_load_ttf_font(AXIS_FILE_FONT, FONT_SIZE_AXIS, 0);
	ALLEGRO_COLOR color = al_color_name(AXIS_COLOR_FONT);

	unsigned int x = 0, y = 0;
	al_draw_line(axis->origin_x, axis->space_y, axis->space_x, axis->origin_y, color, axis->thickness);
	al_draw_line(axis->origin_x, axis->origin_y, axis->long_axis_x + axis->origin_x, axis->origin_y, color, axis->thickness);
	


	for (unsigned int i = 1; i <= axis->cant_x; i++)
	{
		al_draw_line((axis->origin_x + (i * axis->el_scale_x)), axis->origin_y + OFFSET_AXIS_INDICATOR,
			(axis->origin_x + (i * axis->el_scale_x)), axis->origin_y - OFFSET_AXIS_INDICATOR, color, axis->thickness);
		al_draw_textf(font, color, (axis->origin_x + (i * axis->el_scale_x)), axis->origin_y + ((OFFSET_AXIS_INDICATOR) * 2), 0, "%d", i);
	}

	for (unsigned int i = 1; i <= (axis->cant_y / SEPARATION_AXIS_Y); i++)
	{
				al_draw_line(axis->origin_x , (axis->origin_y + (i * axis->el_scale_y*SEPARATION_AXIS_Y)), 
			axis->origin_x - OFFSET_AXIS_INDICATOR, (axis->origin_y + (i * axis->origin_y*OFFSET_AXIS_INDICATOR)), color, axis->thickness);

	}
	
	
	al_draw_textf(font, color, (axis->space_x + axis->long_axis_x), axis->origin_y + (axis->space_y / 4), 0, "%s", axis->name_axis_x);
		
	al_draw_textf(font, color, axis->space_x / 2, axis->space_y, 0, "%s", axis->name_axis_y);

	al_destroy_font(font);
}