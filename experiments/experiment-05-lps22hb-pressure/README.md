# Experiment 05 – LPS22HB Pressure Sensor

## Aim

To interface the LPS22HB sensor via I2C and obtain pressure data for environmental monitoring.

## Hardware

STM32L475 IoT Discovery Board

## Software

STM32CubeMX
STM32CubeIDE
RealTerm

## Description

The LPS22HB is a digital pressure sensor used for measuring atmospheric pressure.
The sensor communicates with the STM32 microcontroller using the I2C protocol.

## Implementation

* Configure I2C1 communication.
* Include BSP drivers for LPS22HB.
* Read pressure values from the sensor.
* Transmit data to the serial terminal via UART.

## Result

Atmospheric pressure values are displayed on the serial terminal.

## Status

Completed
