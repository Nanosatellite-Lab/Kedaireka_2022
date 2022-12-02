#include <LoRa.h> // Include LoRa.h library
#include <SPI.h> // Include SPI.h library

int counter = 0; // Variable to count the number of data transmitted
char message[] = "This is KEDAIREKA LoRa Test"; // Message to send
char message_count[] = ", Message number : "; // Message to send (number of the message)

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

// Main setup function
void setup() {
  SystemClock_Config();
  Serial.begin(115200);
  while (!Serial);

  Serial.println("LoRa Sender");
  Serial.println("+++++++++++");
    
  LoRa.setPins(PA4, PC13, PA1);
  while(!LoRa.begin(923E6)){
    Serial.println("LoRa Initialization failed!");
  }
  Serial.println("LoRa Initialization succeeded!");
  LoRa.setSignalBandwidth(250E3);

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

}
