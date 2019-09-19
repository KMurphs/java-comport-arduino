unsigned long currentMillis;
unsigned long previousMillis;
unsigned long interval;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(19200);
  Serial2.begin(19200);
  interval = 5000;
}


void EnableModule(void){
// enable the module into a dormant state
char Command[8]= {0xf5, 0x05, 0, 0, 0, 0, 0, 0xf5};
char Response[8]= {0xf5, 0, 0, 0, 0, 0, 0, 0xf5};

// calculating checksum
char chk=0;
for (int i=1;i<6;i++)
{
chk=chk^Command[i];
}
 Command[6]=chk;

// sending command
    while (Serial.available()){
    char temp = Serial.read();
 }
  while (!Serial.available()){}

  
  int i = 0;

  // print out the value you read:
  Serial.println("Starting");
  for (int i=0; i<8; i++)
  {
    Serial.print((uint8_t)Command[i]);
    Serial.print("-");
    
    Serial2.print(Command[i]);
  }

  //Start Reading

  i = 0;
   
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
  
  Serial.println("\n\r");

  //if(Response[6]==Command[6]){FP_Add_Mode();}
  
  
  } // end of EnableModule function
//_______________________________________________________________________________________________________________________________
void FP_Add_Mode(){
// enable the module into a dormant state
char Command2[8]= {0xf5, 0x2d, 0, 0, 0, 0, 0, 0xf5};
char Response2[8]= {0xf5, 0, 0, 0, 0, 0, 0, 0xf5};

// calculating checksum
char chk2=0;
for (int i=1;i<6;i++)
{
chk2=chk2^Command2[i];
}
 Command2[6]=chk2;

// sending command
    while (Serial.available()){
    char temp = Serial.read();
 }
  while (!Serial.available()){}

  
  int p = 0;

  // print out the value you read:
  Serial.println("Starting FP_Add_Mode");
  for (int p=0; p<8; p++)
  {

    Serial.print((uint8_t)Command2[p]);
    Serial.print("-");
    
    Serial2.print(Command2[p]);
  }

  //Start Reading

  p = 0;
   
    while (Serial2.available()) {
      Response2[p] = char(Serial2.read());
      p++;
      if(p == 7){
        Serial.println("\nPrinting FP_Add_Mode Response");
        for (int t=0; t<8; t++)
        {
          Serial.print(uint8_t(Response2[t]));
          Serial.print("-");
        }
        break;
      }
    }
  
  Serial.println("\n\r");

  if(Response2[6]==Command2[6]){AddFingerprint();}
AddFingerprint();
  } // end of EnableModule function

//_______________________________________________________________________________________________________________________________


  void AddFingerprint(){

char Command3[8]= {0xf5, 0x01, 0x00, 0x01, 3, 0, 0, 0xf5};
char Response3[8]= {0, 0, 0, 0, 0, 0, 0, 0};

// calculating checksum
char chk3=0;
for (int i=1;i<6;i++)
{
chk3=chk3^Command3[i];
}
 Command3[6]=chk3;

// sending command
    while (Serial.available()){
    char temp = Serial.read();
 }
  while (!Serial.available()){}

  
  int p = 0;

  // print out the value you read:
  Serial.println(" ADD FINGERPRINT 1ST TIME ");
  for (int p=0; p<8; p++)
  {
    Serial.print((uint8_t)Command3[p]);
    Serial.print("-");
    
    Serial2.print(Command3[p]);
  }
///////////////////////////////////////////////////
//  //Start Reading
//  p = 0;
//    while (Serial2.available()) {
//      Response3[p] = char(Serial2.read());
//      p++;
//      if(p == 7){
//        Serial.println("\n ADD FINGERPRINT 1ST RESPONSE");
//        for (int t=0; t<8; t++)
//        {
//          Serial.print(uint8_t(Response3[t]));
//          Serial.print("-");
//        }
//        break;
//      }
//    } 
//  Serial.println("\n\r");
///////////////////////////////////////////////
  //Start Reading
  previousMillis = millis();
  currentMillis = millis();
  p = 0;
  while (currentMillis - previousMillis <= interval){
    currentMillis = millis();
    while (Serial2.available()) {
      Response3[p] = char(Serial2.read());
      p++;
      if(p == 7){
        Serial.println("\n ADD FINGERPRINT 1ST RESPONSE");
        for (int t=0; t<8; t++)
        {
          Serial.print(uint8_t(Response3[t]));
          Serial.print("-");
        }
        break;
      }
    }
  }
  Serial.println("\n\r");
////////////////////////////////////////
    
    }

