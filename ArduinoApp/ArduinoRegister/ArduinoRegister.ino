// https://arduino.stackexchange.com/questions/1013/how-do-i-split-an-incoming-string
// https://www.arduino.cc/en/Tutorial/StringCharacters

char startByte;

int inMsgLen = 0;
String inCmd = "";
String inData = "";
String outMsg = "";


String fpModuleStatuses[9] = {
  "ACK_SUCCESS",
  "ACK_FAIL",
  "",
  "",
  "ACK_FULL",
  "ACK_NOUSER",
  "ACK_USER_EXISTS",
  "ACK_FIN_EXIST",
  "ACK_TIMEOUT"
};
int regStep = 0;
String regStatus = fpModuleStatuses[0];


byte uid_msb = 0;
byte uid_lsb = 0;
byte uright = 0;


long previousMillis;
long currentMillis;
long interval = 10000;






//*************************************************************************
//                      upload fingerprint data
//*************************************************************************
void setup() {
  // put your setup code here, to run once:
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  Serial2.begin(19200);

}

//*************************************************************************
//                      upload fingerprint data
//*************************************************************************
void loop() {
    startByte = Serial.read();
    //Serial.println("Received: " + startByte);
    if(char(startByte) == '$'){
      inMsgLen = Serial.readStringUntil(':').toInt();
      inCmd = Serial.readStringUntil(':');
      //inData = Serial.readString();
      inData = "";
      processMsg(inCmd, inData, inMsgLen - 2 - sizeof(inCmd));
    }
}






//*************************************************************************
//                      upload fingerprint data
//*************************************************************************
void processMsg(String inCmd, String inData, int outDataLength){
  if(inCmd == "ping"){
    //---------------------- Ping Commnand  --------------------------//
    sendMsg(inCmd, "Arduino");

  }else if(inCmd == "doReg"){
    //------------------- Registration Commnand  -----------------------//
    if(regStep == 0){
      //------------------- Step 0
      regStep++;
      regStatus = fpModuleStatuses[0];
      sendMsg(inCmd, "OK");
      
      //extract uid and uprivildege from inData
      //inData = 4092:2 => uid_msb = 0f, uid_lsb = fc, uright = 02 

      uint16_t HighThreshold = Serial.readStringUntil(':').toInt();
      uright = Serial.readString().toInt();
      uid_lsb = (HighThreshold & 0x00FF);
      uid_msb = ((HighThreshold & 0xFF00) >>8);
     
      //sendMsg("User ID MSB", String(uid_msb));
      //sendMsg("User ID LSB", String(uid_lsb));
      //sendMsg("User Right", String(uright));
      
      //call add fingerprint, get error status and save in regStatus
      if(regStatus == fpModuleStatuses[0]){
        regStatus = addFingerPrint(regStep); //call add fingerprint
      } else {
        regStep = 0;
      }
    }
    else if(regStep == 1){
      //------------------- Step 1
      regStep++;
      sendMsg(inCmd, (regStatus == fpModuleStatuses[0] ? "proceed" : String(regStatus)));
      
      //call add fingerprint, get error status and save in regStatus
      if(regStatus == fpModuleStatuses[0]){
        regStatus = addFingerPrint(regStep); //call add fingerprint
      } else {
        regStep = 0;
      }
    }    
    else if(regStep == 2){
      //------------------- Step 2
      regStep++;
      sendMsg(inCmd, (regStatus == fpModuleStatuses[0] ? "proceed" : String(regStatus)));
      
      //call add fingerprint, get error status and save in regStatus
      if(regStatus == fpModuleStatuses[0]){
        regStatus = addFingerPrint(regStep); 
      } else {
        regStep = 0;
      }
    } 
    else if(regStep == 3){
      //------------------- Step 3
      regStep = 0;
      sendMsg(inCmd, (regStatus == fpModuleStatuses[0] ? "done" : String(regStatus)));
    } 

    
  }else if(inCmd == "uploadFP"){
    //------------------- Upload FP Commnand  -----------------------//
    //get fingerprint data of uid (inData = uid)
    uint16_t HighThreshold = Serial.readString().toInt();
    uint8_t uploadData[193];
    
    uid_lsb = (HighThreshold & 0x00FF);
    uid_msb = ((HighThreshold & 0xFF00) >>8);
    
    uploadFingerPrintFromModule(uploadData);
    
    sendMsg(inCmd, uploadData, sizeof(uploadData));
    
  }else if(inCmd == "downloadFP"){
    sendMsg(inCmd, "Not Implemented");


    
  }else{
    Serial.println("Unsupported Message");
    sendMsg(inCmd, inData);
  }
}






//*************************************************************************
//                      upload fingerprint data
//*************************************************************************
void sendMsg(String outCmd, String outData){
  outMsg = ":" + outCmd + ":" + outData;
  outMsg = "$" + String(sizeof(outMsg) + 1) + outMsg;
  Serial.println(outMsg);
}
void sendMsg(String outCmd, uint8_t outData[], int outDataLength){
  Serial.println("\n\rOverloading Function sendMsg");
  outMsg = ":" + outCmd + ":";
  outMsg = "$" + String(sizeof(outMsg) + (3 * outDataLength) + 1) + outMsg;
  Serial.print(outMsg);
  for(int i = 0; i < outDataLength; i++){
    Serial.print(uint8_t(outData[i]), DEC);
    Serial.print("-");
  }
  Serial.print("\r\n");
}





