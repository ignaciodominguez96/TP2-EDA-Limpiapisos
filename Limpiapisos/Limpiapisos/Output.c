#define _USE_MATH_DEFINES
#include "math.h"

#include "Dimension.h"
#include "Output.h"


#define DEGREES_TO_RAD(x) (((x)*(M_PI))/180.0)


#define VECTOR_COLOR "black"
#define	VECTOR_THICKNESS 0.8	//<=0

#define REFACTOR_HISTOGRAM_TICK_SPACE	(1/11.0)
#define REFACTOR_HISTOGRAM_TICK_PER_SPACE	(1/10.0)

#define	HISTOGRAM_FILE_FONT	""
#define HISOGRAM_COLOR_BAR	""
#define	HISTOGRAM_COLOR_FONT	""
#define HISTOGRAM_COLOR_BACK ""
#define HISTOGRAM_COLOR_REFERENCE ""
#define	HISTOGRAM_COLOR_AXIS	""

void 
update_tiles_Output(floor_t * floor, image_tiles_t * images_tiles)
{
	unsigned int height = floor->height;
	unsigned int width = floor->width;

	
	bool is_clean_tile;
	position_t position;

	
	for (unsigned int i = 0; i < height; i++) //actualiza todas las baldosas segun sus estados.
	{
		for (unsigned int j = 0; j < width; j++)
		{

			is_clean_tile = is_clean_Tile((floor->tiles)+ i + j * width );
		//	position = getPisoLocation(baldosas, i, j);

			#error "creo que no es necesario"

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


void
update_robots_Output(robot_t* robots, unsigned int cant_robots, ALLEGRO_BITMAP* image_robot)
{
	double position_x = 0.0;
	double position_y = 0.0;

	position_t vector = { 0.0 , 0.0 };
	position_t vector_vertex_head1; //Representan los tres vertices del triangulo que forma
	position_t vector_vertex_head2; //la cabeza del vector.
	position_t vector_vertex_head3;
	
	//unsigned int unit = (robots->unit);
	#error "creo que no es necesario"
	
	double angle = 0.0;

	for (unsigned int i = 0; i < cant_robots; i++)
	{
		position_x = get_Robot_posx(robots + i);
		position_y = get_Robot_posy(robots + i);

		angle = get_Robot_angle(robots + i);
		angle = DEGREES_TO_RAD(angle);
		al_draw_bitmap(image_robot, position_x, position_y, 0); //dibuja el robot en su posicion del display

		vector.x = position_x + UNITY_VECTOR*cos(angle);
		vector.y = position_y - UNITY_VECTOR*sin(angle);

		al_draw_line((vector.x)+(UNITY_ROBOT)/2.0, (vector.y) + (UNITY_ROBOT)/2.0, vector.x, vector.y,
			al_color_name(VECTOR_COLOR), VECTOR_THICKNESS);

		vector_vertex_head1.x = vector.x - UNITY_VECTOR_HEAD*cos(M_PI_4);
		vector_vertex_head1.y = vector.y - UNITY_VECTOR_HEAD*sen(M_PI_4);

		vector_vertex_head2.x = vector.x + UNITY_VECTOR_HEAD*cos(M_PI_4);
		vector_vertex_head2.y = vector.y + UNITY_VECTOR_HEAD*sen(M_PI_4);

		vector_vertex_head3.x = vector.x + UNITY_VECTOR_HEAD*cos(M_PI_4);
		vector_vertex_head3.y = vector.y - UNITY_VECTOR_HEAD*sen(M_PI_4);

		al_draw_filled_triangle(vector_vertex_head1.x, vector_vertex_head1.y,
								vector_vertex_head2.x, vector_vertex_head2.y,
								vector_vertex_head3.x, vector_vertex_head3.y, al_color_name(VECTOR_COLOR));
		
	}
}


void 
update_display_Output(simulation_t* simulation, images_t* images)
{

	update_tiles_Output(simulation->floor, images->images_tiles);
	update_robots_Output(simulation->robots, simulation->cant_robots, images->image_robot);

}


#error "cambiar nombre variables"

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
				width - (UNITY_FONT_SPACE) / 2.0, height - width - (UNITY_FONT_SPACE) / 2.0, height - (UNITY_FONT_SPACE) / 2.0,
					ALLEGRO_ALIGN_CENTRE, "Cant Robots");
	

			can_print = true;
		
		}

		
		
		
		al_destroy_font(font);

		
	}


	return can_print;

	

}


#error "no se si funciona la funcion, estoy moldeando"
unsigned long
simulation_Mode1(simulation_t * simulation, images_t* images)
{
	int count_iteration = 0;
	double position_x_robot = 0;
	double position_y_robot = 0;

	unsigned int height = (simulation->floor)->height;
	unsigned int width = (simulation->floor)->width;
	unsigned int cant_robots = simulation->cant_robots;

	robot_t * robots = simulation->robots;

	tile_t * tiles = (simulation->floor)->tiles;
	

	bool count_aux = true;
	bool finish = false;

	for (unsigned int k = 0; k < (simulation->cant_robots); k++) //Chequea si la posicion en la que empiezan todos los robots ya limpia las baldosas
	{
		position_x_robot = ((robots + k)->pos).x;
		position_y_robot = ((robots + k)->pos).y;

	#error "KE"
		((piso_t*)((simulation->piso) + (int)(simulation->width)*(int)((posRobY + ROBOT_SIZE(unit) / 2.0) / (unit)) + (int)((posRobX + ROBOT_SIZE(unit) / 2.0) / unit)))->state = true;
	}

	for (unsigned int i = 0; (i < height) && (count_aux); i++)
	{
		for (unsigned int j = 0; (j < width) && (count_aux); j++)
		{
			count_aux = is_clean_Tile(tiles + i + j * width);
		}


		if (i == (height - 1))
		{
			return 0;
		}
	}


	while (finish == false)
	{


		for (unsigned int i = 0; i < cant_robots; i++)
		{
			position_x_robot = ((robots + i)->pos).x;
			position_y_robot = ((robots + i)->pos).y;


			act_Robot(robots + i, width, height);
			
			#error "KE"
			
			((piso_t*)((simulation->piso) + (int)(simulation->width)*(int)((posRobY + ROBOT_SIZE(unit) / 2.0) / (unit)) + (int)((posRobX + ROBOT_SIZE(unit) / 2.0) / unit)))->state = true;


			update_display_Output(simulation, images);



		}


		al_rest(TIME_BTW_UPDATES);
		al_flip_display();

		for (unsigned int i = 0; (i < height) && (count_aux); i++)
		{
			for (unsigned int j = 0; (j < width) && (count_aux); j++)
			{
				count_aux = is_clean_Tile(tiles + i + j * width);

			}

			if (i == (height - 1))
			{
				finish = true;
			}
		}




		count_iteration++;
		count_aux = true;
	}

	return count_iteration;
}
