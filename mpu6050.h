/* 
 * File:   mpu6050.h
 * Author: miyakoshi_macbookpro
 *
 * Created on May 13, 2022, 1:54 PM
 */

#ifndef MPU6050_H
#define	MPU6050_H

// MPU-6050のアドレス、レジスタ設定値
#define MPU6050_WHO_AM_I     0x75  // Read Only
#define MPU6050_PWR_MGMT_1   0x6B  // Read and Write
#define MPU_ADDRESS  0x68
#define MPU6050_ACCEL_XOUT_H     0x3B

void mpu6050_Initialize(void);
void getMpu6050Data(void);

#endif	/* MPU6050_H */