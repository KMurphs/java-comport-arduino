unsigned long currentMillis;
unsigned long previousMillis;
unsigned long interval;

//Define Reponse codes
#define PASS                0x00
#define FAIL                0x01
#define ACK_FULL            0x04  
#define ACK_NOUSER          0x05
#define ACK_USER_EXISTS     0x06
#define ACK_FIN_EXIST       0x07
#define ACK_TIMEOUT         0x08



void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(19200);
  Serial2.begin(19200);
  interval = 15000;
}

//_______________________________________________________________________________________________________________________________


  void AddFingerprint(){

char Command3[8]= {0xf5, 0x31, 0x00, 0x01, 0, 0, 0, 0xf5};
char Response3[8]= {0, 0, 0, 0, 0, 0, 0, 0};
char upload[195];
//char data_packet[199]={0};  
//char eigVal[193]={0};          
// calculating checksum
char chk3=0;
char temp=0;
char isRetrieving=0;
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
  Serial.println("\n\r");

//  //Start Reading
//  previousMillis = millis();
//  currentMillis = millis();
//  p = 0;
//  while (currentMillis - previousMillis <= interval){
//    currentMillis = millis();
//    while (Serial2.available()) {
//      Response3[p] = char(Serial2.read());
//      p++;
//      if(p == 8){
//        Serial.println("\n ADD FINGERPRINT 1ST RESPONSE");
//        for (int t=0; t<9; t++)
//        {
//          Serial.print(uint8_t(Response3[t]));
//          Serial.print("-");
//        }
//        p=0;
//        //break;
//      }
//    }
//  }
//  Serial.println("\n\r");
//-------------------------upload fingerprint data-------------------------

  //Start Reading
  previousMillis = millis();
  currentMillis = millis();
  p = 0;
  isRetrieving = 0;
  while (currentMillis - previousMillis <= interval){
    currentMillis = millis();
    while (Serial2.available()) {
      temp = char(Serial2.read());
      
      if(p == 4){
        Serial.println("\n Response[4] is :");
        Serial.print(uint8_t(temp));
        if(temp == PASS){
          Serial.println("\n Retrieving Data from FingerPrint Module");
          isRetrieving = 1;
          Serial.println("\n Data to be uploaded is...");
        } else {
          Serial.println("\n There was a problem retrieving data from FingerPrint Module");
          isRetrieving = 0;
          break;
        }
      }
      if(p >= 9 && isRetrieving == 1 && p < 205){//205 = 2 + 1 + 193  (user id + user priv + fp data)
        upload[p - 9] = temp;
        Serial.print(uint8_t(temp));
        Serial.print("-");
      }
      p++;
      }
 
    
    
  }
  Serial.println("\n\r");
  }

//_______________________________________________________________________________________________________________________________  

  void loop(){
   // EnableModule();
    AddFingerprint();
    //AddFingerprint2();
    //delay(2000);
   // AddFingerprint3();
    }
