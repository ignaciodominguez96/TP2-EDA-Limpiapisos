#define _USE_MATH_DEFINES
#include "math.h"
#include <stdio.h>
#include "Dimension.h"
#include "Colors.h"
#include "Type_fonts.h"

#include "Output.h"




#define DEGREES_TO_RAD(x) (((x)*(M_PI))/180.0)

#define SHIFT_ANGLE_X 90
#define SHIFT_ANGLE_Y 90


#define REFACTOR_HISTOGRAM_TICK_SPACE	(1/100.0)
#define REFACTOR_HISTOGRAM_TICK_PER_SPACE	(1/50.0)

#define TOLERANCE_FONT_ROBOT 28



//DECLARACIONES FUNCIONES AUXILIARES

void update_robots_Output(robot_t* robots, unsigned int cant_robots, ALLEGRO_BITMAP* image_robot);
void update_tiles_Output(floor_t * floor, image_tiles_t * images_tiles);



allegroStruct_t* allegro_setup(allegroStruct_t* usrAllegro, unsigned int height, unsigned int width)
{
	usrAllegro = (allegroStruct_t*)malloc(sizeof(allegroStruct_t));

	if (usrAllegro != NULL)
	{
		usrAllegro->display = NULL;

		if (!al_init())//inicio allegro
		{
			printf("Could not initialize Allegro!\n");
			return NULL;
		}

		usrAllegro->display = al_create_display(UNITY_TILE*width, UNITY_TILE*height);
		
		if (!(usrAllegro->display))//inicio display
		{
			printf("Could not initialize Display!.\n");
			return NULL;
		}

		al_set_window_title(usrAllegro->display, "Limpiapisos");

		al_init_image_addon();
		al_init_font_addon();
		al_init_primitives_addon();
		al_init_ttf_addon();

	}

	return usrAllegro;

}

void allegro_destroy(allegroStruct_t* usrAllegro)
{
	al_destroy_display(usrAllegro->display);
	usrAllegro->display = NULL;
	free(usrAllegro);
	usrAllegro = NULL;

	al_shutdown_font_addon();
	al_shutdown_ttf_addon();
	al_shutdown_primitives_addon();
	al_shutdown_image_addon();
}

void display_TickCount(unsigned int height, unsigned int width, unsigned int tickCount)
{
	ALLEGRO_FONT* font = al_load_ttf_font(HISTOGRAM_FILE_FONT, 20.0, 0);
	if (font != NULL);
	{
		al_clear_to_color(al_color_name("white"));
		al_draw_textf(font, al_color_name("black"), width*UNITY_TILE/2.0, height*UNITY_TILE/2.0-10.0, ALLEGRO_ALIGN_CENTER,
			"Final tick count: %d", tickCount);
		al_draw_textf(font, al_color_name("black"), width*UNITY_TILE / 2.0, height*UNITY_TILE / 2.0 + 10.0, ALLEGRO_ALIGN_CENTER,
			"Press 'enter' to exit", tickCount);
		al_flip_display();
		al_destroy_font(font);
	}
}

void update_display_Output(floor_t * floor, robot_t * robots, unsigned int cant_robots, images_t* images)
{

	update_tiles_Output(floor, images->images_tiles);
	update_robots_Output(robots, cant_robots, images->image_robot);

}





void print_histogram_Output(unsigned int cant_robots, double * results,  ALLEGRO_DISPLAY * display, char * axis_name_x, char *  axis_name_y)
{
	al_clear_to_color(al_color_name(HISTOGRAM_COLOR_BACK));

	axis_t * axis = create_axis(al_get_display_width(display), al_get_display_height(display), (double)cant_robots, results[0], axis_name_x, axis_name_y);
	print_axis(axis);


	ALLEGRO_COLOR color = al_color_name(HISTOGRAM_COLOR_BAR);
	ALLEGRO_COLOR color_font = al_color_name(HISTOGRAM_COLOR_FONT);


	ALLEGRO_FONT * font = al_load_ttf_font(HISTOGRAM_FILE_FONT, FONT_SIZE_HISTOGRAM, 0);


	double x = 0.0, y = 0.0;

	for (int i = 0; i < axis->max_x; i++)
	{
		x = axis->space_x + (axis->el_scale_x * (i + 1));
		y = axis->space_y + (axis->el_scale_y * (axis->max_y - results[i]));
		
		
		al_draw_filled_rectangle(x - OFFSET_HISTOGRAM, y, x + OFFSET_HISTOGRAM, axis->origin_y, color);
		

		al_draw_textf(font, color_font, x - OFFSET_HISTOGRAM, y - (OFFSET_HISTOGRAM * 2), 0, "%.1f", results[i]);
		
	}
	al_flip_display();

	al_destroy_font(font);
}


