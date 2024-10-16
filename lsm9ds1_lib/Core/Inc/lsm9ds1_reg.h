#ifndef INC_LSM9DS1_REG_H_
#define INC_LSM9DS1_REG_H_

#define LSM9DS1_AG_ADDR      0x6B
#define LSM9DS1_MAG_ADDR     0x1E

// Reserved -- 0x00 - 0x03
#define ACT_THS              0x04  // r/w
#define ACT_DUR              0x05  // r/w
#define INT_GEN_CFG_XL       0x06  // r/w
#define INT_GEN_THS_X_XL     0x07  // r/w
#define INT_GEN_THS_Y_XL     0x08  // r/w
#define INT_GEN_THS_Z_XL     0x09  // r/w
#define INT_GEN_DUR_XL       0x0A  // r/w
#define REFERENCE_G          0x0B  // r/w
#define INT1_CTRL            0x0C  // r/w
#define INT2_CTRL            0x0D  // r/w
// Reserved -- 0x0E
#define WHO_AM_I             0x0F  // r, Default: 0x68
#define CTRL_REG1_G          0x10  // r/w
#define CTRL_REG2_G          0x11  // r/w
#define CTRL_REG3_G          0x12  // r/w
#define ORIENT_CFG_G         0x13  // r/w
#define INT_GEN_SRC_G        0x14  // r, Output
#define OUT_TEMP_L           0x15  // r, Output
#define OUT_TEMP_H           0x16  // r, Output
#define STATUS_REG_A           0x17  // r, Output
#define OUT_X_L_G            0x18  // r, Output
#define OUT_X_H_G            0x19  // r, Output
#define OUT_Y_L_G            0x1A  // r, Output
#define OUT_Y_H_G            0x1B  // r, Output
#define OUT_Z_L_G            0x1C  // r, Output
#define OUT_Z_H_G            0x1D  // r, Output
#define CTRL_REG4            0x1E  // r/w, Default: 0x38
#define CTRL_REG5_XL         0x1F  // r/w, Default: 0x38
#define CTRL_REG6_XL         0x20  // r/w, Default: 0x00
#define CTRL_REG7_XL         0x21  // r/w, Default: 0x00
#define CTRL_REG8            0x22  // r/w, Default: 0x04
#define CTRL_REG9            0x23  // r/w, Default: 0x00
#define CTRL_REG10           0x24  // r/w, Default: 0x00
// Reserved -- 0x25
#define INT_GEN_SRC_XL       0x26  // r, Output
#define STATUS_REG_B         0x27  // r, Output
#define OUT_X_L_XL           0x28  // r, Output
#define OUT_X_H_XL           0x29  // r, Output
#define OUT_Y_L_XL           0x2A  // r, Output
#define OUT_Y_H_XL           0x2B  // r, Output
#define OUT_Z_L_XL           0x2C  // r, Output
#define OUT_Z_H_XL           0x2D  // r, Output
#define FIFO_CTRL            0x2E  // r/w, Default: 0x00
#define FIFO_SRC             0x2F  // r, Output
#define INT_GEN_CFG_G        0x30  // r/w, Default: 0x00
#define INT_GEN_THS_XH_G     0x31  // r/w, Default: 0x00
#define INT_GEN_THS_XL_G     0x32  // r/w, Default: 0x00
#define INT_GEN_THS_YH_G     0x33  // r/w, Default: 0x00
#define INT_GEN_THS_YL_G     0x34  // r/w, Default: 0x00
#define INT_GEN_THS_ZH_G     0x35  // r/w, Default: 0x00
#define INT_GEN_THS_ZL_G     0x36  // r/w, Default: 0x00
#define INT_GEN_DUR_G        0x37  // r/w, Default: 0x00
// Reserved -- 0x38 - 0x7F
// Reserved -- 0x00 - 0x04
#define OFFSET_X_REG_L_M     0x05  // r/w, Default: 0x00 (Offset to compensate environmental effects)
#define OFFSET_X_REG_H_M     0x06  // r/w, Default: 0x00
#define OFFSET_Y_REG_L_M     0x07  // r/w, Default: 0x00
#define OFFSET_Y_REG_H_M     0x08  // r/w, Default: 0x00
#define OFFSET_Z_REG_L_M     0x09  // r/w, Default: 0x00
#define OFFSET_Z_REG_H_M     0x0A  // r/w, Default: 0x00
// Reserved -- 0x0B - 0x0E
#define WHO_AM_I_M           0x0F  // r, Default: 0x3D (Magnetic sensor identification)
// Reserved -- 0x10 - 0x1F
#define CTRL_REG1_M          0x20  // r/w, Default: 0x10 (Magnetic control registers)
#define CTRL_REG2_M          0x21  // r/w, Default: 0x00
#define CTRL_REG3_M          0x22  // r/w, Default: 0x03
#define CTRL_REG4_M          0x23  // r/w, Default: 0x00
#define CTRL_REG5_M          0x24  // r/w, Default: 0x00
// Reserved -- 0x25 - 0x26
#define STATUS_REG_M         0x27  // r, Output (Magnetic sensor status)
#define OUT_X_L_M            0x28  // r, Output (Magnetic output registers)
#define OUT_X_H_M            0x29  // r, Output
#define OUT_Y_L_M            0x2A  // r, Output
#define OUT_Y_H_M            0x2B  // r, Output
#define OUT_Z_L_M            0x2C  // r, Output
#define OUT_Z_H_M            0x2D  // r, Output
// Reserved -- 0x2E - 0x2F
#define INT_CFG_M            0x30  // r/w, Default: 0x08 (Magnetic interrupt configuration)
#define INT_SRC_M            0x31  // r, Default: 0x00 (Magnetic interrupt status)
#define INT_THS_L_M          0x32  // r/w, Default: 0x00 (Magnetic interrupt threshold)
#define INT_THS_H_M          0x33  // r/w, Default: 0x00


#endif /* INC_LSM9DS1_REG_H_ */
