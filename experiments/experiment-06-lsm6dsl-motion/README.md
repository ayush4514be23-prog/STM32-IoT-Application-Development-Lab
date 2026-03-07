# Experiment 06 – LSM6DSL Accelerometer and Gyroscope Sensor

## Aim

To configure communication and read three-axis acceleration data from the LSM6DSL motion sensor.

## Hardware

STM32L475 IoT Discovery Board

## Software

STM32CubeMX
STM32CubeIDE
RealTerm

## Description

The LSM6DSL is a combined accelerometer and gyroscope sensor integrated on the STM32 IoT Discovery board.
This experiment reads motion data from the sensor and transmits it through UART.

## Implementation

* Configure I2C communication.
* Include BSP drivers for LSM6DSL sensor.
* Read accelerometer and gyroscope values in X, Y, and Z directions.
* Send data to the serial terminal.

### Example Code

```c
BSP_ACCELERO_AccGetXYZ(accel_data);
BSP_GYRO_GetXYZ(gyro_data);
```

## Result

Acceleration and gyroscope readings are displayed on the serial terminal.

## Status

Completed
