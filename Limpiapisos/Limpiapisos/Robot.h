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


robot_t * create_Robot(unsigned int pos_lim_x, unsigned int pos_lim_y);			//ver si conviene que devuelva otra cosa y/o reciba mas parametros
bool	move_Robot(robot_t * robot, unsigned int pos_lim_x, unsigned int pos_lim_y); 
//ver si conviene que devuelva otra cosa y/o reciba mas parametros
void	destroy_Robot(robot_t * robot);	//ver si conviene que devuelva otra cosa y/o reciba mas parametros


#endif //ROBOT_H

