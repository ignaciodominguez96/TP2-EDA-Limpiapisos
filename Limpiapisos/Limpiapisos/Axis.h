#pragma once

#ifndef AXIS_H

#define AXIS_H

#include <allegro5\allegro_color.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_image.h>
#include <allegro5/allegro_primitives.h>


/* ESTRUCTURA: Ejes cartesianos */

typedef struct {
	unsigned int space_x;			//margenes de la coordenada x
	unsigned int space_y;			//margenes de la coordenada y
	float max_x;					//valor maximo de x                   
	float max_y;					//valor maximo de y  
	float el_scale_x;				//valor del marcador de escala de la coordena x       
	float el_scale_y;				//valor del marcador de escala de la coordena y   
	unsigned int long_axis_x;       //longitud del eje x  
	unsigned int long_axis_y;		//longitud del eje y 
	unsigned int thickness;			//grosor del eje            
	char * name_axis_x;             //nombre del eje x
	char * name_axis_y;				//nombre del eje y
	unsigned int cant_x;			//cantidad de marcadores sobre el eje x          
	unsigned int cant_y;			//cantidad de marcadores sobre el eje y
	unsigned int origin_x;          //origen del eje x
	unsigned int origin_y;			//origen del eje y

}axis_t;


axis_t * create_axis(double width, double height, double max_x, double max_y, char * name_var_x, char * name_var_y);
/*
Funcion que crea la estructura axis_t segun el tamaño que se le indice (width y height), indicandole tambien la cantidad de elementos
que tiene en dichas coordenadas x e y (max_x y max_y)

Tambien se indica los nombres del grafico de los ejes en dichas coordenadas

NO SE ESCRIBE EN EL DISPLAY, para graficarlo se debe utilizar la funcion print_axis
*/


void print_axis(axis_t * axis);

/*
Se escribe en bitmap actual los ejes caracterizados por la estructura que lo representa (axis_t), del cual se tiene su puntero por parametro

NO SE MUESTRA EN DISPLAY, para mostrar por display se debe realizar un al_flip_display()

*/

#endif // !AXIS_H

