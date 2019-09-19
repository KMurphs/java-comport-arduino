/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
*/
char Array[8]= {0xf5, 0x3c, 0, 0, 0, 0, 0, 0xf5};
char Response[8]= {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
unsigned long currentMillis;
unsigned long previousMillis;
unsigned long interval;


// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(19200);
  Serial2.begin(19200);
  interval = 1000;
  
  char chk=0;
  for (int i=1;i<6;i++)
  {
    chk=chk^Array[i];
  }
  
  Array[6]=chk;
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int i = 0;
  
  // print out the value you read:
  Serial.println("Starting");
  for (int i=0; i<8; i++)
  {
    Serial.print(Array[i]);
    Serial2.print(Array[i]);
  }

  //Start Reading
  previousMillis = millis();
  currentMillis = millis();
  i = 0;
  while (currentMillis - previousMillis <= interval){
    currentMillis = millis();
    while (Serial2.available()) {
      Response[i] = char(Serial2.read());
      i++;
      if(i == 7){
        Serial.println("\nPrinting Response");
        for (int j=0; j<8; j++)
        {
          Serial.print(uint8_t(Response[j]));
          Serial.print("-");
        }
        break;
      }
    }
  }
  Serial.println("\n\r");
}
