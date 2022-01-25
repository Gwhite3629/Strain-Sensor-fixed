//  File Control
//  Dynamic Strain Sensor
//  Grady White
//  1/3/22

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "utils.h"

int find_event(FILE *fd, fpos_t *prof_start, char *locator)
{
    uint ret = 0;
    int flag = 0;
    int found = 0;
    char *buffer = NULL;

    MEM(buffer, strlen(locator) + 1, char);

    buffer[strlen(locator)] = '\0';

    do {
        buffer[flag] = fgetc(fd);
        if (buffer[flag] == locator[flag]) {
            if (flag == strlen(locator) - 1)
                found++;
            else
                flag++;
        } else
            flag = 0;
    } while (found < 1);
    
exit:
    free(buffer);
    return ret;
}

int get_config(Config *config, char *name)
{
    uint ret = 0;

    FILE *config_file;
    fpos_t *config_start = NULL;

    MEM(config, sizeof(Config), FILE);

    MEM(config_start, sizeof(fpos_t), fpos_t);

    VALID((config_file = fopen("config.cfg", "r")), FILE_ERROR);

    find_event(config_file, config_start, name);

    fsetpos(config_file, config_start);

    for (int i = 0; i < 6; i++) {
        fscanf(config_file, "%f\n", &(config->AVERAGE_DATA.AVERAGE_THRESHOLDS[i]));
    }
    fscanf(config_file, "%u", &(config->AVERAGE_DATA.WINDOW_SIZE));
    fscanf(config_file, "%f", &(config->PEAK_THRESHOLD));
    fscanf(config_file, "%u", &(config->SAMPLE_FREQUENCY));
    fscanf(config_file, "%u", &(config->MEASURE_INTERVAL));

exit:
    free(config_start);
    fclose(config_file);
    return ret;
}