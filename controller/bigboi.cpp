#include "bigboi.h"

void saberCom(uint16_t addr, uint8_t command, uint8_t data) {
  uint8_t chksum;
  chksum = (addr + command + data) & 0b01111111;
  Serial2.write(addr);
  Serial2.write(command);
  Serial2.write(data);
  Serial2.write(chksum);
}

void driveMotors(uint8_t states[]) {
  int xVel, yVel;
  xVel = 40 * (int)(states[3] - states[2]);
  yVel = 40 * (int)(states[0] - states[1]);

  int lVel, rVel;

  lVel = constrain(yVel + xVel, -127, 127);
  rVel = constrain(yVel - xVel, -127, 127);

  uint8_t lSpeed, rSpeed, lDir, rDir;
  
  if (lVel < 0) {
    lVel *= -1;
    lDir = M1_BACKWARD;
  } else {
    lDir = M1_FORWARD;
  }
  lSpeed = (uint8_t) lVel;
  
  if (rVel < 0) {
    rVel *= -1;
    rDir = M2_BACKWARD;
  } else {
    rDir = M2_FORWARD;
  }
  rSpeed = (uint8_t) rVel;

  saberCom(SABER_ADDR, lDir, lSpeed);
  saberCom(SABER_ADDR, rDir, rSpeed);

  Serial.print(lSpeed);
  Serial.print(" | ");
  Serial.println(rSpeed);
}
