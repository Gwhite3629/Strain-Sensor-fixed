//  Measurements Header
//  Dynamic Strain Sensor
//  Grady White
//  1/3/22

#ifndef _MEASUREMENTS_H_
#define _MEASUREMENTS_H_

#include <stdint.h>
#include <windows.h>

#define FULL 0
#define PART 1
#define SING 2

int full_measure();

int part_measure();

int get_curve(HANDLE fd, float **output);

#endif //_MEASUREMENTS_H_