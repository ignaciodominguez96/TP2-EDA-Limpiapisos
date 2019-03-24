
#include <stdlib.h>
#include <math.h>

#include "Robot.h"
#include "Random.h"

#define M_PI acos(-1.0)
#define SHIFT_ANGLE_X 90
#define SHIFT_ANGLE_Y 90
#define DEGREES_TO_RAD(x) (((x)*(M_PI))/180.0)

//DECLARACION DE FUNCIONES AUXILIARES
static bool	move_Robot(robot_t * robot, unsigned int pos_lim_x, unsigned int pos_lim_y);
//ver si conviene que devuelva otra cosa y/o reciba mas parametros
static void changedir_Robot(robot_t* robot);


//FUNCIONES PRINCIPALES
robot_t * 
create_Robots(unsigned int pos_lim_x, unsigned int pos_lim_y, int cantRobots)
{
	robot_t * robot = NULL;

	robot = (robot_t *) malloc(sizeof(robot_t)*cantRobots);

	if (robot != NULL)
	{
		for (int i = 0; i < cantRobots; i++)
		{
			(robot + i)->pos.x = randDoubleBetween(0.0, (double)pos_lim_x);
			(robot + i)->pos.y = randDoubleBetween(0.0, (double)pos_lim_y);
			(robot + i)->angle = randDoubleBetween(0.0, (double)ANGLE_MAX);
		}
	}
	else
	{
		free(robot);
		robot = NULL;
	}


	return robot;

}

double
get_Robot_posx(robot_t* robot)
{
	return robot->pos.x;
}

double 
get_Robot_posy(robot_t* robot)
{
	return robot->pos.x;
}

double
get_Robot_angle(robot_t* robot)
{

	return robot->angle;

}

bool
act_Robot(robot_t* robot, unsigned int pos_lim_x, unsigned int pos_lim_y)
{
	bool did_robot_move = false;

	if (move_Robot(robot, pos_lim_x, pos_lim_y))
	{
		did_robot_move = true;
		return did_robot_move;
	}
	else
	{
		changedir_Robot(robot);
		return did_robot_move;
	}
}

void	
destroy_Robots(robot_t * robot)
{
	free(robot);
	robot = NULL;

}

//FUNCIONES AUXILIARES
static bool
move_Robot(robot_t * robot, unsigned int pos_lim_x, unsigned int pos_lim_y)
{

	bool can_i_move_Robot = false;

#error "chequear si esta bien lo de lo mover con los angulos"

	double pos_aux_x = robot->pos.x + cos(DEGREES_TO_RAD(robot->angle - SHIFT_ANGLE_X));
	double pos_aux_y = robot->pos.y + sen(DEGREES_TO_RAD(robot->angle - SHIFT_ANGLE_Y));

	if ((pos_aux_x >= 0) && (pos_aux_x < pos_lim_x) && (pos_aux_y >= 0) && (pos_aux_y < pos_lim_y))
	{
		robot->pos.x = pos_aux_x;
		robot->pos.y = pos_aux_y;

		can_i_move_Robot = true;
	}

	return can_i_move_Robot;

}

static void
changedir_Robot(robot_t* robot)
{
	robot->angle = randDoubleBetween(0.0, (double)ANGLE_MAX);
}