#pragma once

#ifndef ROBOT_H
#define ROBOT_H

#include <stdbool.h>

#define	ANGLE_MAX	360


typedef struct
{
	double x;
	double y;
} position_t;

typedef struct
{
	position_t pos;
	double	angle;

}robot_t;


robot_t * create_Robots(unsigned int pos_lim_x, unsigned int pos_lim_y, int cantRobots);	//ver si conviene que devuelva otra cosa y/o reciba mas parametros
double get_Robot_posx(robot_t* robot);
double get_Robot_posy(robot_t* robot);
double get_Robot_angle(robot_t* robot);
bool act_Robot(robot_t* robot, unsigned int pos_lim_x, unsigned int pos_lim_y); //ver si conviene que devuelva otra cosa y/o reciba mas parametros
void	destroy_Robots(robot_t * robot);	//ver si conviene que devuelva otra cosa y/o reciba mas parametros


#endif //ROBOT_H

