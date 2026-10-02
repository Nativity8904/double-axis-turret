#include <Arduino.h>
#include <Servo.h>

#include "TurretController.h"

TurretController::TurretController(uint8_t tiltServoPin, uint8_t panServoPin, uint8_t laserPin) :
    tiltServoPin(tiltServoPin), panServoPin(panServoPin), laserPin(laserPin), tiltAngle(90), panAngle(90) {}

void TurretController::begin() {
    tiltServo.attach(tiltServoPin);
    panServo.attach(panServoPin);
    
    // Turns on laser
    pinMode(laserPin, OUTPUT);
    digitalWrite(laserPin, HIGH);
}

TurretController::~TurretController() {
    panServo.detach();
    tiltServo.detach();

    // Turns off laser
    digitalWrite(laserPin, LOW);
    pinMode(laserPin, INPUT);
}

void TurretController::update(float pitchDegree, float rollDegree) {
    // Constrains roll and pitch to be within [-90, 90]
    int constrainedPitch = constrain(static_cast<int>(pitchDegree), -90, 90);
    int constrainedRoll = constrain(static_cast<int>(rollDegree), -90, 90);

    // Projects contrained roll and pitch [-90, 90] onto a valid servo range [0, 180]
    tiltAngle = map(constrainedPitch, -90, 90, 180, 0);
    panAngle = map(constrainedRoll, -90, 90, 0, 180);

    tiltServo.write(tiltAngle);
    panServo.write(panAngle);
}

int TurretController::getTiltAngle() const {
    return tiltAngle;
}

int TurretController::getPanAngle() const {
    return panAngle;
}
