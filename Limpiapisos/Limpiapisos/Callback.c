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