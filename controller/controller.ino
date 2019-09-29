#include "definitions.h"
#include <driver/gpio.h>
#include "now_net.h"

void setup() {
  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_LED, OUTPUT);
  

  Serial.begin(115200);
  network_setup();


}

void loop() {
  // Need some delay for watchdog feeding in loop
  delay(50);
  
  #ifdef SENDER
  int state = digitalRead(PIN_BUTTON);
  esp_now_msg_t msg;
  msg = create_msg(2, ESP_ADDR, state);
  send_msg(&msg);
  #endif
  

}
