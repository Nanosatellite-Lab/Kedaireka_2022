#include <Si446x.h> // include Si446x.h library

#define Channel 127 // Channel (0 - 255)
#define Max_Packet_Size 128 // Maximum packet size @128

#define Packet_None 0 // State for packet if packet contain nothing
#define Packet_Ok 1 // State for packet if packet contain something
#define Packet_Invalid 2 // State for packet if packet is invalid (transmitter not working, etc)

// Custom data type for packet handling
typedef struct{
	uint8_t ready;
	int16_t rssi;
	uint8_t length;
	uint8_t buffer[Max_Packet_Size];
} packetReceived_t;

static packetReceived_t packetReceived; // Init the received packet struct
static uint32_t counter; // Variable to count number of transmitted data
static uint32_t invalids; // Variable to count number of invalid transmitted data

si446x_info_t info; // Buffer for storing module info
si446x_info_t *info_ptr = &info; // Pointer for the info buffer

// Callback when RX is complete
void SI446X_CB_RXCOMPLETE(uint8_t length, int16_t rssi){
	if(length > Max_Packet_Size)
		length = Max_Packet_Size;

	packetReceived.ready = Packet_Ok;
	packetReceived.rssi = rssi;
	packetReceived.length = length;

	Si446x_read((uint8_t*)packetReceived.buffer, length);
}

// Callback when RX is Failed
void SI446X_CB_RXINVALID(int16_t rssi){
	packetReceived.ready = Packet_Invalid;
	packetReceived.rssi = rssi;
}

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
}

// Main Loop function
void loop() {
  Si446x_RX(Channel);

  Serial.println("Waiting for Packet...");
  while(packetReceived.ready == Packet_None);

  if(packetReceived.ready != Packet_Ok)
	{
		invalids++;
		packetReceived.ready = Packet_None;
		Serial.print("Invalid packet! Signal: ");
		Serial.print(packetReceived.rssi);
		Serial.println("dBm");

		Si446x_RX(Channel);
	}else{
    counter++;
    packetReceived.ready = Packet_None;

    Serial.println("Got packet, Receiving data...");

    Serial.print("Signal strength: ");
		Serial.print(packetReceived.rssi);
		Serial.println("dBm");
    Serial.print("Data from Transmitter: ");
		Serial.write((uint8_t*)packetReceived.buffer, sizeof(packetReceived.buffer));
		Serial.println();
  }

  Serial.print("Totals: ");
	Serial.print(counter);
	Serial.print("Data, ");
	Serial.print(invalids);
	Serial.println("Invalid");
	Serial.println("+++++++");
  delay(1000);
}