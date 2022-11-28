// Include Arduino Wire library for I2C
#include <Wire.h>
 
// Define Slave I2C Address
#define SLAVE_ADDR 9
 
// Define Slave answer size
#define ANSWERSIZE 5
 
int msg[10] = {1,2,3,4,5,6,7,8,9,10};
void setup() {
 
  // Initialize I2C communications as Master
  Wire.begin();
  
  // Setup serial monitor
  Serial.begin(115200);
  Serial.println("I2C Master Demonstration");
}
 
void loop() {
  delay(50);
  Serial.println("Write data to slave");
  
  // Write a charatre to the Slave
  Wire.beginTransmission(SLAVE_ADDR);
  for(int i = 0; i<10; i++){
    Wire.write(msg[i]);
  }
  Wire.endTransmission();
    
  // Serial.println("Receive data");
  // 
  // // Read response from Slave
  // // Read back 5 characters
  // Wire.requestFrom(SLAVE_ADDR,ANSWERSIZE);
  
  // // Add characters to string
  // String response = "";
  // while (Wire.available()) {
  //     char b = Wire.read();
  //     response += b;
  // } 
  
  // // Print to Serial Monitor
  // Serial.println(response);
}