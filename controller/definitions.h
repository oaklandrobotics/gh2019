#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define PIN_LED       2
#define PIN_BUTTON    26

#define WIFI_CHANNEL    1
#define ESP_ADDR        2

// SENDER and RECEIVER are arbitrary with ESP-NOW, this is solely for this example
//#define SENDER
#ifndef SENDER
#define RECEIVER
#endif

#endif
