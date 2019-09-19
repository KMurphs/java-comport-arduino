// https://arduino.stackexchange.com/questions/1013/how-do-i-split-an-incoming-string
// https://www.arduino.cc/en/Tutorial/StringCharacters

char startByte;

int inMsgLen = 0;
String inCmd = "";
String inData = "";
String outMsg = "";

int regStep = 0;
int regStatus = 0;

void setup() {
  // put your setup code here, to run once:
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

void loop() {
    startByte = Serial.read();
    //Serial.println("Received: " + startByte);
    if(char(startByte) == '$'){
      inMsgLen = Serial.readStringUntil(':').toInt();
      inCmd = Serial.readStringUntil(':');
      inData = Serial.readString();
      processMsg(inCmd, inData, inMsgLen - 2 - sizeof(inCmd));
    }
}

void processMsg(String inCmd, String inData, int outDataLength){
  if(inCmd == "ping"){
    sendMsg(inCmd, "Arduino");
  }else if(inCmd == "doReg"){
    if(regStep == 0){
      regStep++;
      sendMsg(inCmd, "OK");
      //extract uid and uprivildege from inData
      
      //call add fingerprint, get error status and save in regStatus
      regStatus = addFingerPrint(regStep); 
    }
    else if(regStep == 1){
      regStep++;
      sendMsg(inCmd, (regStatus == 0 ? "proceed" : String(regStatus)));
      
      //call add fingerprint, get error status and save in regStatus
      regStatus = addFingerPrint(regStep); //call add fingerprint
    }    
    else if(regStep == 2){
      regStep++;
      sendMsg(inCmd, (regStatus == 0 ? "proceed" : String(regStatus)));
      
      //call add fingerprint, get error status and save in regStatus
      regStatus = addFingerPrint(regStep); 
    } 
    else if(regStep == 3){
      regStep = 0;
      sendMsg(inCmd, (regStatus == 0 ? "done" : String(regStatus)));
    } 
  }else if(inCmd == "uploadFP"){
    //get fingerprint data of uid (inData = uid)
    sendMsg(inCmd, "Your Finger Print Data");
  }else if(inCmd == "downloadFP"){
    sendMsg(inCmd, "Not Implemented");
  }else{
    Serial.println("Unsupported Message");
    sendMsg(inCmd, inData);
  }
}

void sendMsg(String outCmd, String outData){
  outMsg = ":" + outCmd + ":" + outData;
  outMsg = "$" + String(sizeof(outMsg) + 1) + outMsg;
  Serial.println(outMsg);
}

int addFingerPrint(int regStep){
  int fpModuleStatus = 0;

  
  return fpModuleStatus;
}
