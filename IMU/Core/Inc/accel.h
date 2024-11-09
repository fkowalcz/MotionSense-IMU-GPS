#ifndef INC_ACCEL_H_
#define INC_ACCEL_H_

#include "lsm9ds1_lib.h"

extern float calibrationMatrix[3][3];
extern float bias[3];
extern float alpha;
extern float previousFilteredData[3];

void calibrateAccelerometer(IMU_t* imu);
void lowPassFilter(IMU_t* imu);

#endif /* INC_ACCEL_H_ */
