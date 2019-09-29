#include <BleKeyboard.h>
#include "BL_Keyboard.h"
#include "Touch_Sensors.h"

BleKeyboard bleKeyboard;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(1000);
  Serial.println("Starting BLE work!");
  bleKeyboard.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

}
