# Concepts:

## Moving average:

The moving average is intended to maintain constant measurement without varying the sample rate on peaks. The moving average acquires data and averages from the newest data point to some time in the past. The moving average is intended to give a good idea of strain magnitude over a time frame, and is thus good for trends and quite bad for spikes in activity.

## Time stamps:

Time stamps are relative to the beginning of program execution. Time is in format of Days-Minutes-Seconds and the calendar date of program execution is recorded.  

## Measurements: 
  
Measurements are constantly taken. The time domain magnitude of the signal is the most important and is measured with a rolling average. Several pre-defined thresholds are available to determine when measurements are saved. Temperature is measured through a thermocouple.

Measurements include:
- Time domain
- FFT
- Peak magnitude
- Time average
- Largest frequency component

## Data:

Measurements are saved in specific cases.  
### 1. **Large variation of moving average**

Variations in the moving average mean the average has met one of several threshold values that are pre-defined empirically. These values determine when vibrations of noticeable strength are occuring.  
    **Data recorded:**  
- FFT
- Average temperature
- Peak magnitude
- Average magnitude

### 2. **Fixed increment in time**

Data should be saved in cases of obvious vibration, but general behaviour is also important. Data is saved sporadically to ensure data is plentiful.  
    **Data recorded:**  
- FFT
- Average temperature
- Peak magnitude
- Average magnitude

### 3. **Large spikes:**

Data is recorded when large spikes in magnitude are detected. These are expected to be frequent and will have thresholds associated with them. This method is to ensure that the rolling average doesn't miss any important fluctuations.  
    **Data recorded:**  
- Average temperature
- Peak magnitude
- Average magnitude

# Code:

## main.c:

The purpose of the main function is to have an easy to access initialization to the program. In this file the serial device will be registered and configured. The runtime environment will also be initialized and given appropriate arguments.

## runtime.c:

The runtime environment in this function is responsible for dynamically acquiring and moving data.

### TODO:

#### *Config interpretation:*

Config file will include:
- Moving average thresholds
- Peak value thresholds
- Generic data gathering rate 

## file.c

Controls file operations. Functions in this file are entirely responsible for every read and write to files in this program.

## measurement.c

Controls data acquisition from the oscilloscope. Functions in this file are entirely responsible for control and operation of serial devices.

## serial.c

General functions for serial control. Uses windows serial functionality. A Linux build could easily be made for this program by replacing all instances of `HANDLE` with a file descriptor `int`. Linux implementation would also use a different serial controller available in the resources folder.

## GPIB_prof.c

Simple GPIB controls. There is only one profile named `def`, this is the default configuration. Other configurations can easily be added by creating a function that looks like `def` in this file and adding a case to the `GPIB_conf` function in `serial.c`. Finally the profile is selected in `main.c`.

## setup.c

This file controls the initial instrument setup and configuration including synchronization of the instrument with measurement threads as well as calibration and test or baseline measurements.

# Building

This program relies on C standard libraries and POSIX standard libraries. Any compiler that can use POSIX libraries will correctly compile this program. Releases are built using MinGW-x64 and gcc. Windows releases are statically linked to ensure that it is portable to any windows computer. Linux or POSIX builds do not need to be statically linked.

Single line Windows compilation:
```
gcc -pthread -static -o DynamicSensor.exe main.c file.c GPIB_prof.c measurement.c runtime.c serial.c
```

Single line Linux compilation:
```
gcc -pthread -o DynamicSensor main.c file.c GPIB_prof.c measurement.c runtime.c serial.c
```
