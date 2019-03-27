#pragma once
#ifndef SIMULATION_H
#define SIMULATION_H

#include <stdbool.h>
#include "Robot.h"
#include "Floor.h"
#include "Output.h"

#define	MODE_1	1		//MODO TIEMPO REAL
#define	MODE_2	2		//MODO HISTOGRAMA

#define CANT_SIMULATIONS_MODE_2 1000.0 //cantidad de simulaciones que se realiza en el modo 2 por una misma cantidad de robot


/*   ESTRUCTURA: SIMULACION   */
typedef struct
{
	robot_t	* robots;						//puntero a los robots de la simulacion
	unsigned int cant_robots;				//cantidad de robots que se encuentra en la simulacion
	floor_t * floor;						//piso que estan limpiando los robots en la simulacion
	unsigned int mode;						//en que modo se esta simulando
	unsigned int tickcount;					//indica cuantos movimientos se hizo en la simulacion
	images_t * images;						//puntero a las imagenes que se utiliza en el modo 1, para graficar en el display
	allegroStruct_t* usrAllegro;			//puntero a los elementos Allegro que se utiliza en la simulacion

}simulation_t;

simulation_t * create_Simulation(unsigned int cant_robots, unsigned int height, unsigned int width, unsigned int mode, allegroStruct_t* usrAllegro);

/*
Funcion que crea la estructura simulacion, guardando en memoria la misma
Se le indica el tamaño del piso (heigh y width) sobre la cual se va a simular
Se le indica la cantidad de robots que van a limpiar en la simulacion
Se le indica el modo en el cual se va a simular
Se le indica que elementos de Allegro se van a utilizar en la simulacion

Se devuelve un puntero a la memoria que se guardo para dicha estructura,
el cual se debe destruir cuando no se lo utilice mas

*/

bool	simulate_Simulation(simulation_t * simulation);

/*
Funcion que corre la simulacion con las caracteristicas indicadas en la
estructura (del cual se tiene el puntero "simulation")

*/



unsigned int get_tickcount_Simulation(simulation_t * simulation);

/*

Se obtiene el tickcount de la simulacion que se le pasa por parametros

*/


void	destroy_Simulation(simulation_t * simulation);

/*
Funcion que destruye la estructura simulacion que se le pasa por parametros, liberando la memoria guardada para
la estructura

*/

#endif //SIMULATION_H