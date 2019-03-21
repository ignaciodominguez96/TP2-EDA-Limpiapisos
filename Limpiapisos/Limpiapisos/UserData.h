#pragma once
#ifndef USERDATA_H
#define USERDATA_H

#include <stdbool.h>

typedef struct {
	unsigned int height;
	unsigned int width;
	unsigned int robotCount;
	unsigned int mode;
	bool heightSet;
	bool widthSet;
	bool robotSet;
	bool modeSet;
	int fullfiled;
}userData_t;

#endif