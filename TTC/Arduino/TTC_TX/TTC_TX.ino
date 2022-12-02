#include <RH_RF24.h> // include Si446x.h library
#include <RHSoftwareSPI.h>

#define Max_Packet_Size 128
#define rf_receive A3
#define rf_transmit A2
#define power_hpa PB8

char message[Max_Packet_Size] = "LOREM IPSUM DOLOR SIT AMET"; // Test Message
char *message_ptr = &message[Max_Packet_Size]; // Pointer for variable "message"

static int counter; // Variable to count number of transmitted data

RHSoftwareSPI spi2;
RH_RF24 rf4463(PB12, PB4, PB5, spi2); // Initialize RF4463 Object

// Main Setup function
void setup() {
  spi2.setPins(PB14, PB15, PB13);
  pinMode(rf_receive, OUTPUT);
  pinMode(rf_transmit, OUTPUT);
  pinMode(power_hpa, OUTPUT);

  digitalWrite(rf_receive, LOW);
  digitalWrite(rf_transmit, HIGH);
  digitalWrite(power_hpa, HIGH);

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
}