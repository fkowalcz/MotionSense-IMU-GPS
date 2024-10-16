#include "lsm9ds1_lib.h"

uint8_t LSM9DS1_Init_AccelGyro(I2C_HandleTypeDef *I2Cx)
{
    uint8_t check;
    uint8_t Data;

    // Odczytujemy rejestr WHO_AM_I dla akcelerometru/żyroskopu
    HAL_I2C_Mem_Read(I2Cx, LSM9DS1_AG_ADDR, WHO_AM_I, 1, &check, 1, 50);

    if (check == 0x68) // 0x68 jest wartością WHO_AM_I dla akcelerometru/żyroskopu
    {
        // Wyłączamy tryb oszczędzania energii - rejestr CTRL_REG6_XL
        // Konfigurujemy akcelerometr - rejestr CTRL_REG6_XL
        Data = 0x60; // 119 Hz, ±2g, BW default
        HAL_I2C_Mem_Write(I2Cx, LSM9DS1_AG_ADDR, CTRL_REG6_XL, 1, &Data, 1, 50);

        // Konfigurujemy żyroskop - rejestr CTRL_REG1_G
        Data = 0x60; // 119 Hz, ±245 dps, BW 14Hz
        HAL_I2C_Mem_Write(I2Cx, LSM9DS1_AG_ADDR, CTRL_REG1_G, 1, &Data, 1, 50);

        return 0; // Zwracamy 0, jeśli inicjalizacja zakończyła się sukcesem
    }
    return check; // Zwracamy 1, jeśli inicjalizacja nie powiodła się
}

uint8_t LSM9DS1_Init_Mag(I2C_HandleTypeDef *I2Cx)
{
    uint8_t check;
    uint8_t Data;

    // Odczytujemy rejestr WHO_AM_I dla magnetometru
    HAL_I2C_Mem_Read(I2Cx, LSM9DS1_MAG_ADDR, WHO_AM_I_M, 1, &check, 1, 50);

    if (check == 0x3D) // 0x3D jest wartością WHO_AM_I dla magnetometru
    {
        // Konfigurujemy magnetometr - rejestr CTRL_REG1_M
        Data = 0b00111100; // 10 Hz, Medium-performance, ustawienie temperatury off
        HAL_I2C_Mem_Write(I2Cx, LSM9DS1_MAG_ADDR, CTRL_REG1_M, 1, &Data, 1, 50);

        // Konfigurujemy zakres magnetometru - rejestr CTRL_REG2_M
        Data = 0b00000000; // ±4 gauss (default)
        HAL_I2C_Mem_Write(I2Cx, LSM9DS1_MAG_ADDR, CTRL_REG2_M, 1, &Data, 1, 50);

        // Konfigurujemy tryb działania magnetometru - rejestr CTRL_REG3_M
        Data = 0b00000000; // Continuous-conversion mode
        HAL_I2C_Mem_Write(I2Cx, LSM9DS1_MAG_ADDR, CTRL_REG3_M, 1, &Data, 1, 50);

        // Konfigurujemy wydajność magnetometru na osi Z - rejestr CTRL_REG4_M
        Data = 0b00000000; // Medium-performance mode on Z-axis
        HAL_I2C_Mem_Write(I2Cx, LSM9DS1_MAG_ADDR, CTRL_REG4_M, 1, &Data, 1, 50);

        return 0; // Zwracamy 0, jeśli inicjalizacja zakończyła się sukcesem
    }
    return 1; // Zwracamy 1, jeśli inicjalizacja nie powiodła się
}



void LSM9DS1_Read_Accel(I2C_HandleTypeDef *I2Cx, IMU_t *DataStruct)
{
    uint8_t Rec_Data[6];

    // Read 6 BYTES of data starting from GYRO_XOUT_H register

    HAL_I2C_Mem_Read(I2Cx, LSM9DS1_AG_ADDR, OUT_X_L_XL, 1, Rec_Data, 6, 50);

    DataStruct->Accel_X_RAW = (int16_t)(Rec_Data[1] << 8 | Rec_Data[0]);
    DataStruct->Accel_Y_RAW = (int16_t)(Rec_Data[3] << 8 | Rec_Data[2]);
    DataStruct->Accel_Z_RAW = (int16_t)(Rec_Data[5] << 8 | Rec_Data[4]);

    // Read 6 BYTES of data starting from ACCEL_XOUT_H register
}

void LSM9DS1_Read_Gyro(I2C_HandleTypeDef *I2Cx, IMU_t *DataStruct)
{
    uint8_t Rec_Data[6];

    // Read 6 BYTES of data starting from GYRO_XOUT_H register

    HAL_I2C_Mem_Read(I2Cx, LSM9DS1_AG_ADDR, OUT_X_L_G, 1, Rec_Data, 6, 50);

    DataStruct->Gyro_X_RAW = (int16_t)(Rec_Data[1] << 8 | Rec_Data[0]);
    DataStruct->Gyro_Y_RAW = (int16_t)(Rec_Data[3] << 8 | Rec_Data[2]);
    DataStruct->Gyro_Z_RAW = (int16_t)(Rec_Data[5] << 8 | Rec_Data[4]);
}

void LSM9DS1_Read_Mag(I2C_HandleTypeDef *I2Cx, IMU_t *DataStruct)
{
    uint8_t Rec_Data[6];

    // Read 6 BYTES of data starting from GYRO_XOUT_H register

    HAL_I2C_Mem_Read(I2Cx, LSM9DS1_AG_ADDR, OUT_X_L_M, 1, Rec_Data, 6, 50);

    DataStruct->Mag_X_RAW = (int16_t)(Rec_Data[1] << 8 | Rec_Data[0]);
    DataStruct->Mag_Y_RAW = (int16_t)(Rec_Data[3] << 8 | Rec_Data[2]);
    DataStruct->Mag_Z_RAW = (int16_t)(Rec_Data[5] << 8 | Rec_Data[4]);
}

void Normalize_Accel_Values(IMU_t *Raw_Values){
    //Scale values
	Raw_Values-> Accel_X = Raw_Values-> Accel_X_RAW*((2*G)/32768); //Values for AFS_SEL = 0
	Raw_Values-> Accel_Y = Raw_Values-> Accel_Y_RAW*((2*G)/32768);
	Raw_Values-> Accel_Z = Raw_Values-> Accel_Z_RAW*((2*G)/32768);
};

void Normalize_Gyro_Values(IMU_t *Raw_Values){
    //Scale values
	Raw_Values-> Gyro_X = Raw_Values-> Gyro_X_RAW/245.0; //Values for FS_SEL = 0
	Raw_Values-> Gyro_Y = Raw_Values-> Gyro_Y_RAW/245.0;
	Raw_Values-> Gyro_Z = Raw_Values-> Gyro_Z_RAW/245.0;
};

void Normalize_Mag_Values(IMU_t *Raw_Values){
    //Scale values
	Raw_Values-> Mag_X = Raw_Values-> Mag_X_RAW/4.0; //Values for FS_SEL = 0
	Raw_Values-> Mag_Y = Raw_Values-> Mag_Y_RAW/4.0;
	Raw_Values-> Mag_Z = Raw_Values-> Mag_Z_RAW/4.0;
};








