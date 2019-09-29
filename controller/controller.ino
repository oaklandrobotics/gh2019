/*  Variable to maintain states of each input
    Index:
    0 - UP
    1 - DOWN
    2 - LEFT
    3 - RIGHT
    4 - A
    5 - B
    6 - SELECT
    7 - START
    8 - 0
    9 - "PAIR"ITY BIT

    If you need to use these in a cpp file, include the following line in your .h file and add it below the initialization.
    extern uint8_t states[10];
*/

uint8_t states[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t slave_sel = 0;
uint8_t master_sel = 8;
uint8_t pot_master = 8;

#include "definitions.h"
#include "now_net.h"

#ifdef MASTER
#include "Touch_Sensors.h"
#endif

#ifndef MASTER
  #if ESP_ADDR == 2
  #include "bigboi.h"
  #endif

  #if ESP_ADDR == 4
  #include "BL_Keyboard.h"
  #endif
  
#include "rfid_tag.h"
#endif

void setup() {
  //pinMode(PIN_BUTTON, INPUT);

#ifdef MASTER
  pinMode(PIN_LED, OUTPUT);
#endif

#ifndef MASTER
  Serial2.begin(9600, SERIAL_8N1, 16, 17);
  rfid_init();
  #if ESP_ADDR == 4
  keyboard_setup();
  #endif
#endif

  Serial.begin(115200);
  network_setup();


}

void loop() {
  // Need some delay for watchdog feeding in loop
  delay(50);

#ifdef MASTER
  if (slave_sel != 0) { // have a slave
    // Get values for states.
    //readCap(states);
    states[0] = !digitalRead(26);
    states[1] = !digitalRead(25);
    states[2] = !digitalRead(33);
    states[3] = !digitalRead(34);

    esp_now_msg_t msg;
    msg = create_msg(slave_sel, ESP_ADDR, states);
    send_msg(&msg);
  }

#endif

#ifndef MASTER
  // Pair Process
  while (master_sel == 8) {
    // No master, try to find one
    int newID = -1;
    while (newID == -1) {
      newID = rfid_search();
    }

    pot_master = (uint8_t) newID;
    // Potential master, send request
    esp_now_msg_t msg;
    msg = create_msg(ESP_ADDR, pot_master, states);
    // If something goes wrong, fix line below.
    delay(500);
    
  }

  
  // Input processing

#endif


}
