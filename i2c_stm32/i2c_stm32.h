#ifndef I2C_STM32_H_
#define I2C_STM32_H_

#include "main.h"

void I2C_STM32_FIND_DEVICES(I2C_HandleTypeDef);
void I2C_STM32_WRITE(I2C_HandleTypeDef,uint8_t*, uint8_t);
uint16_t I2C_STM32_READ(I2C_HandleTypeDef,uint8_t [], uint8_t,  uint8_t );
uint16_t I2C_STM32_READ_EXTENDED(I2C_HandleTypeDef,uint8_t [] , uint8_t, uint8_t );
#endif
