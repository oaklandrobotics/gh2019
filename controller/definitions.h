#ifndef DEFINITIONS_H
#define DEFINITIONS_H

//#define MASTER
#ifndef MASTER
#define SLAVE
#endif

#ifdef MASTER
//#define PIN_LED     16
#endif

#ifndef MASTER

#endif


#define WIFI_CHANNEL    1

/*  Address Table
 *  0 - Controller #1
 *  1 - Controller #2
 *  2 - Big Boi
 *  3 - Little Boi
 *  4 - Keyboard
 *  5 - Littlist Boi
 *  8 - No Master Flag
 */
#define ESP_ADDR        5



#endif
