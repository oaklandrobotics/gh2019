#ifndef _BL_Keyboard_
#define _BL_Keyboard_

#include <BleKeyboard.h>

BleKeyboard bleKeyboard;

void keyboard_setup() {
  bleKeyboard.begin();
}

void keyboard_msg(uint8_t keyb[10]) {
    if (keyb[0] > 0) {bleKeyboard.write(KEY_UP_ARROW);Serial.println("Up");} else {bleKeyboard.release(KEY_UP_ARROW);} 
    if (keyb[1] > 0) {bleKeyboard.write(KEY_DOWN_ARROW);Serial.println("Down");} else {bleKeyboard.release(KEY_DOWN_ARROW);}
    if (keyb[2] > 0) {bleKeyboard.write(KEY_LEFT_ARROW);Serial.println("Left");} else {bleKeyboard.release(KEY_LEFT_ARROW);}
    if (keyb[3] > 0) {bleKeyboard.write(KEY_RIGHT_ARROW);Serial.println("Right");} else {bleKeyboard.release(KEY_RIGHT_ARROW);}
    if (keyb[4] > 0) {bleKeyboard.write(KEY_RETURN);Serial.println("Enter");} else {bleKeyboard.release(KEY_RETURN);}
    if (keyb[5] > 0) {bleKeyboard.write(KEY_BACKSPACE);Serial.println("Backspace");} else {bleKeyboard.release(KEY_BACKSPACE);}
    if (keyb[6] > 0) {bleKeyboard.write(KEY_DELETE);Serial.println("Delete");} else {bleKeyboard.release(KEY_DELETE);}
    if (keyb[7] > 0) {bleKeyboard.write(KEY_ESC);Serial.println("Esc");} else {bleKeyboard.release(KEY_ESC);}
    if (keyb[8] > 0) {} else {}
    if (keyb[9] > 0) {} else {}
    delay(10);
}

bool keyboard_call(uint8_t out[10]) {
  if (bleKeyboard.isConnected()) {
    keyboard_msg(out);
  } else {
    
  }
}

#endif
