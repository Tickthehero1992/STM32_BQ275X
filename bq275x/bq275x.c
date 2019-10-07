/*
 * ba275x.c
 *
 *  Created on: 1 окт. 2019 г.
 *      Author: pc-pcмп
 */


#include "bq275x.h"
#include "i2c_stm32.h"
I2C_HandleTypeDef hi2c1;


uint8_t BQ275x_init(I2C_HandleTypeDef i2c, uint16_t battery_capacity) //+++
{


	MESSAGE_TO_BQ275X MESSAGE={(BQ275X_ADDRES>>8)&0xff,BQ275X_ADDRES&0xff,BQ275X_CNTL,0X00, 0X80};
	I2C_STM32_WRITE(i2c,&MESSAGE,5);
	I2C_STM32_WRITE(i2c,&MESSAGE,5);

	MESSAGE_TO_BQ275X MESSAGEA={(BQ275X_ADDRES>>8)&0xff,BQ275X_ADDRES&0xff,BQ275X_CNTL, BQ275X_CNTL_SET_CFGUPDATE, BQ275X_CNTL_SET_CFGUPDATE/256};
	I2C_STM32_WRITE(i2c,&MESSAGEA,5);

	for(uint8_t i=0; i<100 ;i++)
	{
		uint16_t Dat=BQ275x_data_information(i2c,BQ275X_FLAGS);
//		HAL_UART_Transmit(&huart1, (uint8_t*)"Waiting 1\r\n",17,1000);
		HAL_Delay(10);

		if(Dat&0x10)
		{
			HAL_UART_Transmit(&huart1, (uint8_t*)"xep\r\n",6,1000);
			break;
		}


	}
	uint16_t status=BQ275x_status_read(i2c, BQ275X_CNTL_SEALED);
	MESSAGE_TO_BQ275X MESSAGEB={(BQ275X_ADDRES>>8)&0xff,BQ275X_ADDRES&0xff,BQ275X_BLOCKDATACONTROL, 0x00};
	I2C_STM32_WRITE(i2c,&MESSAGEB,4);

	MESSAGE_TO_BQ275X MESSAGEC={(BQ275X_ADDRES>>8)&0xff,BQ275X_ADDRES&0xff,BQ275X_DATACLASS, 0x52};
	I2C_STM32_WRITE(i2c,&MESSAGEC,4);

	MESSAGE_TO_BQ275X MESSAGED={(BQ275X_ADDRES>>8)&0xff,BQ275X_ADDRES&0xff,BQ275X_DATABLOCK, 0x00};
	I2C_STM32_WRITE(i2c,&MESSAGED,4);

	/*uint8_t Chksum, OLD_DESCAP_MSB, OLD_DESCAP_LSB;
	if(HAL_I2C_Master_Transmit(&i2c,BQ275X_ADDRES,(uint8_t*)BLOCKDATACHKSM,1, 100)==HAL_OK)
		if(HAL_I2C_Master_Receive(&i2c, BQ275X_ADDRES+0x01,&Chksum,1, 100)!=HAL_OK)HAL_UART_Transmit(&huart1, (uint8_t*)"Error of read \r\n",17,1000);
	HAL_Delay(10);
	if(HAL_I2C_Master_Transmit(&i2c,BQ275X_ADDRES,(uint8_t*)0x4A,1, 100)==HAL_OK)
		if(HAL_I2C_Master_Receive(&i2c, BQ275X_ADDRES+0x01,&OLD_DESCAP_MSB, 1, 100)!=HAL_OK)HAL_UART_Transmit(&huart1, (uint8_t*)"Error of read 0x4a\r\n",17,1000);
	HAL_Delay(10);
	if(HAL_I2C_Master_Transmit(&i2c,BQ275X_ADDRES,(uint8_t*)0x4B,1, 100)==HAL_OK)
		if(HAL_I2C_Master_Receive(&i2c, BQ275X_ADDRES+0x01,&OLD_DESCAP_LSB, 1, 100)!=HAL_OK)HAL_UART_Transmit(&huart1, (uint8_t*)"Error of read 0x4b\r\n",17,1000);
	HAL_Delay(10);*/

	/*uint8_t Chksum=(uint8_t)(BQ275x_data_information(BLOCKDATACHKSM)/256);


	uint8_t OLD_DESCAP_MSB=(uint8_t)(BQ275x_data_information(0x4A)/256);
    HAL_Delay(10);

    uint8_t OLD_DESCAP_LSB=(uint8_t)(BQ275x_data_information(0x4B)/256);
	HAL_Delay(10);*/

	MESSAGE_TO_BQ275X MESSAGEX={(BQ275X_ADDRES>>8)&0xff,BQ275X_ADDRES&0xff,BQ275X_BLOCKDATACHKSM, 0x00};
	uint8_t Chksum=I2C_STM32_READ_EXTENDED(i2c,&MESSAGEX,1,3);
	HAL_Delay(10);

	MESSAGE_TO_BQ275X MESSAGEY={(BQ275X_ADDRES>>8)&0xff,BQ275X_ADDRES&0xff,0x4A, 0x00};
	uint8_t OLD_DESCAP_MSB=I2C_STM32_READ_EXTENDED(i2c,&MESSAGEY,1,3);
	HAL_Delay(10);

	MESSAGE_TO_BQ275X MESSAGEZ={(BQ275X_ADDRES>>8)&0xff,BQ275X_ADDRES&0xff,0x4B, 0x00};
	uint8_t OLD_DESCAP_LSB=I2C_STM32_READ_EXTENDED(i2c,&MESSAGEZ,1,3);
	HAL_Delay(10);

	MESSAGE_TO_BQ275X MESSAGEE={(BQ275X_ADDRES>>8)&0xff,BQ275X_ADDRES&0xff,0x4A, battery_capacity/256};
	I2C_STM32_WRITE(i2c,&MESSAGEE,4);

	MESSAGE_TO_BQ275X MESSAGEF={(BQ275X_ADDRES>>8)&0xff,BQ275X_ADDRES&0xff,0X4B, battery_capacity};
	I2C_STM32_WRITE(i2c,&MESSAGEF,4);

	uint8_t temp = (255-Chksum-OLD_DESCAP_MSB-OLD_DESCAP_LSB)%256;
	uint8_t NewCHK = 255 - (temp+ battery_capacity/256+battery_capacity%256)%256;

	MESSAGE_TO_BQ275X MESSAGEK={(BQ275X_ADDRES>>8)&0xff,BQ275X_ADDRES&0xff,BQ275X_BLOCKDATACHKSM,  NewCHK};
	I2C_STM32_WRITE(i2c,&MESSAGEK,4);

	MESSAGE_TO_BQ275X MESSAGEJ={(BQ275X_ADDRES>>8)&0xff,BQ275X_ADDRES&0xff,BQ275X_CNTL, 0X42, 0X00};
	I2C_STM32_WRITE(i2c,&MESSAGEJ,5);

	for(;;)
		{
			uint16_t Dat=BQ275x_data_information(i2c,BQ275X_FLAGS);
			HAL_UART_Transmit(&huart1, (uint8_t*)"Waiting 2\r\n",17,1000);
			if(Dat&&0x10)
			{
				break;
			}

		}

	MESSAGE_TO_BQ275X MESSAGEU={(BQ275X_ADDRES>>8)&0xff,BQ275X_ADDRES&0xff,BQ275X_CNTL, 0X20, 0X00};
	I2C_STM32_WRITE(i2c,&MESSAGEU,5);
}


