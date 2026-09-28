#include <Arduino.h>
#include <Servo.h>

#include "TurretController.h"

TurretController::TurretController(uint8_t tiltServoPin, uint8_t panServoPin, uint8_t laserPin) :
    tiltServoPin(tiltServoPin), panServoPin(panServoPin), laserPin(laserPin), tilt(90), pan(90) {}

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
    tilt = map(constrainedPitch, -90, 90, 180, 0);
    pan = map(constrainedRoll, -90, 90, 0, 180);

    tiltServo.write(tilt);
    panServo.write(pan);
}

int TurretController::getTilt() const {
    return tilt;
}

int TurretController::getPan() const {
    return pan;
}
