#pragma once
#ifndef USERDATA_H
#define USERDATA_H

#include <stdbool.h>

#define EMPTY 0

typedef enum {HEIGHT, WIDTH, ROBOTC, MODE} data_t;

typedef struct {
	unsigned int height;
	unsigned int width;
	unsigned int robotCount;
	unsigned int mode;
}userData_t;

userData_t* createUserData();
bool setUserData(userData_t* userData, data_t field, int value);
int getUserData(userData_t* userData, data_t field);
bool isDataFull(userData_t* data);
void destroyUserData(userData_t* userData);

#endif