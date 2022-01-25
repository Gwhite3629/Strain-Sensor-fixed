//  Utility Header
//  Dynamic Strain Sensor
//  Grady White
//  1/7/22

#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdbool.h>
#include <string.h>
#include <errno.h>

//  CONSTANTS

// Setup 
#define CURVE_SIZE 2500

// Waveform
#define BIT_SIZE 1

// Incoming header size
//#define HEADER 

//  Measurement types
#define GENERIC_MEASUREMENT 0
#define PEAK_MEASUREMENT 1
#define MOVING_AVERAGE_MEASUREMENT 2

//  Return codes
#define FAULT -1

//  Error messages
#define MEM_ERROR "memory error"
#define FILE_ERROR "file error"

// TYPES

#define uint unsigned int

//  Moving average data
typedef struct AVERAGE_DATA{
    float AVERAGE_THRESHOLDS[6];
    uint WINDOW_SIZE;
} AVERAGE_DATA;

//  Config data
typedef struct Config {
    AVERAGE_DATA AVERAGE_DATA;
    float PEAK_THRESHOLD;
    uint SAMPLE_FREQUENCY;
    uint MEASURE_INTERVAL;
} Config;

//  Struct for peak comparison
typedef struct PEAK{
    float data[2500];
    float peak_threshold;
    bool detected;
    bool done;
} PEAK;

//  MACROS

//  Memory or file check
#define VALID(check, code) \
    if (check == NULL) { \
        fprintf(stderr, "%s: %s\n", code, strerror(errno)); \
        perror(code); \
        ret = FAULT; \
        goto exit; \
    }

#define HANDLE_ERR(check, code) \
    if (check != 0) { \
        fprintf(stderr, "%s: %s\n", code, strerror(errno)); \
        perror(code); \
        goto exit; \
    }

//  Memory alloc, checking, and allignment
#define MEM(ptr, size, type) \
    ptr = malloc(size*sizeof(type)); \
    VALID(ptr, MEM_ERROR); \
    memset(ptr, 0, size);

//  Return condition check
#define CHECK(ret) \
    if (ret < 0) \
        goto exit;

//  FUNCTIONS

float average();

//  Moving average
float moving_average(float *window, // Active data window
                     int windowSize, // Size of window
                     float *sum, // Sum of current window
                     int pos, // Position in window
                     float next); // Next number from main data

float ReverseFloat(const float inFloat);

#endif //_UTILS_H_
