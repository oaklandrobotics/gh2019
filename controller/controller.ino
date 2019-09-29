/*  Variable to maintain states of each input
 *  Index:
 *  0 - UP
 *  1 - DOWN
 *  2 - LEFT
 *  3 - RIGHT
 *  4 - A
 *  5 - B
 *  6 - SELECT
 *  7 - START
 *  8 - 0
 *  9 - 0
 *  
 *  If you need to use these in a cpp file, include the following line in your .h file and add it below the initialization.
 *  extern uint8_t states[10];
 */
 
uint8_t states[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

#include "definitions.h"
//#include <driver/gpio.h>
#include "now_net.h"
#include "bigboi.h"


void setup() {
  //pinMode(PIN_BUTTON, INPUT);

  #ifdef SENDER
  pinMode(PIN_BUTTON1, INPUT);
  pinMode(PIN_BUTTON2, INPUT);
  pinMode(PIN_BUTTON3, INPUT);
  pinMode(PIN_BUTTON4, INPUT);
  #endif

  #ifndef SENDER
  Serial2.begin(9600, SERIAL_8N1, 16, 17);
  #endif
  
  Serial.begin(115200);
  network_setup();


}

void loop() {
  // Need some delay for watchdog feeding in loop
  delay(50);
  
  #ifdef SENDER
  // Get values for states.
  states[0] = !digitalRead(PIN_BUTTON1);
  states[1] = !digitalRead(PIN_BUTTON2);
  states[2] = !digitalRead(PIN_BUTTON3);
  states[3] = !digitalRead(PIN_BUTTON4);

  
  esp_now_msg_t msg;
  msg = create_msg(2, ESP_ADDR, states);
  send_msg(&msg);
  #endif

  #ifndef SENDER
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
  
  #endif
  

}
