#pragma once

#ifndef ROBOT_H
#define ROBOT_H

#include <stdbool.h>

#define	ANGLE_MAX	360 //angulo maximo posible para el angulo que tiene cada robot


/* ESTRUCTURA: POSICION  */
typedef struct
{
	double x;		//posicion x
	double y;		//posicion y

} position_t;


/* ESTRUCTURA: ROBOT  */

typedef struct
{
	position_t pos;	//posicion del robot
	double	angle;	//angulo con el que se mueve el robot (tener que el 0° apunta al norte)

}robot_t;


robot_t * create_Robots(unsigned int pos_lim_x, unsigned int pos_lim_y, int cantRobots);	
double get_Robot_posx(robot_t* robot);
double get_Robot_posy(robot_t* robot);
double get_Robot_angle(robot_t* robot);
bool act_Robot(robot_t* robot, unsigned int pos_lim_x, unsigned int pos_lim_y);
void	destroy_Robots(robot_t * robot);	


#endif //ROBOT_H

