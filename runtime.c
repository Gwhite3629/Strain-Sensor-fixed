//  Runtime Control
//  Dynamic Strain Sensor
//  Grady White
//  1/3/22

#include <stdbool.h>
#include <stdatomic.h>
#include <pthread.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

#include "measurements.h"
#include "file.h"
#include "threads.h"

int runtime(HANDLE dev)
{
    int ret = 0;
    int pos;
    int barrier = 0; // Current threshold
    PEAK input;

    float *window;
    float *current_acquisition = NULL;

    float sum = 0;
    float current_mag;
    float avg;

    time_t start_time = 0;
    time_t end_time = 0;

    pthread_t exit_thr;
    pthread_t peak_thr;
    pthread_t time_thr;

    // Get config data
    Config *config;
    char name[64] = "DEFAULT";
    printf("Enter config name:\n");
    scanf("%s", name);
    get_config(config, name);

    HANDLE_ERR((ret = pthread_create(&exit_thr, NULL, &quit_condition, NULL)), "pthread_create");
    HANDLE_ERR((ret = pthread_create(&time_thr, NULL, &time_measure, NULL)), "pthread_create");

    // Setup window
    int pos_max = config->AVERAGE_DATA.WINDOW_SIZE;
    MEM(window, pos_max, float);
    MEM(current_acquisition, CURVE_SIZE*BIT_SIZE, float);

    // Main runtime loop
    while(!exit_runtime) {
        time(&start_time);
        // Get most recent strain
        CHECK((ret = get_curve(dev, &(input.data))));
        input.done = 0;
        input.detected = 0;
        input.peak_threshold = config->PEAK_THRESHOLD;
        HANDLE_ERR((ret = pthread_create(&peak_thr, NULL, &find_peak, &input)), "pthread_create");
        // Average the strain
        avg = average(window,config->AVERAGE_DATA.WINDOW_SIZE, &sum, pos, current_mag);

        pthread_join(peak_thr, NULL);
        if (input.detected) {
            CHECK((ret = part_measure()));
        }

        // Measurement conditions (non-timer)
        if (avg > config->AVERAGE_DATA.AVERAGE_THRESHOLDS[barrier]) {
            if (barrier < 5)
                barrier++;
            CHECK((ret = full_measure()));
        } else if (avg < config->AVERAGE_DATA.AVERAGE_THRESHOLDS[barrier-1]) {
            barrier--;
        }

        time(&end_time);

        usleep(1000000*(1/config->SAMPLE_FREQUENCY) - (int)difftime(start_time, end_time));
    }

exit:

    if (window)
        free(window);
    if (current_acquisition)
        free(current_acquisition);
    if (config)
        free(config);

    return ret;
}