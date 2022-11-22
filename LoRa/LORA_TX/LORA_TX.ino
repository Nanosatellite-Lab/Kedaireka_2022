#include <LoRa.h> // Include LoRa.h library
#include <SPI.h> // Include SPI.h library

int counter = 0; // Variable to count the number of data transmitted
char message[] = "This is KEDAIREKA LoRa Test"; // Message to send
char message_count[] = ", Message number : "; // Message to send (number of the message)

// Main setup function
void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("LoRa Sender");
  Serial.println("+++++++++++");
    
  LoRa.setPins(PA4, PC13, PA1);
  while(!LoRa.begin(923E6)){
    Serial.println("LoRa Initialization failed!");
  }
  Serial.println("LoRa Initialization succeeded!");

}

// Main loop function
void loop() {
  Serial.print("Sending packet number :");
  Serial.println(counter);

  LoRa.beginPacket();
  LoRa.print(message);
  LoRa.print(message_count);
  LoRa.print(counter);
  LoRa.endPacket();

  counter++;

  delay(2000);
}
