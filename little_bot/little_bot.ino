#define PIN_1         3
#define PIN_2         4
#define PIN_1E        5

#define PIN_2E        6
#define PIN_3         7
#define PIN_4         8

#define IN_1          10
#define IN_2          12
#define IN_3          11

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_1, OUTPUT);
  pinMode(PIN_2, OUTPUT);
  pinMode(PIN_1E, OUTPUT);
  pinMode(PIN_2E, OUTPUT);
  pinMode(PIN_3, OUTPUT);
  pinMode(PIN_4, OUTPUT);

  pinMode(IN_1, INPUT);
  pinMode(IN_2, INPUT);
  pinMode(IN_3, INPUT);

  digitalWrite(PIN_1, LOW);
  digitalWrite(PIN_2, LOW);
  digitalWrite(PIN_1E, LOW);
  digitalWrite(PIN_2E, LOW);
  digitalWrite(PIN_3, LOW);
  digitalWrite(PIN_4, LOW);

  Serial.begin(9600);


}

void loop() {
  // put your main code here, to run repeatedly:
    int by = (digitalRead(IN_3) << 2) + (digitalRead(IN_2) << 1) + digitalRead(IN_1);
    switch (by) {
      case 1:
        digitalWrite(PIN_1, LOW);
        digitalWrite(PIN_2, HIGH);
        digitalWrite(PIN_3, LOW);
        digitalWrite(PIN_4, HIGH);
        break;
      case 2:
        digitalWrite(PIN_1, HIGH);
        digitalWrite(PIN_2, LOW);
        digitalWrite(PIN_3, HIGH);
        digitalWrite(PIN_4, LOW);
        break;
      case 3:
        digitalWrite(PIN_1, HIGH);
        digitalWrite(PIN_2, LOW);
        digitalWrite(PIN_3, LOW);
        digitalWrite(PIN_4, HIGH);
        break;
      case 4:
        digitalWrite(PIN_1, LOW);
        digitalWrite(PIN_2, HIGH);
        digitalWrite(PIN_3, HIGH);
        digitalWrite(PIN_4, LOW);
        break;
      case 5:
        digitalWrite(PIN_1, LOW);
        digitalWrite(PIN_2, LOW);
        digitalWrite(PIN_3, LOW);
        digitalWrite(PIN_4, LOW);
      /*default:
        digitalWrite(PIN_1, LOW);
        digitalWrite(PIN_2, LOW);
        digitalWrite(PIN_3, LOW);
        digitalWrite(PIN_4, LOW);
        break;
    }
    delay(100); */
    }
}
