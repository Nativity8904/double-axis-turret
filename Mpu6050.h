#ifndef MPU6050_H
#define MPU6050_H

#include <math.h>
#include <Arduino.h>
#include <Wire.h>

struct RawAccel {
    int16_t x;
    int16_t y;
    int16_t z;
};

class Mpu6050 {
    uint8_t mpuAddr;

    uint8_t rawAccelBytes[6];
    RawAccel rawAccel;
    
    float pitchDegree;
    float rollDegree;

    void _read(uint8_t registerAddr, uint8_t requestedLength, uint8_t output[]);
    void _write(uint8_t registerAddr, uint8_t input);

public:
    Mpu6050(uint8_t mpuAddr);

    void begin();
    void update();

    int16_t getRawAccelX() const;
    int16_t getRawAccelY() const;
    int16_t getRawAccelZ() const;

    float getPitchDegree() const;
    float getRollDegree() const;
};

#endif // MPU6050_H
