//  Utility Functions
//  Dynamic Strain Sensor
//  Grady White
//  1/7/22

#include <stdbool.h>

#include "utils.h"

float average(float *window, int windowSize, float *sum, int *pos, float *input)
{
    float avg;
    for (int i = 0; i < CURVE_SIZE*BIT_SIZE; i++) {
        avg = moving_average(window, windowSize, sum, (*pos), input[i]);
        (*pos)++;
        if ((*pos) >= windowSize)
            (*pos) = 0;
    }
    return avg;
}

float moving_average(float *window, int windowSize, float *sum, int pos, float next)
{
    // Update sum
    *sum = *sum - window[pos] + next;
    // Update window
    window[pos] = next;
    // Average
    return *sum/windowSize;
}

float ReverseFloat(const float inFloat)
{
   float retVal;
   char *floatToConvert = ( char* ) & inFloat;
   char *returnFloat = ( char* ) & retVal;

   // swap the bytes into a temporary buffer
   returnFloat[0] = floatToConvert[3];
   returnFloat[1] = floatToConvert[2];
   returnFloat[2] = floatToConvert[1];
   returnFloat[3] = floatToConvert[0];

   return retVal;
}