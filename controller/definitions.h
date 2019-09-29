#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define PIN_LED         2
#define PIN_BUTTON1    26
#define PIN_BUTTON2    25
#define PIN_BUTTON3    33
#define PIN_BUTTON4    34

// INCLUDE AN ARRAY OF PIN VALUES FOR TOUCH -- MAKES THINGS WAY EASIER

#define WIFI_CHANNEL    1

/*  Address Table
 *  0 - Controller #1
 *  1 - Controller #2
 *  2 - Big Boi
 *  3 - Little Boi
 *  4 - Keyboard
 */
#define ESP_ADDR        1

// Sender - Master
// Receiver - Slave
#define SENDER
#ifndef SENDER
#define RECEIVER
#endif

#endif