//FUNCIONES AUXILIARES


void update_tiles_Output(floor_t * floor, image_tiles_t * images_tiles)
{
	unsigned int height = floor->height;
	unsigned int width = floor->width;


	bool is_clean_tile;


	for (unsigned int i = 0; i < height; i++) //actualiza todas las baldosas segun sus estados.
	{
		for (unsigned int j = 0; j < width; j++)
		{

			is_clean_tile = is_clean_Tile((floor->tiles) + j + i * width);
			//	position = getPisoLocation(baldosas, i, j);

				//#error "creo que no es necesario"

			if (is_clean_tile == true)
			{
				al_draw_bitmap(images_tiles->image_tile_clean, j*UNITY_TILE, i*UNITY_TILE, 0); //dibuja la baldosa limpia.
			}
			else
			{
				al_draw_bitmap(images_tiles->image_tile_dirty, j*UNITY_TILE, i*UNITY_TILE, 0); //dibuja la baldosa sucia.
			}
		}

	}
}


void update_robots_Output(robot_t* robots, unsigned int cant_robots, ALLEGRO_BITMAP* image_robot)
{
	double position_x = 0.0;
	double position_y = 0.0;

	position_t vector = { 0.0 , 0.0 };
	position_t vector_vertex_head1; //Representan los tres vertices del triangulo que forma
	position_t vector_vertex_head2; //la cabeza del vector.
	position_t vector_vertex_head3;

	//unsigned int unit = (robots->unit);
	//#error "creo que no es necesario"

	double angle = 0.0;

	for (unsigned int i = 0; i < cant_robots; i++)
	{
		position_x = get_Robot_posx(robots + i)*UNITY_TILE;
		position_y = get_Robot_posy(robots + i)*UNITY_TILE;

		angle = get_Robot_angle(robots + i);
		angle = DEGREES_TO_RAD(angle);
		al_draw_bitmap(image_robot, position_x - (UNITY_ROBOT/2.0) , position_y - (UNITY_ROBOT/ 2.0), 0); //dibuja el robot en su posicion del display

		vector.x = position_x + UNITY_VECTOR * cos(angle - DEGREES_TO_RAD(SHIFT_ANGLE_X));
		vector.y = position_y + UNITY_VECTOR * sin(angle - DEGREES_TO_RAD(SHIFT_ANGLE_Y));

		al_draw_line(position_x, position_y, vector.x, vector.y, al_color_name(VECTOR_COLOR), VECTOR_THICKNESS);

		vector_vertex_head1.x = vector.x - UNITY_VECTOR_HEAD *cos(angle + M_PI_4 - DEGREES_TO_RAD(SHIFT_ANGLE_X));
		vector_vertex_head1.y = vector.y - UNITY_VECTOR_HEAD *sin(angle + M_PI_4 - DEGREES_TO_RAD(SHIFT_ANGLE_Y));


		vector_vertex_head2.x = vector.x + UNITY_VECTOR_HEAD * cos(angle + M_PI_4 - DEGREES_TO_RAD(SHIFT_ANGLE_X));
		vector_vertex_head2.y = vector.y - UNITY_VECTOR_HEAD * sin(angle + M_PI_4 - DEGREES_TO_RAD(SHIFT_ANGLE_Y));

		vector_vertex_head3.x = vector.x - UNITY_VECTOR_HEAD * cos(angle + M_PI_4 - DEGREES_TO_RAD(SHIFT_ANGLE_X));
		vector_vertex_head3.y = vector.y - UNITY_VECTOR_HEAD * sin(angle + M_PI_4 - DEGREES_TO_RAD(SHIFT_ANGLE_Y));

		al_draw_filled_triangle(vector_vertex_head1.x, vector_vertex_head1.y,
			vector_vertex_head2.x, vector_vertex_head2.y,
			vector_vertex_head3.x, vector_vertex_head3.y, al_color_name(VECTOR_COLOR));

	}
}

