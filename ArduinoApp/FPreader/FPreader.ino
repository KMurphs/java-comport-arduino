
char SetFPcmd[8]= {0xf5, 0x01, 0X01, 0, 0, 0X01, 0, 0xf5};
char ResponseSetFPcmd[8]= {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
char Array2[8]= {0xf5, 0x3c, 0, 0, 0, 0, 0, 0xf5};
unsigned long currentMillis;
unsigned long previousMillis;
unsigned long interval;

// DEFINES
// 1. Start and stop conditions
#define START_CMD   0xF5
#define STOP_CMD    0xF5

// 2. Command list
#define CMD_ENABLE_MODULE     0x2C
#define CMD_SET_ADD_MODE      0x2D
#define CMD_ADD_FINGERPRINT   0x01
// ...

// 3. Reponse codes
#define ACK_SUCCESS         0x00
#define ACK_FAIL            0x01
#define ACK_FULL            0x04  
#define ACK_NOUSER          0x05
#define ACK_USER_EXISTS     0x06
#define ACK_FIN_EXIST       0x07
#define ACK_TIMEOUT         0x08

// Init
//--------------------------------------------------------------------------
// -> Setup UART
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(19200); // Serial monitor
  Serial2.begin(19200); // FP Sensor comms
  interval = 1000;
}
//--------------------------------------------------------------------------

// HELPER FUNCTIONS
// 1. Checksum
//--------------------------------------------------------------------------
uint8_t calculate_checksum(uint8_t *buf, uint8_t len)
{
  // Variables
  int i = 0;
  uint8_t checksum = 0;

  for (i = 1; i < len; i++) {
    checksum ^= buf[i];
    Serial.print(buf[i]);
    Serial.print("*");
  }

  Serial.print("\n");

  Serial.println("Checksum:");
  Serial.print(checksum);

  Serial.print("\n");

  return checksum;  
}
//--------------------------------------------------------------------------

// FP COMMS FUNCTIONS
// 1. Enable Module
//--------------------------------------------------------------------------
bool FP_add_module(void)
{
  // Variables
  bool ret_code = false;  // Indicates operation success/failure
  uint8_t txBuf[8] = {0}; // Data to be sent
  uint8_t rxBuf[8] = {0}; // Data to be received

  // Populate message to be sent to sensor
  txBuf[0] = START_CMD;         // 0xF5
  txBuf[1] = CMD_ENABLE_MODULE; // CMD = 0x2C
  txBuf[2] = 0x00;  // P1
  txBuf[3] = 0x00;  // P2
  txBuf[4] = 0x00;  // P3
  txBuf[5] = 0x00;  // Blank byte always 0x00

  // Calculate and load checksum value
  txBuf[6] = calculate_checksum(txBuf, 5);

  txBuf[7] = STOP_CMD;  // 0xF5

  // Send message to sensor
//  while (Serial.available()) {
    for (int i = 0; i < sizeof(txBuf); i++) {
      Serial.write(txBuf[i]);
      Serial.print("-");
    }
//  }

  Serial.print("\n");

  // Analyse the response, check if valid?

  return ret_code;
}
//--------------------------------------------------------------------------

void loop()
{
  // Test
  Serial.println("Test");

  // Send command data over serial
  FP_add_module();

  delay(2000);
}
