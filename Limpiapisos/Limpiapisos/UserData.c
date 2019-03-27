#include <stdlib.h>
#include "UserData.h"

//esta funcion crea una instancia de la estructura userData y la incializa con la constante EMPTY en cada campo
userData_t* createUserData()
{
	userData_t* data = NULL;
	data = (userData_t*)malloc(sizeof(userData_t));
	if (data != NULL)
	{
		data->height = EMPTY;
		data->width = EMPTY;
		data->robotCount = EMPTY;
		data->mode = EMPTY;
	}
	return data;
}

//esta funcion modifica el dato seleccionado con el valor recibido por argumento
bool setUserData(userData_t* userData, data_t field, int value)
{
	bool success = false;

	switch (field)
	{
	case HEIGHT:
		if (!(userData->height))
		{
			userData->height = value;
			success = true;
		}
		break;
	case WIDTH:
		if (!(userData->width))
		{
			userData->width = value;
			success = true;
		}
		break;
	case ROBOTC:
		if (!(userData->robotCount))
		{
			userData->robotCount = value;
			success = true;
		}
		break;
	case MODE:
		if (!(userData->mode))
		{
			userData->mode = value;
			success = true;
		}
		break;
	}

	return success;
}

//esta funcion devuelve el dato especificado
int getUserData(userData_t* userData, data_t field)
{
	switch (field)
	{
	case HEIGHT:
		return userData->height;
		break;
	case WIDTH:
		return userData->width;
		break;
	case ROBOTC:
		return userData->robotCount;
		break;
	case MODE:
		return userData->mode;
		break;
	
	default: return -1;  break;
	} 
}

//esta funcion devuelve 'true' si todos los datos han sido ingresados exitosamente, 'false' si no
bool isDataFull(userData_t* data)
{
	bool dataFull = true;

	if (data->height == EMPTY)
		dataFull = false;
	if (data->width == EMPTY)
		dataFull = false;
	if (data->robotCount == EMPTY)
		dataFull = false;
	if (data->mode == EMPTY)
		dataFull = false;

	return dataFull;
}

//esta funcion libera la memoria pedida por la estructura 
void destroyUserData(userData_t* userData)
{
	free(userData);
	userData = NULL;
}