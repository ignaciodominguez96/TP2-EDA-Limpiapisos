#pragma once
#ifndef USERDATA_H
#define USERDATA_H

#include <stdbool.h>

typedef struct {
	int height;
	int width;
	int robotCount;
	int mode;
	bool heightSet;
	bool widthSet;
	bool robotSet;
	bool modeSet;
	int fullfiled;
}userData_t;

#endif