#include <Si446x.h> // include Si446x.h library

si446x_info_t info; // Buffer for storing module info
si446x_info_t *info_ptr = &info; // Pointer for the info buffer

#define Channel 127 // Channel (0 - 255)
#define Max_Packet_Size 128 // Maximum packet size @128

#define Packet_None 0 // State for packet if packet contain nothing
#define Packet_Ok 1 // State for packet if packet contain something
#define Packet_Invalid 2 // State for packet if packet is invalid (transmitter not working, etc)

char message[Max_Packet_Size] = "LOREM IPSUM DOLOR SIT AMET"; // Test Message
char *message_ptr = &message[Max_Packet_Size]; // Pointer for variable "message"

static uint8_t counter; // Variable to count number of transmitted data

// Function to get the module's info
void ModuleInfo(){
  Si446x_getInfo(info_ptr);

  Serial.print("Chip Revision          : ");
  Serial.println(info.chipRev);

  Serial.print("Customer               : ");
  Serial.println(info.customer);

  Serial.print("Function               : ");
  Serial.println(info.func);

  Serial.print("Id                     : ");
  Serial.println(info.id);

  Serial.print("Part Id                : ");
  Serial.println(info.part);

  Serial.print("Part Build             : ");
  Serial.println(info.partBuild);

  Serial.print("Patch                  : ");
  Serial.println(info.patch);

  Serial.print("Revision Branch        : ");
  Serial.println(info.revBranch);

  Serial.print("Revision External      : ");
  Serial.println(info.revExternal);

  Serial.print("Revision Internal      : ");
  Serial.println(info.revInternal);

  Serial.print("ROM ID                 : ");
  Serial.println(info.romId);

  Serial.print("Temperature            : ");
  Serial.println(Si446x_adc_temperature());

  Serial.print("RF4463 State           : ");
  Serial.println(Si446x_getState());

  Serial.println("+++++++++++++++++++++++++");
  Serial.println();
}

// Main Setup function
void setup() {
  Serial.begin(115200);
  Si446x_init();
  ModuleInfo();

  Si446x_setTxPower(SI446X_MAX_TX_POWER);
}

// Main Loop function
void loop() {
  Serial.print(F("Sending Data..."));
  Serial.println(message);

  if(Si446x_TX(message, sizeof(message), Channel, SI446X_STATE_SLEEP)){
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