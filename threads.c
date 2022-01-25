//  Thread Functions
//  Dynamic Strain Sensor
//  Grady White
// 1/7/22

#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include "threads.h"
#include "utils.h"
#include "measurements.h"

void *quit_condition(void *arg)
{
    char detect[64];

    while(!exit_runtime) {
        scanf("%s", detect);
        if (strcmp(detect, "quit") ==  0) {
            exit_runtime = 1;
        }
    }

    pthread_exit(NULL);
}

void *time_measure(void *arg)
{
    Config *conf = (Config *)arg;
    int ret = 0;
    
    while(!exit_runtime) {
        CHECK((ret = full_measure()));
        usleep(1000000*(conf->MEASURE_INTERVAL));
    }

exit:
    pthread_exit(NULL);
}

void *find_peak(void *arg)
{
    PEAK *input = (PEAK *)arg;
    for (int i = 0; i < CURVE_SIZE*BIT_SIZE; i++) {
        if (input->data[i] > input->peak_threshold) {
            input->detected = 1;
            input->done = 1;
            break;
        }
    }
    input->done = 1;

    pthread_exit(NULL);
}