//*************************************************************************
//                      upload fingerprint data
//*************************************************************************
String addFingerPrint(int regStep){
  String fpModuleStatus = fpModuleStatuses[0];

  fpModuleStatus = addFingerPrintOnModule(regStep);
  Serial.println("Operation status at Step " + String(regStep - 1) + ": " + fpModuleStatus);
  
  return fpModuleStatus;
}






//*************************************************************************
//                      upload fingerprint data
//*************************************************************************
String addFingerPrintOnModule(int regStep){

  char Command[8]= {0xf5, 0, 0,0, 0, 0, 0, 0xf5};
  char Response[8]= {0, 0, 0, 0, 0, 0, 0, 0};
  
  Command[0x01] = regStep;
  Command[0x02] = uid_msb;
  Command[0x03] = uid_lsb;
  Command[0x04] = uright;
  
  // calculating checksum
  char chk3=0;
  for (int i=1;i<6;i++){
    chk3=chk3^Command[i];
  }
  Command[6]=chk3;

  
  int p = 0;
  //Cleaning up buffer
  //Serial.println("Cleaning up Buffer for Step: " + String(regStep));
  while (Serial2.available()) {
    Response[p] = char(Serial2.read());
  }
  // Sending command
  //Serial.println("Sending Add Fingerprint Command - Step: " + String(regStep));
  for (int p=0; p<8; p++)
  {
    //Serial.print((uint8_t)Command[p]);
    //Serial.print("-");
    Serial2.print(Command[p]);
  }


  //Reading Repsonse
  Serial.println("Waiting for a response for " + String(interval) + "msec");
  previousMillis = millis();
  currentMillis = millis();
  p = 0;
  boolean isComplete = false;
  while ((currentMillis - previousMillis <= interval) && (isComplete == false)){
    currentMillis = millis();
    while (Serial2.available()) {
      Response[p] = char(Serial2.read());
      p++;
      if(p == 7){
        //Serial.println("\nAdd Fingerprint - Step: " + String(regStep) + " - Response");
        //for (int t=0; t<8; t++)
        //{
        //  Serial.print(uint8_t(Response[t]));
        //  Serial.print("-");
        //}
        isComplete = true;
        break;
      }
    }
  }
  //Serial.println("\n\r");  
  return fpModuleStatuses[Response[4]];
}




//*************************************************************************
//                      upload fingerprint data
//*************************************************************************
void uploadFingerPrintFromModule(uint8_t ptUploadData[]){
  
  char Command[8]= {0xf5, 0x31, 0,0, 0, 0, 0, 0xf5};
  char Response[8]= {0, 0, 0, 0, 0, 0, 0, 0};
  //char upload[193];
  
  char temp = 0;
  boolean isRetrieving = false;
  boolean isComplete = false;
  String fpdata = "";
  
  Command[0x02] = uid_msb;
  Command[0x03] = uid_lsb;
  
  // calculating checksum
  char chk3=0;
  for (int i=1;i<6;i++){
    chk3=chk3^Command[i];
  }
  Command[6]=chk3;

  
  int p = 0;
  //Cleaning up buffer
  //Serial.println("Cleaning up Buffer for Step: " + String(regStep));
  while (Serial2.available()) {
    temp = char(Serial2.read());
  }

  
  // Sending command
  //Serial.println("Sending Upload Fingerprint Command");
  for (int p=0; p<8; p++)
  {
    //Serial.print((uint8_t)Command[p]);
    //Serial.print("-");
    Serial2.print(Command[p]);
  }


  //Start Reading
  previousMillis = millis();
  currentMillis = millis();
  p = 0;
  isComplete = false;
  isRetrieving = false;
  while ((currentMillis - previousMillis <= interval) && (isComplete == false)){
    currentMillis = millis();
    while (Serial2.available()) {
      temp = char(Serial2.read());
      
      if(p == 4){
        Serial.println("\n Operation Status is: ");
        Serial.print(uint8_t(temp));
        if(temp == 0){
          Serial.println("\n Retrieving Data from FingerPrint Module");
          isRetrieving = 1;
          Serial.println("\n Data to be uploaded is...");
        } else {
          Serial.println("\n There was a problem retrieving data from FingerPrint Module");
          isRetrieving = 0;
          fpdata = fpModuleStatuses[temp];
          break;
        }
      }
      
      if(p >= 8 && isRetrieving == 1){//205 = 2 + 1 + 193  (user id + user priv + fp data)
        //ptUploadData[p - 9] = temp;
        //Serial.print(uint8_t(temp));
        //Serial.print("-");
        if(p >= 12 && isRetrieving == 1 && p < 205){
          ptUploadData[p - 12] = uint8_t(temp);
          Serial.print(uint8_t(temp));
          Serial.print("-");
        }
        if(p >= 205){
          isComplete = true;
          break;
        }
      }
            
      p++;
    }
  }
}
