//  Setup
//  Dynamic Strain Sensor
//  Grady White
//  1/5/22

#include <windows.h>
#include <stdio.h>

#include "utils.h"
#include "serial.h"

#define DIV "CH1:SCALE 100E-3\r"

int init(HANDLE fd)
{
    int ret = 0;

    CHECK((ret = write_port(fd, "CURSOR:SELect:SOUrce CH1\r", 25)));
    CHECK((ret = write_port(fd, "CH1:COUPLING DC\r", 16)));
    CHECK((ret = write_port(fd, DIV, 17)));
    CHECK((ret = write_port(fd, "HORIZONTAL:SCALE 2E-1\r", 22)));
    CHECK((ret = write_port(fd, "DATA:SOURCE CH1\r", 16)));
    CHECK((ret = write_port(fd, "DATA:START 1\r", 13)));
    CHECK((ret = write_port(fd, "DATA:STOP 2500\r", 15)));  
    CHECK((ret = write_port(fd, "DATA:WIDth 1\r", 13)));
    CHECK((ret = write_port(fd, "DATA:ENCDG SRIBINARY\r", 21)));
    CHECK((ret = write_port(fd, "HEADER OFF\r", 11)));
    CHECK((ret = write_port(fd, "ACQUIRE:STATE ON\r", 17)));

exit:
    return ret;
}