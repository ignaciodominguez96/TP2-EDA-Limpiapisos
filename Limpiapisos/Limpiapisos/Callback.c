#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Callback.h"
#include "UserData.h"

int parseCallBack(const char* key, const char* value, void* userData)
{
	int tempValue = atoi(value);

	//checking if option is valid
	if (key != NULL) //es opcion
	{
		if (!strcmp(key, "height") && 0 < tempValue && tempValue <= 70) //check if key is valid
		{
			if (!(((userData_t*)userData)->heightSet))
			{
				((userData_t*)userData)->heightSet = true;
				((userData_t*)userData)->height = tempValue;
				((userData_t*)userData)->fullfiled++;
			}
		}
		else if (!strcmp(key, "width") && 0 < tempValue && tempValue <= 100)
		{
			if (!(((userData_t*)userData)->widthSet))
			{
				((userData_t*)userData)->widthSet = true;
				((userData_t*)userData)->width = tempValue;
				((userData_t*)userData)->fullfiled++;
			}
		}
		else if (!strcmp(key, "robots") && 0 < tempValue)
		{
			if (!(((userData_t*)userData)->robotSet))
			{
				((userData_t*)userData)->robotSet = true;
				((userData_t*)userData)->robotCount = tempValue;
				((userData_t*)userData)->fullfiled++;
			}
		}
		else if (!strcmp(key, "mode") && (tempValue == 1 || tempValue == 2))
		{
			if (!(((userData_t*)userData)->modeSet))
			{
				((userData_t*)userData)->modeSet = true;
				((userData_t*)userData)->mode = tempValue;
				((userData_t*)userData)->fullfiled++;
			}
		}
		else //option not valid
			return CB_ERR;
	}

	else
	{

	}

	return CB_SUXS;
}






/*
static int validKey(const char* clave) //return 1 if key is valid
{ 
	if (!strcmp(clave, "height"))
	{

	}
}

static int validValue(const char* valor) { //return 1 if value is valid

	if (strlen(valor) > (MAXLENGTH - 1))	//verifica el largo del valor
	{
		printf("Supero el limite de %d caracteres del valor\n", MAXLENGTH);
		return CB_ERR;
	}
	else
	{
		//free space for validation
		return CB_SUXS;
	}
}*/