uint16_t BQ275x_status_read(I2C_HandleTypeDef i2c,CNTRL_BQ275X CNTL_STATUS_TO_OUT)
{
	uint16_t Data=0;
	MESSAGE_TO_BQ275X MESSAGE={(BQ275X_ADDRES>>8)&0xff,BQ275X_ADDRES&0xff,BQ275X_CNTL, CNTL_STATUS_TO_OUT, CNTL_STATUS_TO_OUT/256};
	Data=I2C_STM32_READ(i2c,&MESSAGE,2,5);
	//HAL_UART_Transmit(&huart1, (uint8_t*)&Data,4,1000);
	return Data;
}

uint16_t BQ275x_data_information(I2C_HandleTypeDef i2c, COMMAND_BQ275X COMMAND_NAME)
{
	uint16_t Data=0;
	if(COMMAND_NAME==BQ275X_CNTL)
	{
		Data=BQ275x_status_read(i2c, BQ275X_CNTL_CONTROL_STATUS);
	}
	else
	{

		MESSAGE_TO_BQ275X MESSAGE={(BQ275X_ADDRES>>8)&0xff,BQ275X_ADDRES&0xff,COMMAND_NAME, 0x00, 0x00};
		Data=I2C_STM32_READ_EXTENDED(i2c,&MESSAGE,2,3);
	}
	return Data;
}
