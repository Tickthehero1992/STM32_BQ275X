/*
 * i2c_stm32.c
 *
 *  Created on: 1 окт. 2019 г.
 *      Author: pc-pc
 */


#include "i2c_stm32.h"

void I2C_STM32_FIND_DEVICES(I2C_HandleTypeDef i2c)
{
	  uint8_t i = 0;
		  char exit[2];
		  for(i = 15; i<127; i++)
		  {
		      if(HAL_I2C_IsDeviceReady(&i2c, i<<1, 10, 100) == HAL_OK)
		      {
		    	 exit[0]=i/10+48;
		    	 exit[1]=i%10+48;
		    	 HAL_UART_Transmit(&huart1, (uint8_t*)&exit[0],1,100);
		    	 HAL_UART_Transmit(&huart1, (uint8_t*)&exit[1],1,100);
		    	 HAL_UART_Transmit(&huart1, (uint8_t*)&"\r\n",2,100);
		    	 //break;
		      }
		  }
		  HAL_UART_Transmit(&huart1, (uint8_t*)&"It all that i find\r\nFor using use address<<1\r\n",46,1000);
}

void I2C_STM32_WRITE(I2C_HandleTypeDef i2c,uint8_t* MESSAGE, uint8_t MESSAGE_SIZE)
{
	uint16_t address= (uint16_t)MESSAGE[0]*16+(uint16_t)MESSAGE[1];
	uint8_t number_of_bytes= MESSAGE_SIZE-2;
	uint8_t message[number_of_bytes];
	for(uint8_t i=0; i<number_of_bytes;i++)
	{
		message[i]=MESSAGE[i+2];
	}
	if(HAL_I2C_Master_Transmit(&i2c,address,(uint8_t*)&message,number_of_bytes, 100)!=HAL_OK)
		{
			HAL_UART_Transmit(&huart1, (uint8_t*)"Error of  write \r\n",17,1000);
		}
	/*if(HAL_I2C_Master_Transmit(&i2c,address,(uint8_t*)MESSAGE[2],1, 100)==HAL_OK)
	{



	}
	else HAL_UART_Transmit(&huart1, (uint8_t*)"Error of  write\r\n",17,1000);
	*/
}

uint16_t I2C_STM32_READ(I2C_HandleTypeDef i2c,uint8_t MESSAGE[], uint8_t NUMBER_OF_BYTES, uint8_t MESSAGE_SIZE)
{
	uint16_t address= (uint16_t)MESSAGE[0]+(uint16_t)MESSAGE[1];
	uint8_t number_of_bytes=MESSAGE_SIZE-2;
	uint8_t message[number_of_bytes];
	for(uint8_t i=0; i<number_of_bytes;i++)
	{
		message[i]=MESSAGE[i+2];
	}
	uint8_t Data[NUMBER_OF_BYTES];

	if(HAL_I2C_Master_Transmit(&i2c,address,(uint8_t*)&message,number_of_bytes, 100)==HAL_OK)
	{
		if(HAL_I2C_Master_Transmit(&i2c,address,(uint8_t*)message[0]+0x01,1, 100)==HAL_OK)
		{
		if(HAL_I2C_IsDeviceReady(&i2c,address,1,100)==HAL_OK)
			{
			if(HAL_I2C_Master_Receive(&i2c, address,&Data, NUMBER_OF_BYTES, 100)!=HAL_OK)HAL_UART_Transmit(&huart1, (uint8_t*)"Error of read\r\n",17,1000);
			}
		else HAL_UART_Transmit(&huart1, (uint8_t*)"Error of state\r\n",17,1000);
		}
		else HAL_UART_Transmit(&huart1, (uint8_t*)"Error of  write write\r\n",22,1000);
	}
	else HAL_UART_Transmit(&huart1, (uint8_t*)"Error of  write read\r\n",22,1000);
	uint16_t Data_out=Data[1]*256+Data[0];
	return Data_out;

}

uint16_t I2C_STM32_READ_EXTENDED(I2C_HandleTypeDef i2c,uint8_t MESSAGE[],uint8_t NUMBER_OF_BYTES, uint8_t MESSAGE_SIZE)
{
	uint16_t address= (uint16_t)MESSAGE[0]+(uint16_t)MESSAGE[1];
	uint8_t number_of_bytes=MESSAGE_SIZE-2;
	uint8_t message[number_of_bytes];
	for(uint8_t i=0; i<number_of_bytes;i++)
	{
		message[i]=MESSAGE[i+2];
	}
	uint8_t Data[2];
	Data[0]=0;
	Data[1]=0;
	if(HAL_I2C_Master_Transmit(&i2c,address,(uint8_t*)&message,number_of_bytes, 100)==HAL_OK)
	{

		if(HAL_I2C_IsDeviceReady(&i2c,address,1,100)==HAL_OK)
			{
			if(HAL_I2C_Master_Receive(&i2c, address,&Data, NUMBER_OF_BYTES, 100)!=HAL_OK)HAL_UART_Transmit(&huart1, (uint8_t*)"Error of read\r\n",17,1000);
			}
		else HAL_UART_Transmit(&huart1, (uint8_t*)"Error of state\r\n",17,1000);

	}
	else HAL_UART_Transmit(&huart1, (uint8_t*)"Error of  write read\r\n",22,1000);

	uint16_t Data_out=Data[1]*256+Data[0];
	return Data_out;
}

