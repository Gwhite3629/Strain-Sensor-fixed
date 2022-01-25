//  File Header
//  Dynamic Strain Sensor
//  Grady White
//  1/3/22

#ifndef _FILE_H_
#define _FILE_H_

#include <windows.h>
#include <stdio.h>

#include "utils.h"

//  Generic function to find a string in a file and return its location.
int find_event(FILE *fd, // File to search
               fpos_t *prof_start, // Event location
               char *locator); // String to search for

//  Acquires data from config file and puts it into a struct
int get_config(Config *config, // Config struct
               char *name); // Config selection

//  Template for data write
int dat_Write(HANDLE dev, // Serial device
              double Itemp, // Initial temp
              double mag, // Magnitude
              double freq, // Frequency
              double Ftemp); // Final temp

#endif //_FILE_H_