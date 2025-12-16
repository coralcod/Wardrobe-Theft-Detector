#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

// MAC address of Board 2
uint8_t broadcastAddress[] ={0x34, 0x5F, 0x45, 0xE7, 0x58, 0x28};

// message structure, must match on receiver end
typedef struct
{

} struct_message;

// create a message structure
struct_message myData;

esp_now_peer_info_t peerInfo;

// function prototypes
void onDataSent(const uint8_t, esp_now_send_status_t);

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_MODE_STA);
  Serial.println(WiFi.macAddress());
}

void loop() {
  
}

void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  // callback when data is sent??
}