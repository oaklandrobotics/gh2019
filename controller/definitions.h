#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define MASTER
#ifndef MASTER
#define SLAVE
#endif

#ifdef MASTER
#define PIN_LED     16
#endif

#ifndef MASTER

#endif

// INCLUDE AN ARRAY OF PIN VALUES FOR TOUCH -- MAKES THINGS WAY EASIER

#define WIFI_CHANNEL    1

/*  Address Table
 *  0 - Controller #1
 *  1 - Controller #2
 *  2 - Big Boi
 *  3 - Little Boi
 *  4 - Keyboard
 *  8 - No Master Flag
 */
#define ESP_ADDR        0



#endif
