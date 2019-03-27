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

/*
Funcion que crea la estructura robots (arreglo de robots), guardando en memoria la misma
Se le indica la cantidad de robots que crea ("cantRobots") y cuales son las posiciones maximas ("pos_lim_y" y "pos_lim_x")
que puede adoptar en el espacio, ya sea en la coordenada x y/o coordenada y (tener en cuenta que la posicion solo puede 
tomar valores positivos o nulos)

Se devuelve un puntero a la memoria que se guardo para dicha estructura,
el cual se debe destruir cuando no se lo utilice mas

*/

double get_Robot_posx(robot_t* robot);

/*

Se obtiene la posicion x del robot que se le pasa por parametros

*/

double get_Robot_posy(robot_t* robot);

/*

Se obtiene la posicion y del robot que se le pasa por parametros

*/

double get_Robot_angle(robot_t* robot);

/*

Se obtiene el angulo con el que se mueve el robot ( robot que se le pasa por parametros )

*/

bool act_Robot(robot_t* robot, unsigned int pos_lim_x, unsigned int pos_lim_y);

/*
Funcion que hace actuar al robot

Se fija si el robot se puede mover (es decir que no rebota con alguno de los limites del espacio del mismo)
Si no rebota o "choca" en el movimiento, realiza dicho movimiento
Si rebota, se cambia el angulo de dicho robot

la funcion devuelve un bool indicando si es que no hubo rebote (true) o no.

*/



void	destroy_Robots(robot_t * robot);

/*
Funcion que destruye la estructura robots que se le pasa por parametros, liberando la memoria guardada para
la estructura

*/



#endif //ROBOT_H

