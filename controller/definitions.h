#ifndef DEFINITIONS_H
#define DEFINITIONS_H

// Sender - Master
// Receiver - Slave
//#define SENDER
#ifndef SENDER
#define RECEIVER
#endif

#ifdef SENDER
#define PIN_BUTTON1    26
#define PIN_BUTTON2    25
#define PIN_BUTTON3    33
#define PIN_BUTTON4    34
#endif

// INCLUDE AN ARRAY OF PIN VALUES FOR TOUCH -- MAKES THINGS WAY EASIER

#define WIFI_CHANNEL    1

/*  Address Table
 *  0 - Controller #1
 *  1 - Controller #2
 *  2 - Big Boi
 *  3 - Little Boi
 *  4 - Keyboard
 */
#define ESP_ADDR        2



#endif
