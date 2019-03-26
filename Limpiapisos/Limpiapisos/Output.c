#define _USE_MATH_DEFINES
#include "math.h"
#include <stdio.h>
#include "Dimension.h"
#include "Output.h"


#define DEGREES_TO_RAD(x) (((x)*(M_PI))/180.0)


#define VECTOR_COLOR "black"
#define	VECTOR_THICKNESS 0.8	//<=0

#define REFACTOR_HISTOGRAM_TICK_SPACE	(1/11.0)
#define REFACTOR_HISTOGRAM_TICK_PER_SPACE	(1/10.0)

#define	HISTOGRAM_FILE_FONT	"Starjedi.ttf"
#define HISOGRAM_COLOR_BAR	"green"
#define	HISTOGRAM_COLOR_FONT	"hotpink"
#define HISTOGRAM_COLOR_BACK "black"
#define HISTOGRAM_COLOR_REFERENCE "lightblue"
#define	HISTOGRAM_COLOR_AXIS	"white"



//DECLARACIONES FUNCIONES AUXILIARES

void update_robots_Output(robot_t* robots, unsigned int cant_robots, ALLEGRO_BITMAP* image_robot);
void update_tiles_Output(floor_t * floor, image_tiles_t * images_tiles);



allegroStruct_t* allegro_setup(allegroStruct_t* usrAllegro)
{
	usrAllegro = NULL;
	usrAllegro = (allegroStruct_t*)malloc(sizeof(allegroStruct_t));

	if (usrAllegro != NULL)
	{
		usrAllegro->event_queue = NULL;
		usrAllegro->display = NULL;
		usrAllegro->timer = NULL;

		if (!al_init())//inicio allegro
		{
			printf("Could not initialize Allegro!\n");
			return NULL;
		}


		usrAllegro->display = al_create_display(960, 800);
		if (!(usrAllegro->display))//inicio display
		{
			printf("Could not initialize Display!.\n");
			return NULL;
		}

		usrAllegro->event_queue = al_create_event_queue();
		if (!(usrAllegro->event_queue))//inicio cola de eventos
		{
			printf("Could not initialize event queue!.\n");
			al_destroy_display(usrAllegro->display);
			return NULL;
		}

		usrAllegro->timer = al_create_timer(1 / FPS); //FIJARSE POR QUE NO LO RECONOCE (y si conviene 60, esto parece copiado de otro prog)
		if (!(usrAllegro->timer))//inicio timer IMPORTANTE FUNCIONA  A 60 FPS
		{
			printf("Failed to create timer!\n");
			al_destroy_event_queue(usrAllegro->event_queue);
			al_destroy_display(usrAllegro->display);
			return NULL;
		}

		al_set_window_title(usrAllegro->display, "Limpiapisos");

		al_register_event_source(usrAllegro->event_queue, al_get_display_event_source(usrAllegro->display));
		al_register_event_source(usrAllegro->event_queue, al_get_timer_event_source(usrAllegro->timer));

		al_start_timer(usrAllegro->timer);

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
	al_destroy_timer(usrAllegro->timer);
	usrAllegro->timer = NULL;
	al_destroy_event_queue(usrAllegro->event_queue);
	usrAllegro->event_queue = NULL;
	free(usrAllegro);
	usrAllegro = NULL;

	al_shutdown_font_addon();
	al_shutdown_ttf_addon();
	al_shutdown_primitives_addon();
	al_shutdown_image_addon();
}

void update_display_Output(floor_t * floor, robot_t * robots, unsigned int cant_robots, images_t* images)
{

	update_tiles_Output(floor, images->images_tiles);
	update_robots_Output(robots, cant_robots, images->image_robot);

}


//#error "cambiar nombre variables"

bool 
print_histogram_Output( ALLEGRO_DISPLAY* display, unsigned int cant_simulations, unsigned long* tick_per_simulation)
{

	bool can_print;

	ALLEGRO_FONT* font = al_load_ttf_font(HISTOGRAM_FILE_FONT, UNITY_FONT_LETTER, 0);
	
	if (font == NULL)
	{
		can_print = false;
	}
	else
	{
		al_set_target_backbuffer(display);
		al_clear_to_color(al_color_name(HISTOGRAM_COLOR_BACK)); //pinta el display.


		unsigned int height = al_get_display_height(display);
		unsigned int width = al_get_display_width(display);

		double plane_width = width - 2.0*UNITY_FONT_SPACE; //le resto dos para que quede un cuadrado donde escribir las axis
		double plane_height = height - 2.0*UNITY_FONT_SPACE;

		double tick_space = plane_height*REFACTOR_HISTOGRAM_TICK_SPACE;
		unsigned long max_tick = tick_per_simulation[0];
		unsigned long ticks_per_space = max_tick* REFACTOR_HISTOGRAM_TICK_PER_SPACE;


		double tick_number_y = 0.0;

		//imprime los numeros sobre el eje de ticks.
		for (int j = 1; j <= 10; j++)
		{
			tick_number_y = height - (UNITY_FONT_SPACE)-j * tick_space;
			al_draw_textf(font, al_color_name(HISTOGRAM_COLOR_FONT), (UNITY_FONT_SPACE) / 2.0,
								tick_number_y, ALLEGRO_ALIGN_CENTRE, "%lu", j*ticks_per_space);
		}
		
		al_draw_text(font, al_color_name(HISTOGRAM_COLOR_REFERENCE), (UNITY_FONT_SPACE) / 2.0, (UNITY_FONT_SPACE) / 2.0,
							ALLEGRO_ALIGN_CENTRE, "Count Ticks");


		double bar_width = plane_width / (double)(cant_simulations + 1);
		double bar_space = bar_width / (double)(cant_simulations - 1);


		al_draw_line(UNITY_FONT_SPACE, height - UNITY_FONT_SPACE, width - UNITY_FONT_SPACE,
					height - UNITY_FONT_SPACE, al_color_name(HISTOGRAM_COLOR_AXIS), 2.0);
		//Dibuja el eje donde se representa el numero de robots

		al_draw_line(UNITY_FONT_SPACE, height - UNITY_FONT_SPACE, UNITY_FONT_SPACE, UNITY_FONT_SPACE,
					al_color_name(HISTOGRAM_COLOR_AXIS), 2.0);
		//dibuja el eje donde se representa el numero de Ticks.

		double upper_left_corner_x = 0.0;
		double upper_left_corner_y = 0.0;
		double lower_right_corner_x = 0.0;
		double lower_right_corner_y = 0.0;

		double number_x = 0.0;

		for (unsigned int i = 0; i < cant_simulations; i++)
		{
			upper_left_corner_x = (UNITY_FONT_SPACE)+i * (bar_width + bar_space);
			upper_left_corner_y = (height - (UNITY_FONT_SPACE)) - ((tick_per_simulation[i]) / ((double)ticks_per_space))*tick_space;
			lower_right_corner_x = upper_left_corner_x + bar_space;
			lower_right_corner_y = height - UNITY_FONT_SPACE;

			al_draw_filled_rectangle(upper_left_corner_x, upper_left_corner_y, lower_right_corner_x, lower_right_corner_y,
								al_color_name(HISOGRAM_COLOR_BAR));
			//Dibuja la barra correspondiente al robot

			number_x = (upper_left_corner_x + lower_right_corner_x) / 2.0;

			al_draw_textf(font, al_color_name(HISTOGRAM_COLOR_FONT),
						number_x, height - ((UNITY_FONT_SPACE) / 2.0), ALLEGRO_ALIGN_CENTRE, "%d", i + 1);
			//imprime el numero de robots abajo de la barra correspondiente.
			
			al_draw_text(font, al_color_name(HISTOGRAM_COLOR_REFERENCE),
				width - (UNITY_FONT_SPACE) / 2.0, height - (UNITY_FONT_SPACE) / 2.0, ALLEGRO_ALIGN_CENTRE, "Cant Robots");
	
			can_print = true;
		
		}

		
		
		
		al_destroy_font(font);

		
	}


	return can_print;

	

}




//FUNCIONES AUXILIARES


void update_tiles_Output(floor_t * floor, image_tiles_t * images_tiles)
{
	unsigned int height = floor->height;
	unsigned int width = floor->width;


	bool is_clean_tile;
	//position_t position;


	for (unsigned int i = 0; i < height; i++) //actualiza todas las baldosas segun sus estados.
	{
		for (unsigned int j = 0; j < width; j++)
		{

			is_clean_tile = is_clean_Tile((floor->tiles) + i + j * width);
			//	position = getPisoLocation(baldosas, i, j);

				//#error "creo que no es necesario"

			if (is_clean_tile == true)
			{
				al_draw_bitmap(images_tiles->image_tile_clean, i, j, 0); //dibuja la baldosa limpia.
			}
			else
			{
				al_draw_bitmap(images_tiles->image_tile_dirty, i, j, 0); //dibuja la baldosa sucia.
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
		position_x = get_Robot_posx(robots + i);
		position_y = get_Robot_posy(robots + i);

		angle = get_Robot_angle(robots + i);
		angle = DEGREES_TO_RAD(angle);
		al_draw_bitmap(image_robot, position_x, position_y, 0); //dibuja el robot en su posicion del display

		vector.x = position_x + UNITY_VECTOR * cos(angle);
		vector.y = position_y - UNITY_VECTOR * sin(angle);

		al_draw_line((vector.x) + (UNITY_ROBOT) / 2.0, (vector.y) + (UNITY_ROBOT) / 2.0, vector.x, vector.y,
			al_color_name(VECTOR_COLOR), VECTOR_THICKNESS);

		vector_vertex_head1.x = vector.x - UNITY_VECTOR_HEAD * cos(M_PI_4);
		vector_vertex_head1.y = vector.y - UNITY_VECTOR_HEAD * sin(M_PI_4);

		vector_vertex_head2.x = vector.x + UNITY_VECTOR_HEAD * cos(M_PI_4);
		vector_vertex_head2.y = vector.y + UNITY_VECTOR_HEAD * sin(M_PI_4);

		vector_vertex_head3.x = vector.x + UNITY_VECTOR_HEAD * cos(M_PI_4);
		vector_vertex_head3.y = vector.y - UNITY_VECTOR_HEAD * sin(M_PI_4);

		al_draw_filled_triangle(vector_vertex_head1.x, vector_vertex_head1.y,
			vector_vertex_head2.x, vector_vertex_head2.y,
			vector_vertex_head3.x, vector_vertex_head3.y, al_color_name(VECTOR_COLOR));

	}
}

