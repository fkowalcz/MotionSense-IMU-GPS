#ifndef INC_LSM9DS1_LIB_H_
#define INC_LSM9DS1_LIB_H_

#include <stdint.h>
#include <math.h>
#include <stdio.h>

#include "stm32l4xx_hal.h"
#include "i2c.h"

#include "lsm9ds1_reg.h"


#define G  9.81
#define RAD_TO_DEG 57.29

#define SUCCESS 0
#define ERROR_INIT 1
#define ERROR_WHO_AM_I 2



typedef struct
{
	int16_t Gyro_X_RAW;
    int16_t Gyro_Y_RAW;
    int16_t Gyro_Z_RAW;

    float Gyro_X;
    float Gyro_Y;
    float Gyro_Z;

    float filteredGyro_X;
    float filteredGyro_Y;
    float filteredGyro_Z;

	int16_t Accel_X_RAW;
    int16_t Accel_Y_RAW;
    int16_t Accel_Z_RAW;

    float Accel_X;
    float Accel_Y;
    float Accel_Z;

    float filteredAccel_X;
    float filteredAccel_Y;
    float filteredAccel_Z;

	int16_t Mag_X_RAW;
    int16_t Mag_Y_RAW;
    int16_t Mag_Z_RAW;

    float Mag_X;
    float Mag_Y;
    float Mag_Z;

    float filteredMag_X;
    float filteredMag_Y;
    float filteredMag_Z;

} IMU_t;

uint8_t LSM9DS1_Init_AccelGyro(I2C_HandleTypeDef *I2Cx);
uint8_t LSM9DS1_Init_Mag(I2C_HandleTypeDef *I2Cx);

//uint8_t LSM9DS1_Setup_Accel(I2C_HandleTypeDef *I2Cx, uint8_t ODR, uint8_t FS);
//uint8_t LSM9DS1_Setup_Gyro(I2C_HandleTypeDef *I2Cx, uint8_t ODR, uint8_t FS);

void LSM9DS1_Read_Accel(I2C_HandleTypeDef *I2Cx, IMU_t *DataStruct);
void LSM9DS1_Read_Gyro(I2C_HandleTypeDef *I2Cx, IMU_t *DataStruct);
void LSM9DS1_Read_Mag(I2C_HandleTypeDef *I2Cx, IMU_t *DataStruct);
void Normalize_Accel_Values(IMU_t *Raw_Values);
void Normalize_Gyro_Values(IMU_t *Raw_Values);
void Normalize_Mag_Values(IMU_t *Raw_Values);



#endif /* INC_LSM9DS1_LIB_H_ */
