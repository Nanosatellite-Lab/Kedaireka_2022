#include <RH_RF24.h> // include Si446x.h library

#define Max_Packet_Size 128

char message[Max_Packet_Size] = "LOREM IPSUM DOLOR SIT AMET"; // Test Message
char *message_ptr = &message[Max_Packet_Size]; // Pointer for variable "message"

static uint8_t counter; // Variable to count number of transmitted data

RH_RF24 rf4463(A4, A0, A1); // Initialize RF4463 Object

// Main Setup function
void setup() {
  Serial.begin(115200);

  while (!rf4463.init())
    Serial.println("Init Failed");
  Serial.println("Init Success");
}

// Main Loop function
void loop() {
  Serial.print(F("Sending Data..."));
  Serial.println(message);

  if(rf4463.send((uint8_t*)message, sizeof(message))){
    counter++;
  }else{
    Serial.println(F("Transmit Failed"));
  }

  Serial.print(F("Totals : "));
  Serial.print(counter);
  Serial.println(" Data");
  Serial.println("+++++++");
  delay(1000);
}