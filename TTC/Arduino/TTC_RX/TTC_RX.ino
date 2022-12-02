#include <RH_RF24.h>  // include Si446x.h library

#define Max_Packet_Size 128  // Maximum packet size @128
#define rf_receive A2
#define rf_transmit A3

uint8_t buf[Max_Packet_Size];
uint8_t len = sizeof(buf);
static uint8_t counter;   // Variable to count number of received data
static uint8_t invalids;  // Variable to count number of failed received data
static uint32_t tries;  // Variable to count number of tries received data


RH_RF24 rf4463(A4, A0, A1);  // Initialize RF4463 Object

// Main Setup function
void setup() {
  pinMode(rf_receive, OUTPUT);
  pinMode(rf_transmit, OUTPUT);

  digitalWrite(rf_receive, HIGH);
  digitalWrite(rf_transmit, LOW);

  Serial.begin(115200);

  if (!rf4463.init())
    Serial.println("Init Failed");
  Serial.println("Success");
}

// Main Loop function
void loop() {
  if (rf4463.recv(buf, &len)) {
    Serial.print("Tries : ");
    Serial.print(tries);
    Serial.print(" --> Received Message: ");
    Serial.println((char*)buf);
    counter++;
  } else {
    Serial.print("Tries : ");
    Serial.print(tries);
    Serial.println(" --> recv failed");
    invalids++;
  }
  tries++;
}