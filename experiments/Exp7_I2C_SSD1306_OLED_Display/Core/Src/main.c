/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32l475e_iot01.h"
#include "stm32l475e_iot01_tsensor.h"
#include <stdio.h>
#include <string.h>

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;
UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
#define SLAVE_ADDRESS_LCD 0x4E   // 0x27 << 1
#define TEMP_THRESHOLD 28.0     // Temperature threshold set to 28°C

float temp_value = 0;
char uart_buffer[100];
char lcd_line1[20];
char lcd_line2[20];
uint8_t msg3[] = "=====> Temperature sensor HTS221 initialized \r\n ";
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART1_UART_Init(void);

/* USER CODE BEGIN 0 */
/* ================= LCD FUNCTIONS ================= */

void lcd_send_cmd(char cmd)
{
    char data_u, data_l;
    uint8_t data_t[4];

    data_u = (cmd & 0xf0);
    data_l = ((cmd << 4) & 0xf0);

    data_t[0] = data_u | 0x0C;
    data_t[1] = data_u | 0x08;
    data_t[2] = data_l | 0x0C;
    data_t[3] = data_l | 0x08;

    HAL_I2C_Master_Transmit(&hi2c1, SLAVE_ADDRESS_LCD, data_t, 4, 100);
    HAL_Delay(2);
}

void lcd_send_data(char data)
{
    char data_u, data_l;
    uint8_t data_t[4];

    data_u = (data & 0xf0);
    data_l = ((data << 4) & 0xf0);

    data_t[0] = data_u | 0x0D;
    data_t[1] = data_u | 0x09;
    data_t[2] = data_l | 0x0D;
    data_t[3] = data_l | 0x09;

    HAL_I2C_Master_Transmit(&hi2c1, SLAVE_ADDRESS_LCD, data_t, 4, 100);
    HAL_Delay(1);
}

void lcd_init(void)
{
    HAL_Delay(50);
    lcd_send_cmd(0x30);
    HAL_Delay(5);
    lcd_send_cmd(0x30);
    HAL_Delay(5);
    lcd_send_cmd(0x30);
    HAL_Delay(5);
    lcd_send_cmd(0x20);

    lcd_send_cmd(0x28);
    lcd_send_cmd(0x08);
    lcd_send_cmd(0x01);
    HAL_Delay(2);
    lcd_send_cmd(0x06);
    lcd_send_cmd(0x0C);
}

void lcd_set_cursor(uint8_t col, uint8_t row)
{
    uint8_t address = (row == 0) ? (0x80 + col) : (0xC0 + col);
    lcd_send_cmd(address);
}

void lcd_send_string(char *str)
{
    while (*str) lcd_send_data(*str++);
}
/* USER CODE END 0 */

int main(void)
{
  HAL_Init();
  SystemClock_Config();

  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();

  /* USER CODE BEGIN 2 */
  BSP_TSENSOR_Init();
  HAL_UART_Transmit(&huart1, msg3, sizeof(msg3), 1000);
  lcd_init();
  /* USER CODE END 2 */

  /* Infinite loop */
  while (1)
  {
      temp_value = BSP_TSENSOR_ReadTemp();

      /* Temperature Threshold Alert Logic */
      if(temp_value >= TEMP_THRESHOLD)
      {
          /* LED ON */
          HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);

          /* Buzzer ON */
          HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);

          snprintf(lcd_line2, sizeof(lcd_line2), "ALERT: HOT!");
      }
      else
      {
          /* LED OFF */
          HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);

          /* Buzzer OFF */
          HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);

          snprintf(lcd_line2, sizeof(lcd_line2), "Temp Normal");
      }

      /* UART Output */
      snprintf(uart_buffer, sizeof(uart_buffer),
               "Temp: %.2f C\r\n", temp_value);

      HAL_UART_Transmit(&huart1,
                        (uint8_t*)uart_buffer,
                        strlen(uart_buffer),
                        1000);

      /* LCD Line 1 */
      snprintf(lcd_line1, sizeof(lcd_line1),
               "Temp: %.2f C", temp_value);

      lcd_set_cursor(0,0);
      lcd_send_string("                ");
      lcd_set_cursor(0,0);
      lcd_send_string(lcd_line1);

      /* LCD Line 2 */
      lcd_set_cursor(0,1);
      lcd_send_string("                ");
      lcd_set_cursor(0,1);
      lcd_send_string(lcd_line2);

      HAL_Delay(500);
  }
}

/* ================= GPIO INIT ================= */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /* LED PB14 */
  GPIO_InitStruct.Pin = GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* Buzzer PB15 */
  GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* Button PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}
