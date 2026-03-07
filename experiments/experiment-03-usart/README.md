# Experiment 03 – USART Serial Communication

## Aim

To configure the USART peripheral for asynchronous serial transmission of text data to a terminal.

## Hardware

STM32L475 IoT Discovery Board

## Software

STM32CubeMX
STM32CubeIDE
RealTerm Serial Terminal

## Description

In this experiment, the USART peripheral of the STM32 microcontroller is configured for asynchronous communication.
The microcontroller continuously sends a text message to a serial terminal through USART1.

## Implementation

* USART1 is configured in asynchronous mode.
* PB6 is used as TX.
* PB7 is used as RX.
* Data is transmitted using the HAL UART transmit function.

### Example Code

```c
uint8_t Test[] = "Chitkara University !!!\r\n";
HAL_UART_Transmit(&huart1, Test, sizeof(Test), 10);
HAL_Delay(1000);
```

## Result

The message **"Chitkara University !!!"** is displayed repeatedly on the serial terminal.

## Status

Completed