//_______________________________________________________________________________________________________________________________


  void AddFingerprint2(){

char Command3[8]= {0xf5, 0x02, 0x00,0x01, 3, 0, 0, 0xf5};
char Response3[8]= {0, 0, 0, 0, 0, 0, 0, 0};

// calculating checksum
char chk3=0;
for (int i=1;i<6;i++)
{
chk3=chk3^Command3[i];
}
 Command3[6]=chk3;

// sending command
    while (Serial.available()){
    char temp = Serial.read();
 }
  while (!Serial.available()){}

  
  int p = 0;

  // print out the value you read:
  Serial.println(" ADD FINGERPRINT 2ND TIME");
  for (int p=0; p<8; p++)
  {
    Serial.print((uint8_t)Command3[p]);
    Serial.print("-");
    
    Serial2.print(Command3[p]);
  }

//  //Start Reading
//
//  p = 0;
//   
//    while (Serial2.available()) {
//      Response3[p] = char(Serial2.read());
//      p++;
//      if(p == 7){
//        Serial.println("\n ADD FINGERPRINT 2ND RESPONSE");
//        for (int t=0; t<8; t++)
//        {
//          Serial.print(uint8_t(Response3[t]));
//          Serial.print("-");
//        }
//        break;
//      }
//    }
//  
//  Serial.println("\n\r");
  //Start Reading
  previousMillis = millis();
  currentMillis = millis();
  p = 0;
  while (currentMillis - previousMillis <= interval){
    currentMillis = millis();
    while (Serial2.available()) {
      Response3[p] = char(Serial2.read());
      p++;
      if(p == 7){
        Serial.println("\n ADD FINGERPRINT 2ND RESPONSE");
        for (int t=0; t<8; t++)
        {
          Serial.print(uint8_t(Response3[t]));
          Serial.print("-");
        }
        break;
      }
    }
  }
  Serial.println("\n\r");
    
    }


//_______________________________________________________________________________________________________________________________  

  void AddFingerprint3(){

char Command3[8]= {0xf5, 0x03, 0x00,0x01, 3, 0, 0, 0xf5};
char Response3[8]= {0, 0, 0, 0, 0, 0, 0, 0};

// calculating checksum
char chk3=0;
for (int i=1;i<6;i++)
{
chk3=chk3^Command3[i];
}
 Command3[6]=chk3;

// sending command
    while (Serial.available()){
    char temp = Serial.read();
 }
  while (!Serial.available()){}

  
  int p = 0;

  // print out the value you read:
  Serial.println(" ADD FINGERPRINT 3RD TIME ");
  for (int p=0; p<8; p++)
  {
    Serial.print((uint8_t)Command3[p]);
    Serial.print("-");
    
    Serial2.print(Command3[p]);
  }

//  //Start Reading
//
//  p = 0;
//   
//    while (Serial2.available()) {
//      Response3[p] = char(Serial2.read());
//      p++;
//      if(p == 7){
//        Serial.println("\n ADD FINGERPRINT 3RD RESPONSE ");
//        for (int t=0; t<8; t++)
//        {
//          Serial.print(uint8_t(Response3[t]));
//          Serial.print("-");
//        }
//        break;
//      }
//    }
//  Serial.println("\n\r");
  //Start Reading
  previousMillis = millis();
  currentMillis = millis();
  p = 0;
  while (currentMillis - previousMillis <= interval){
    currentMillis = millis();
    while (Serial2.available()) {
      Response3[p] = char(Serial2.read());
      p++;
      if(p == 7){
        Serial.println("\n ADD FINGERPRINT 3RD RESPONSE");
        for (int t=0; t<8; t++)
        {
          Serial.print(uint8_t(Response3[t]));
          Serial.print("-");
        }
        break;
      }
    }
  }
  Serial.println("\n\r");  
    
    }




//_______________________________________________________________________________________________________________________________  

  void loop(){
   // EnableModule();
    AddFingerprint();
    AddFingerprint2();
    //delay(2000);
    AddFingerprint3();
    }
