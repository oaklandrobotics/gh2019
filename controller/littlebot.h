#ifndef LITTLEBOT_H
#define LITTLEBOT_H

#define PIN_1     25
#define PIN_2     26
#define PIN_3     27

void little_init() {
  pinMode(PIN_1, OUTPUT);
  pinMode(PIN_2, OUTPUT);
  pinMode(PIN_3, OUTPUT);

  digitalWrite(PIN_1, LOW);
  digitalWrite(PIN_2, LOW);
  digitalWrite(PIN_3, LOW);

}

void little_drive(uint8_t states[]) {
  //digitalWrite(PIN_1E, HIGH);
  //digitalWrite(PIN_2E, HIGH);

  if (states[0] == 1) {
    digitalWrite(PIN_1, HIGH);
    digitalWrite(PIN_2, LOW);
    digitalWrite(PIN_3, LOW);
  } else if (states[1] == 1) {
    digitalWrite(PIN_1, LOW);
    digitalWrite(PIN_2, HIGH);
    digitalWrite(PIN_3, LOW);
  } else if (states[2] == 1) {
    digitalWrite(PIN_1, HIGH);
    digitalWrite(PIN_2, HIGH);
    digitalWrite(PIN_3, LOW);
  } else if (states[3] == 1) {
    digitalWrite(PIN_1, LOW);
    digitalWrite(PIN_2, LOW);
    digitalWrite(PIN_3, HIGH);
  } else {
    digitalWrite(PIN_1, LOW);
    digitalWrite(PIN_2, LOW);
    digitalWrite(PIN_3, HIGH);
  }


}


#endif
