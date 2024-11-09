#include "accel.h"
#include "lsm9ds1_lib.h"

// Definicje zmiennych globalnych
float calibrationMatrix[3][3] = {
    {0.9997, 0.0036, -0.0129},
    {-0.0049, 1.0065, -0.0174},
    {-0.0112, 0.0061, 1.0039}
};

float bias[3] = {0.3255, 0.0559, 0.1460};
float alpha = 0.059117;

void calibrateAccelerometer(IMU_t* imu) {
    float tempData[3];
    tempData[0] = imu->Accel_X - bias[0];
    tempData[1] = imu->Accel_Y - bias[1];
    tempData[2] = imu->Accel_Z - bias[2];

    float correctedData[3] = {0, 0, 0};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            correctedData[i] += calibrationMatrix[i][j] * tempData[j];
        }
    }

    imu->Accel_X = correctedData[0];
    imu->Accel_Y = correctedData[1];
    imu->Accel_Z = correctedData[2];
}

void lowPassFilter(IMU_t* imu) {
    imu->filteredAccel_X = alpha * imu->Accel_X + (1 - alpha) * imu->filteredAccel_X;
    imu->filteredAccel_Y = alpha * imu->Accel_Y + (1 - alpha) * imu->filteredAccel_Y;
    imu->filteredAccel_Z = alpha * imu->Accel_Z + (1 - alpha) * imu->filteredAccel_Z;
}
