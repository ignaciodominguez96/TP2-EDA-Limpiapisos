#pragma once

#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdbool.h>

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_color.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_image.h>

#include "Images.h"
#include "Floor.h"
#include "Robot.h"

#include "Axis.h"


#define FPS 5.0			//cantidad de actualizaciones o ticks por segundo en el modo 1

/*  ESTRUCTURA: ALLEGRO  */

/*Contiene todos los elementos propios de Allegro que se utilizan en el proyecto, en este caso es solamente un display*/

typedef struct
{

	ALLEGRO_DISPLAY *display;	//puntero al display que se utiliza en el proyecto


} allegroStruct_t;



allegroStruct_t* allegro_setup(allegroStruct_t* usrAllegro, unsigned int height, unsigned int width);
/*
Funcion que crea la estructura allegro, guardando en memoria la misma
Se le indica el tamaño del mismo del display (heigh y width)

Se devuelve un puntero a la memoria que se guardo para dicha estructura,
el cual se debe destruir cuando no se lo utilice mas

*/


void allegro_destroy(allegroStruct_t* usrAllegro);

/*
Funcion que destruye la estructura allegro que se le pasa por parametros, liberando la memoria guardada para
la estructura

*/


void display_TickCount(unsigned int height, unsigned int width, unsigned int tickCount);



void update_display_Output(floor_t * floor, robot_t * robots, unsigned int cant_robots, images_t* images);

/*
Funcion que muestra las baldosas y robots en sus posiciones correspondientes (indicados a traves de floor y robots)
en pantalla con las imagenes que se encuentran en images

Funcion que se utiliza en el modo 1
*/

void print_histogram_Output(unsigned int cant_robots, double * results, ALLEGRO_DISPLAY * display, char * axis_name_x, char *  axis_name_y);

/*
Funcion que imprime en pantalla el histograma del modo 2
El histograma se imprime en el display indicado por la variable "display"
La cantidad de robots maxima se indica por la variable "cant_robots"
El nombre del eje x se indica por la variable "axis_name_x" y el nombre del eje y se indica por la variable "axis_name_y"
Los resultados que tuvo para cada robot (tickcount medio) se indica por el arreglo del cual se tiene su puntero llamado "results"

*/



#endif //OUTPUT_H