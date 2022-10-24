#include <LoRa.h> // Include LoRa.h library
#include <SPI.h> // Include SPI.h library

int packetSize; // Variable to handle the size of data transmitted

// Main setup function
void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("LoRa Receiver");
  Serial.println("+++++++++++");
    

  LoRa.setPins(PA4, PC13, PA1);
  while(!LoRa.begin(868E6)){
    Serial.println("LoRa Initialization failed!");
  }
  Serial.println("LoRa Initialization succeeded!");
}

// Main loop function
void loop() {
  packetSize = LoRa.parsePacket();
  if (packetSize) {
    Serial.print("Received packet : '");

    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }

    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
}