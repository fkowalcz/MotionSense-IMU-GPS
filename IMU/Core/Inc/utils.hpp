#ifndef INC_UTILS_HPP_
#define INC_UTILS_HPP_

#include <string.h>

#include "lsm9ds1_lib.h"

void ftoa3(float value1, float value2, float value3, char* buffer, int bufferSize, int decimalDigits) {
    int wholePart1 = (int)value1;
    int fractionalPart1 = (int)((value1 - wholePart1) * pow(10, decimalDigits));
    int wholePart2 = (int)value2;
    int fractionalPart2 = (int)((value2 - wholePart2) * pow(10, decimalDigits));
    int wholePart3 = (int)value3;
    int fractionalPart3 = (int)((value3 - wholePart3) * pow(10, decimalDigits));


    // Check for negative values
    if (value1 < 0) {
        fractionalPart1 = -fractionalPart1;
    }
    if (value2 < 0) {
        fractionalPart2 = -fractionalPart2;
    }
    if (value3 < 0) {
        fractionalPart3 = -fractionalPart3;
    }

    snprintf(buffer, bufferSize, "%d.%0*d,%d.%0*d,%d.%0*d\n",
             wholePart1, decimalDigits, fractionalPart1,
             wholePart2, decimalDigits, fractionalPart2,
             wholePart3, decimalDigits, fractionalPart3);
}


void ftoaIMU(IMU_t *IMU, char *buffer, int bufferSize, int decimalDigits) {
    int wholePart[9];
    int fractionalPart[9];

    float values[9] = {IMU->Gyro_X, IMU->Gyro_Y, IMU->Gyro_Z,
                       IMU->Accel_X, IMU->Accel_Y, IMU->Accel_Z,
                       IMU->Mag_X, IMU->Mag_Y, IMU->Mag_Z};

    for (int i = 0; i < 9; i++) {
        wholePart[i] = (int)values[i];
        fractionalPart[i] = (int)(fabs(values[i] - wholePart[i]) * pow(10, decimalDigits));

        if (values[i] < 0) {
            wholePart[i] = -wholePart[i];
        }
    }

    snprintf(buffer, bufferSize,
             "%d.%0*d,%d.%0*d,%d.%0*d,%d.%0*d,%d.%0*d,%d.%0*d,%d.%0*d,%d.%0*d,%d.%0*d\n",
             wholePart[0], decimalDigits, fractionalPart[0],
             wholePart[1], decimalDigits, fractionalPart[1],
             wholePart[2], decimalDigits, fractionalPart[2],
             wholePart[3], decimalDigits, fractionalPart[3],
             wholePart[4], decimalDigits, fractionalPart[4],
             wholePart[5], decimalDigits, fractionalPart[5],
             wholePart[6], decimalDigits, fractionalPart[6],
             wholePart[7], decimalDigits, fractionalPart[7],
             wholePart[8], decimalDigits, fractionalPart[8]);
}

#endif /* INC_UTILS_HPP_ */
