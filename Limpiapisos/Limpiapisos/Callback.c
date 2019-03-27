#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Callback.h"
#include "UserData.h"

int parseCallBack(const char* key, const char* value, void* userData) //chequea si los datos ingresados por la linea de comandos son validos
{
	int tempValue = atoi(value);
	userData_t* myData = (userData_t*)userData;

	//checking if option is valid
	if (key != NULL) //es opcion
	{
		if (!strcmp(key, "height") && 0 < tempValue && tempValue <= 70) //altura del piso
		{
			if (!setUserData(myData, HEIGHT, tempValue))
			{
				printf("%s\n", "Error: Option 'Height' has been set more than once");
				return CB_ERR;
			}
		}
		else if (!strcmp(key, "width") && 0 < tempValue && tempValue <= 100)//ancho del piso
		{
			if (!setUserData(myData, WIDTH, tempValue))
			{
				printf("%s\n", "Error: Option 'Width' has been set more than once");
				return CB_ERR;
			}
		}
		else if (!strcmp(key, "robots") && 0 < tempValue)//cantidad de robots
		{
			if (!setUserData(myData, ROBOTC, tempValue))
			{
				printf("%s\n", "Error: Option 'robots' has been set more than once");
				return CB_ERR;
			}
		}
		else if (!strcmp(key, "mode") && (tempValue == 1 || tempValue == 2))//modo
		{
			if (!setUserData(myData, MODE, tempValue))
			{
				printf("%s\n", "Error: Option 'mode' has been set more than once");
				return CB_ERR;
			}
		}
		else //option not valid
		{
			printf("%s\n", "Invalid Option");
			return CB_ERR;
		}
	}

	else
	{
		printf("%s\n", "This program does not accept parameters. Invalid input");
		return CB_ERR;
	}

	return CB_SUXS; //devuelve 1 si ingreso bien los datos y 0 si los ingreso mal
}
