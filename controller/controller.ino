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


void setup() {
  //pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BUTTON1, INPUT);
  pinMode(PIN_BUTTON2, INPUT);
  pinMode(PIN_BUTTON3, INPUT);
  pinMode(PIN_BUTTON4, INPUT);
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
  

}
