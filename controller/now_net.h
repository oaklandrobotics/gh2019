#ifndef NOW_NET_H
#define NOW_NET_H

#include <WiFi.h>
#include <esp_now.h>
#include <stdint.h>
#include <string.h>

#include "definitions.h"

extern uint8_t states[10];
extern uint8_t slave_sel;
extern uint8_t master_sel;
extern uint8_t pot_master;

typedef struct __attribute__((packed)) esp_now_msg_t
{
  uint8_t addr_slave;
  uint8_t addr_master;
  uint16_t data;
  uint16_t chksum;
  
  // Can put lots of things here...
} esp_now_msg_t;

void handle_error(esp_err_t err);
void msg_recv_cb(const uint8_t *mac_addr, const uint8_t *data, int len);
void msg_send_cb(const uint8_t* mac, esp_now_send_status_t sendStatus);
void send_msg(esp_now_msg_t * msg);
uint16_t createData(uint8_t st[10]);
esp_now_msg_t create_msg(uint8_t addr_slave, uint8_t addr_master, uint8_t dat[]);
void network_setup();

#endif
