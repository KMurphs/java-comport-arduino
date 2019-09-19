/*
 * There are three serial ports on the ESP known as U0UXD, U1UXD and U2UXD.
 * 
 * U0UXD is used to communicate with the ESP32 for programming and during reset/boot.
 * U1UXD is unused and can be used for your projects. Some boards use this port for SPI Flash access though
 * U2UXD is unused and can be used for your projects.
 * 
*/
 
#define RXD2 3
#define TXD2 1
char txdata[8] = {0xf5, 0x3C,0,0,0,0,0x3c,0xf5};
 
void setup() {
  // Note the format for setting a serial port is as follows: Serial2.begin(baud-rate, protocol, RX pin, TX pin);
  //Serial.begin(115200);
  //Serial1.begin(9600, SERIAL_8N1, RXD2, TXD2);
  //Serial2.begin(19200, SERIAL_8N1, RXD2, TXD2);
  Serial.begin(19200);
 // Serial.println("Serial Txd is on pin: "+String(TX));
 // Serial.println("Serial Rxd is on pin: "+String(RX));

  
}
 
void loop() { //Choose Serial1 or Serial2 as required


//finger print reader according to the flow diagram in the waveshare datasheet
  //int db=Serial2.read();
   Serial.read();
//Serial.write(txdata);
//int value=Serial.read();

Serial.println(RXD2);
delay(1000);

  
  
 /* Serial2.write(0X01); // send cmd to start checking
  int fptemplate1=Serial2.read();

  Serial2.write(0X02);
  int fptemplate2=Serial2.read();

  Serial2.write(0X03);
  int fptemplate3=Serial2.read();
  */
}
