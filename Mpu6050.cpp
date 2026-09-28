#include "Mpu6050.h"

constexpr uint8_t PWR_MGMT_1 = 0x6B;
constexpr uint8_t ACCEL_CONFIG = 0x1C;
constexpr uint8_t ACCEL_XOUT_H = 0x3B;

Mpu6050::Mpu6050(uint8_t mpuAddr) : mpuAddr(mpuAddr), rawAccelBytes{}, rawAccel{0, 0, 0}, pitchDegree(0.0f), rollDegree(0.0f) {}

void Mpu6050::begin() {
    this->_write(PWR_MGMT_1, 0x00); // Wake MPU-6050 by clearing sleep bit
    this->_write(ACCEL_CONFIG, 0x00); // Set accelerometer to +-2g
}

void Mpu6050::_read(uint8_t registerAddr, uint8_t requestedLength, uint8_t output[]) {
    Wire.beginTransmission(mpuAddr);
    Wire.write(registerAddr);
    Wire.endTransmission(false);

    Wire.requestFrom(mpuAddr, requestedLength);

    for (uint8_t i = 0; i < requestedLength; i++) {
        output[i] = Wire.read();
    }
}

void Mpu6050::_write(uint8_t registerAddr, uint8_t input) {
    Wire.beginTransmission(mpuAddr);
    Wire.write(registerAddr);
    Wire.write(input);
    Wire.endTransmission(true);
}

void Mpu6050::update() {
    _read(ACCEL_XOUT_H, 6, rawAccelBytes);

    // Bitshift the hi-byte up so you can orsert the lo-byte
    rawAccel.x = static_cast<int16_t>((rawAccelBytes[0] << 8) | rawAccelBytes[1]);
    rawAccel.y = static_cast<int16_t>((rawAccelBytes[2] << 8) | rawAccelBytes[3]);
    rawAccel.z = static_cast<int16_t>((rawAccelBytes[4] << 8) | rawAccelBytes[5]);

    pitchDegree = atan2(rawAccel.y, sqrt(static_cast<float>(rawAccel.x) * rawAccel.x + 
                static_cast<float>(rawAccel.z) * rawAccel.z)) * (180.0f / PI);
    rollDegree = atan2(-rawAccel.x, rawAccel.z) * (180.0f / PI);
}

int16_t Mpu6050::getRawAccelX() const {
    return rawAccel.x;
}

int16_t Mpu6050::getRawAccelY() const {
    return rawAccel.y;
}

int16_t Mpu6050::getRawAccelZ() const {
    return rawAccel.z;
}

float Mpu6050::getPitchDegree() const {
    return pitchDegree;
}

float Mpu6050::getRollDegree() const {
    return rollDegree;
}
