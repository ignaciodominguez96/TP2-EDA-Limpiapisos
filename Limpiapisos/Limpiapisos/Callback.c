#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Callback.h"
#include "UserData.h"

int parseCallBack(const char* key, const char* value, void* userData)
{
	int tempValue = atoi(value);
	userData_t* myData = (userData_t*)userData;

	//checking if option is valid
	if (key != NULL) //es opcion
	{
		if (!strcmp(key, "height") && 0 < tempValue && tempValue <= 70)
		{
			if (!setUserData(myData, HEIGHT, tempValue))
			{
				printf("%s\n", "Error: Option 'Height' has been set more than once");
				return CB_ERR;
			}
		}
		else if (!strcmp(key, "width") && 0 < tempValue && tempValue <= 100)
		{
			if (!setUserData(myData, WIDTH, tempValue))
			{
				printf("%s\n", "Error: Option 'Width' has been set more than once");
				return CB_ERR;
			}
		}
		else if (!strcmp(key, "robots") && 0 < tempValue)
		{
			if (!setUserData(myData, ROBOTC, tempValue))
			{
				printf("%s\n", "Error: Option 'robots' has been set more than once");
				return CB_ERR;
			}
		}
		else if (!strcmp(key, "mode") && (tempValue == 1 || tempValue == 2))
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

	return CB_SUXS;
}