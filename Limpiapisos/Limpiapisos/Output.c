#define _USE_MATH_DEFINES
#include "math.h"

#include "Dimension.h"
#include "Output.h"


#define DEGREES_TO_RAD(x) (((x)*(M_PI))/180.0)


#define COLOR_VECTOR "black"
#define	THICKNESS_VECTOR 0.8	//<=0

void update_tiles_Output(floor_t * floor, image_tiles_t * images_tiles)
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


void update_robots_Output(robot_t* robots, unsigned int cant_robots, ALLEGRO_BITMAP* image_robot)
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

		al_draw_line((vector.x)+(UNITY_ROBOT)/2.0, (vector.y) + (UNITY_ROBOT)/2.0, vector.x, vector.y, al_color_name(COLOR_VECTOR), THICKNESS_VECTOR);

		vector_vertex_head1.x = vector.x - UNITY_VECTOR_HEAD*cos(M_PI_4);
		vector_vertex_head1.y = vector.y - UNITY_VECTOR_HEAD*sen(M_PI_4);

		vector_vertex_head2.x = vector.x + UNITY_VECTOR_HEAD*cos(M_PI_4);
		vector_vertex_head2.y = vector.y + UNITY_VECTOR_HEAD*sen(M_PI_4);

		vector_vertex_head3.x = vector.x + UNITY_VECTOR_HEAD*cos(M_PI_4);
		vector_vertex_head3.y = vector.y - UNITY_VECTOR_HEAD*sen(M_PI_4);

		al_draw_filled_triangle(vector_vertex_head1.x, vector_vertex_head1.y,
								vector_vertex_head2.x, vector_vertex_head2.y,
								vector_vertex_head3.x, vector_vertex_head3.y, al_color_name(COLOR_VECTOR));
		
	}
}


void update_display_Output(simulation_t* simulation, images_t* images)
{

	update_tiles_Output(simulation->floor, images->images_tiles);
	update_robots_Output(simulation->robots, simulation->cant_robots, images->image_robot);

}





