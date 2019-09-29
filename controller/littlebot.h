#ifndef LITTLEBOT_H
#define LITTLEBOT_H

#define PIN_1         33
#define PIN_2         25
#define PIN_1E        26

#define PIN_2E        27
#define PIN_3         14
#define PIN_4         12

void little_init() {
  pinMode(PIN_1, OUTPUT);
  pinMode(PIN_2, OUTPUT);
  pinMode(PIN_1E, OUTPUT);
  pinMode(PIN_2E, OUTPUT);
  pinMode(PIN_3, OUTPUT);
  pinMode(PIN_4, OUTPUT);

  digitalWrite(PIN_1, LOW);
  digitalWrite(PIN_2, LOW);
  digitalWrite(PIN_1E, LOW);
  digitalWrite(PIN_2E, LOW);
  digitalWrite(PIN_3, LOW);
  digitalWrite(PIN_4, LOW);

}

void little_drive(uint8_t states[]) {
  //digitalWrite(PIN_1E, HIGH);
  //digitalWrite(PIN_2E, HIGH);

  int xVel, yVel;
  xVel = states[3] - states[2];
  yVel = states[0] - states[1];

  if (yVel == 1) {
    if (xVel == 0) {
      digitalWrite(PIN_1, HIGH);
      digitalWrite(PIN_2, LOW);
      digitalWrite(PIN_3, HIGH);
      digitalWrite(PIN_4, LOW);
    } else if (xVel == 1) {
      digitalWrite(PIN_1, HIGH);
      digitalWrite(PIN_2, LOW);
      digitalWrite(PIN_3, LOW);
      digitalWrite(PIN_4, HIGH);
    } else if (xVel == -1) {
      digitalWrite(PIN_1, LOW);
      digitalWrite(PIN_2, HIGH);
      digitalWrite(PIN_3, HIGH);
      digitalWrite(PIN_4, LOW);
    }
  } else if (yVel == -1) {
    if (xVel == 0) {
      digitalWrite(PIN_1, LOW);
      digitalWrite(PIN_2, HIGH);
      digitalWrite(PIN_3, LOW);
      digitalWrite(PIN_4, HIGH);
    } else if (xVel == 1) {
      digitalWrite(PIN_1, LOW);
      digitalWrite(PIN_2, HIGH);
      digitalWrite(PIN_3, HIGH);
      digitalWrite(PIN_4, LOW);
    } else if (xVel == -1) {
      digitalWrite(PIN_1, HIGH);
      digitalWrite(PIN_2, LOW);
      digitalWrite(PIN_3, LOW);
      digitalWrite(PIN_4, HIGH);
    } else if (yVel == 0) {
      if (xVel == 1) {
        digitalWrite(PIN_1, LOW);
        digitalWrite(PIN_2, HIGH);
        digitalWrite(PIN_3, LOW);
        digitalWrite(PIN_4, HIGH);
      } else if (xVel == -1) {
        digitalWrite(PIN_1, HIGH);
        digitalWrite(PIN_2, LOW);
        digitalWrite(PIN_3, LOW);
        digitalWrite(PIN_4, HIGH);
      } else if (xVel == 0) {
        digitalWrite(PIN_1, LOW);
        digitalWrite(PIN_2, LOW);
        digitalWrite(PIN_3, LOW);
        digitalWrite(PIN_4, LOW);
      }
    }
  }

}
#endif
