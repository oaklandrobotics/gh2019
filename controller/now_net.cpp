#include "now_net.h"

static uint8_t broadcast_mac[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

void handle_error(esp_err_t err)
{
  switch (err)
  {
    case ESP_ERR_ESPNOW_NOT_INIT:
      Serial.println("Not init");
      break;

    case ESP_ERR_ESPNOW_ARG:
      Serial.println("Argument invalid");
      break;

    case ESP_ERR_ESPNOW_INTERNAL:
      Serial.println("Internal error");
      break;

    case ESP_ERR_ESPNOW_NO_MEM:
      Serial.println("Out of memory");
      break;

    case ESP_ERR_ESPNOW_NOT_FOUND:
      Serial.println("Peer is not found");
      break;

    case ESP_ERR_ESPNOW_IF:
      Serial.println("Current WiFi interface doesn't match that of peer");
      break;

    default:
      break;
  }
}

void msg_recv_cb(const uint8_t *mac_addr, const uint8_t *data, int len)
{
  if (len == sizeof(esp_now_msg_t))
  {
    esp_now_msg_t msg;
    memcpy(&msg, data, len);

#ifdef MASTER
    if (slave_sel == 0) { // Not paired
      if (msg.addr_master == ESP_ADDR) {
        slave_sel = msg.addr_slave;
        states[9] = 1;

        // Send acceptance
        esp_now_msg_t msg = create_msg(slave_sel, ESP_ADDR, states);
        for (int i = 0; i < 1; i++) {
          send_msg(&msg);
        }

      }
    }

#endif

#ifndef MASTER
    if (msg.addr_slave == ESP_ADDR) {
      if (msg.addr_master == pot_master && master_sel == 8) {
        // Cool, pair devices
        master_sel = pot_master;
      }
      if (msg.addr_master == master_sel) {

        Serial.print(msg.addr_slave);
        Serial.print(" | ");
        Serial.print(msg.addr_master);
        Serial.print(" | ");
        Serial.print(msg.data);
        Serial.print(" | ");
        Serial.println(msg.chksum);
        // Not from itself, and intended for it.
        int datVal = (int) msg.data;
        for (int i = 9; i >= 0; i--) {
          int testVal = pow(2, i);
          if (datVal / testVal != 0) {
            datVal -= testVal;
            states[9 - i] = 1;
          } else {
            states[9 - i] = 0;
          }
          Serial.print(states[9 - i]);
          Serial.print(" | ");
        }
        Serial.println(" ");


        /* if (msg.data == 1) {
          digitalWrite(PIN_LED, HIGH);
          Serial.println("ON!");
          }
          else {
          digitalWrite(PIN_LED, LOW);
          Serial.println("OFF!");
          }

        */
      }
    }
#endif

  }
}

void msg_send_cb(const uint8_t* mac, esp_now_send_status_t sendStatus)
{

  switch (sendStatus)
  {
    case ESP_NOW_SEND_SUCCESS:
      Serial.println("Send success");
      break;

    case ESP_NOW_SEND_FAIL:
      Serial.println("Send Failure");
      break;

    default:
      break;
  }
}

void send_msg(esp_now_msg_t * msg)
{
  // Pack
  uint64_t packet_size = sizeof(esp_now_msg_t);
  uint8_t msg_data[packet_size];
  memcpy(&msg_data[0], msg, sizeof(esp_now_msg_t));

  esp_err_t status = esp_now_send(broadcast_mac, msg_data, packet_size);
  if (ESP_OK != status)
  {
    //Serial.println("Error sending message");
    handle_error(status);
  }
}

uint16_t createData(uint8_t st[]) {
  uint16_t dat = 0;
  for (int i = 0; i < 10; i++) {
    dat += (st[i] << (9 - i));
  }
  return dat;
}

esp_now_msg_t create_msg(uint8_t addr_slave, uint8_t addr_master, uint8_t dat[])
{
  esp_now_msg_t msg;
  msg.addr_slave = addr_slave;
  msg.addr_master = addr_master;
  msg.data = createData(dat);

  // Compute checksum
  uint16_t chkSum = (addr_slave << 8) + addr_master;
  chkSum = chkSum ^ msg.data;
  msg.chksum = chkSum;

  return msg;
}
void network_setup()
{
  //Puts ESP in STATION MODE
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  if (esp_now_init() != 0)
  {
    return;
  }

  esp_now_peer_info_t peer_info;
  peer_info.channel = WIFI_CHANNEL;
  memcpy(peer_info.peer_addr, broadcast_mac, 6);
  peer_info.ifidx = ESP_IF_WIFI_STA;
  peer_info.encrypt = false;
  esp_err_t status = esp_now_add_peer(&peer_info);
  if (ESP_OK != status)
  {
    Serial.println("Could not add peer");
    handle_error(status);
  }

  // Set up callback
  status = esp_now_register_recv_cb(msg_recv_cb);
  if (ESP_OK != status)
  {
    Serial.println("Could not register callback");
    handle_error(status);
  }

  status = esp_now_register_send_cb(msg_send_cb);
  if (ESP_OK != status)
  {
    Serial.println("Could not register send callback");
    handle_error(status);
  }

  Serial.println("Exit.");
}
