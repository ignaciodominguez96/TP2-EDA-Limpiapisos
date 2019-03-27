#pragma once
#ifndef USERDATA_H
#define USERDATA_H

#include <stdbool.h>

#define EMPTY 0		//los campos de la estructura userData se inicializan con esta constante

typedef enum {HEIGHT, WIDTH, ROBOTC, MODE} data_t;	//los distintos datos que se pueden pedir o modificar en la estructura

typedef struct {
	unsigned int height;
	unsigned int width;
	unsigned int robotCount;
	unsigned int mode;
}userData_t;

userData_t* createUserData();	//esta funcion crea una instancia de la estructura userData y la incializa con la constante EMPTY en cada campo
bool setUserData(userData_t* userData, data_t field, int value);	//esta funcion modifica el dato seleccionado con el valor recibido por argumento
int getUserData(userData_t* userData, data_t field);	//esta funcion devuelve el dato especificado
bool isDataFull(userData_t* data);	//esta funcion devuelve 'true' si todos los datos han sido ingresados exitosamente, 'false' si no
void destroyUserData(userData_t* userData);	//esta funcion libera la memoria pedida por la estructura 

#endif