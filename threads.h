//  Thread Header
//  Dynamic Strain Sensor
//  Grady White
//  1/7/22

#ifndef _THREADS_H_
#define _THREADS_H_

#include <stdatomic.h>

atomic_bool exit_runtime = 0;

void *quit_condition(void *arg);

void *time_measure(void *arg);

void *find_peak(void *arg);

#endif //_THREADS_H_