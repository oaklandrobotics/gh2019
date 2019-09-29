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

#ifndef SENDER
    if (msg.addr_send != ESP_ADDR && msg.addr_recv == ESP_ADDR) {
      if (msg.data == 1) {
        digitalWrite(PIN_LED, HIGH);
        Serial.println("ON!");
      }
      else {
        digitalWrite(PIN_LED, LOW);
        Serial.println("OFF!");
      }

      Serial.print(msg.addr_recv);
      Serial.print(" | ");
      Serial.print(msg.addr_send);
      Serial.print(" | ");
      Serial.print(msg.data);
      Serial.print(" | ");
      Serial.println(msg.chksum);
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
    Serial.println("Error sending message");
    handle_error(status);
  }
}

esp_now_msg_t create_msg(uint8_t addr_recv, uint8_t addr_send, uint16_t data)
{
  esp_now_msg_t msg;
  msg.addr_recv = addr_recv;
  msg.addr_send = addr_send;
  msg.data = data;

  // Compute checksum
  uint16_t chkSum = (addr_recv << 8) + addr_send;
  chkSum = chkSum ^ data;
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
