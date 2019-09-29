#ifndef BIGBOI_H
#define BIGBOI_H

#include "Arduino.h"
// Sabertooth declarations
#define SABER_ADDR          130

// Commands
#define M1_FORWARD          0x00
#define M1_BACKWARD         0x01
#define SET_MIN_VOLTAGE     0x02
#define SET_MAX_VOLTAGE     0x03
#define M2_FORWARD          0x04
#define M2_BACKWARD         0x05
#define M1_7BIT             0x06
#define M2_7BIT             0x07
#define MIX_FORWARD         0x08
#define MIX_BACKWARD        0x09
#define MIX_RIGHT           0x0a
#define MIX_LEFT            0x0b
#define MIX_7BIT_DRIVE      0x0c
#define MIX_7BIT_TURN       0x0d
#define SET_SERIAL_TIMEOUT  0x0e
#define SET_BAUD_RATE       0x0f
#define SET_RAMPING         0x10
#define SET_DEADBAND        0x11

void saberCom(uint16_t addr, uint8_t command, uint8_t data);
void driveMotors(uint8_t states[]);

#endif
