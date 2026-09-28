#include <Arduino.h>
#include <Wire.h>

#include "Mpu6050.h"
#include "TurretController.h"
#include "Stats.h"

constexpr uint32_t BAUD_RATE = 115200;
constexpr uint32_t BUS_CLOCK = 400000;

constexpr uint8_t MPU_ADDR = 0x68;

constexpr uint8_t TILT_SERVO = 9;
constexpr uint8_t PAN_SERVO = 10;
constexpr uint8_t LASER = 11;

Mpu6050 mpu{MPU_ADDR};
TurretController turret{TILT_SERVO, PAN_SERVO, LASER};
Stats<uint8_t> rawAccelXStats{};

void setup() {
    Serial.begin(BAUD_RATE);
    delay(100);

    Wire.begin();
    Wire.setClock(BUS_CLOCK);

    mpu.begin();
    turret.begin();

    delay(100);
}

void loop() {
    mpu.update();

    float pitchDegree = mpu.getPitchDegree();
    float rollDegree = mpu.getRollDegree();

    turret.update(pitchDegree, rollDegree);

    // STATS
    rawAccelXStats.update(mpu.getRawAccelX());

    // F Keeps the string in flash memory
    Serial.print(F("AccelX mean: "));
    Serial.print(rawAccelXStats.getMean());
    Serial.print(F(" | "));
    Serial.print(F("AccelX std: "));
    Serial.print(rawAccelXStats.getStd());

    Serial.println();

    delay(50);
}
