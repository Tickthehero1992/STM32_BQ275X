STM32_BQ275X
This is the library to work STM32 with sensors BQ275X Texas Instruments. It was tested on BQ-27441-g1. 
Library contains:
uint8_t BQ275x_init(I2C_HandleTypeDef i2c_to_use, uint16_t CAPACITY) - initialization of sensor with capcaity of accumulator
uint16_t BQ275x_status_read(I2C_HandleTypeDef i2c_to_use ,CNTRL_BQ275X) - read status of sensor 
uint16_t BQ275x_data_information(I2C_HandleTypeDef i2c_to_use,COMMAND_BQ275X) - read data from sensor

Commands for data reading - COMMAND_BQ275X:
	BQ275X_CNTL,
	BQ275X_TEMP,
	BQ275X_VOLTAGE,
	BQ275X_FLAGS,
	BQ275X_NOMINALCAPACITY,
	BQ275X_FULLCAPACITY,
	BQ275X_REMAININGCAPACITY,
	BQ275X_FULLCHARGECAPACITY,
	BQ275X_AVERAGECURRENT,
	BQ275X_STANDBYCURRENT,
	BQ275X_MAXLOADCURRENT,
	BQ275X_AVERAGEPOWER,
	BQ275X_STATEOFCHARGE,
	BQ275X_INTERNALTEMPERATURE,
	BQ275X_STATEOFHEALTH,
	BQ275X_REMAININGCAPACITYUNFIL,
	BQ275X_REMAININCAPACITYFILTERED,
	BQ275X_FULLCHARGECAPACITYUN,
	BQ275X_FULLCHARGECAPACITYFIL,
	BQ275X_STATEOFCHARGEUNFILTERED,
	BQ275X_OPCONFIG ,
	BQ275X_DESIGNCAPACITY,
	BQ275X_DATACLASS,
	BQ275X_DATABLOCK,
	BQ275X_BLOCKDATA,
	BQ275X_BLOCKDATACHKSM,
	BQ275X_BLOCKDATACONTROL



Control status of sensor - CNTRL_BQ275X:
	BQ275X_CNTL_CONTROL_STATUS,
	BQ275X_CNTL_DEVICE_INFO,
	BQ275X_CNTL_FW_VERSION,
	BQ275X_CNTL_DM_CODE,
	BQ275X_CNTL_PROTECTOR_VERSION,
	BQ275X_CNTL_PREV_MACWRITE,
	BQ275X_CNTL_CHEM_ID,
	BQ275X_CNTL_BAT_INSERT,
	BQ275X_CNTL_BAT_REMOVE,
	BQ275X_CNTL_SET_HIBERNATE,
	BQ275X_CNTL_CLEAR_HIBERNATE,
	BQ275X_CNTL_SET_CFGUPDATE,
	BQ275X_CNTL_SHUTDOWN_ENABLE,
	BQ275X_CNTL_SHUTDOWN,
	BQ275X_CNTL_SEALED,
	BQ275X_CNTL_TOGGLE_GPOUT,
	BQ275X_CNTL_RESET_STAT,
	BQ275X_CNTL_SOFT_RESET,
	BQ275X_CNTL_EXIT_CFGUPDATE,
	BQ275X_CNTL_EXIT_RESIM

