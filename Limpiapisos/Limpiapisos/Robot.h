#pragma once

#ifndef ROBOT_H
#define ROBOT_H

#include <stdbool.h>

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


robot_t * create_Robot(void);			//ver si conviene que devuelva otra cosa y/o reciba mas parametros
bool	move_Robot(robot_t * robot); //ver si conviene que devuelva otra cosa y/o reciba mas parametros
bool	destroy_Robot(robot_t * robot);	//ver si conviene que devuelva otra cosa y/o reciba mas parametros


#endif //ROBOT_H

