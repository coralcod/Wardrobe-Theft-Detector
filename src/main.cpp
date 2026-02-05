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

/*
#include <Arduino.h>
#include <math.h>

unsigned long startTime;
unsigned long endTime;
float timeDuration;
bool measured;

void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, INPUT);
}

void loop() {
  int buttonState = digitalRead(3);

  while (buttonState == HIGH){
    digitalWrite(2, HIGH);
    if (measured == false){
      startTime = millis();
      measured = true;
    }
    buttonState = digitalRead(3);
  }

  if (measured ==  true){
    endTime = millis();
    timeDuration = endTime - startTime;
    timeDuration = timeDuration / 1000;
    Serial.print("Duration: ");
    Serial.print(timeDuration);
    Serial.println(" sec");
  }

  measured = false;
  digitalWrite(2, LOW); 
}
*/