#ifndef TURRETCONTROLLER_H
#define TURRETCONTROLLER_H

#include <stdint.h>
#include <Servo.h>

class TurretController {
    uint8_t tiltServoPin;
    uint8_t panServoPin;
    uint8_t laserPin;

    Servo tiltServo;
    Servo panServo;

    int tilt;
    int pan;

public:
    TurretController(uint8_t tiltServoPin, uint8_t panServoPin, uint8_t laserPin);
    ~TurretController();

    void begin();
    void update(float pitchDegree, float rollDegree);

    int getTilt() const;
    int getPan() const;
};

#endif // TURRETCONTROLLER_H
