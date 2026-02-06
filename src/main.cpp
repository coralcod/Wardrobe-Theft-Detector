#include <Arduino.h>
#include <esp_now.h>
#include <math.h>
#include <WiFi.h>

// MAC address of Board 2 - The Indicator (Receiver)
uint8_t broadcastAddress[] ={0x34, 0x5F, 0x45, 0xE7, 0x58, 0x28};

// message structure, must match on receiver end
typedef struct
{
  float timeDuration;
} struct_message;

// create a message structure
struct_message myData;

esp_now_peer_info_t peerInfo;

// time variables
unsigned long startTime, endTime;
bool measured = false;

// function prototypes
void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
void switchStateChange();

void setup() {
  // Setup serial and Wi-Fi station
  Serial.begin(115200);
  WiFi.mode(WIFI_MODE_STA);
  Serial.print("\r\nMAC Address:\t");
  Serial.println(WiFi.macAddress());

  // initialise ESP-NOW
  if (esp_now_init() != ESP_OK){
    Serial.println("Error initialising ESP-NOW");
    return;
  }

  // register for send callback so we can tell if sent message was received OK
  esp_now_register_send_cb(onDataSent);

  // memcpy is simply copying MAC address into the "official" address that ESP-NOW uses
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }

  // interrupt for switch state change
  attachInterrupt(digitalPinToInterrupt(4), switchStateChange, CHANGE);
}

void loop() {
  // set data
  if (measured == true){
    myData.timeDuration = (endTime - startTime) / 1000.0;

    // send data
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

    // check data sent successfully
    if (result == ESP_OK){
      Serial.println("\nMessage sent");
    } else {
      Serial.println("Error sending message");
    }
    measured = false;
    delay(2000);
  }
}

void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Delivery status:  ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "SUCCESS" : "FAIL");
}

void switchStateChange(){
  // get either start or end time depending on switch state
  if (digitalRead(4) == HIGH){
    startTime = millis();
  } else {
    endTime = millis();
    measured = true;
  }
}