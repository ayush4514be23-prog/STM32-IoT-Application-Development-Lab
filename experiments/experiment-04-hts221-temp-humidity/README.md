# Experiment 04 – HTS221 Temperature and Humidity Sensor

## Aim

To interface the HTS221 sensor via I2C and acquire temperature and humidity measurements.

## Hardware

STM32L475 IoT Discovery Board

## Software

STM32CubeMX
STM32CubeIDE
RealTerm

## Description

The HTS221 sensor is used to measure environmental temperature and humidity.
Communication between the STM32 microcontroller and the sensor is performed using the I2C protocol.

## Implementation

* Configure I2C1 in STM32CubeMX.
* Include BSP drivers for HTS221 sensor.
* Read temperature and humidity values from the sensor.
* Transmit sensor readings through UART.

## Result

Temperature and humidity values are successfully displayed on the serial terminal.

## Status

Completed
