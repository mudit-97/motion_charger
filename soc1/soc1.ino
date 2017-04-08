#include <GSM.h>
#include <string.h>

#define PINNUMBER ""

GSM gsmAccess;
GSM_SMS sms;


/*
  Read input serial
 */


const int AnalogIn = A0;
//const int AnalogOut = A1;
int timex=0;
float voltage=0;
float charge=0.0;

  char remoteNum[20];

void setup() {

  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // connection state
  boolean notConnected = true;
  while (notConnected) {
    if (gsmAccess.begin(PINNUMBER) == GSM_READY) {
      notConnected = false;
    } else {
      Serial.println("Not connected");
      delay(1000);
    }
  }

  Serial.println("GSM initialized");
  
  Serial.println("Enter a mobile number: ");  // telephone number to send sms
  
  readSerial(remoteNum);
  
Serial.println("Enter s for SOC and voltage data: ");

Serial.println("Enter m for sending message: ");
}
char cnt;
void loop() {
  cnt = Serial.read();
  if(cnt=='s')
  {
     Serial.print(" voltage = ");
  Serial.print(voltage*5/1023);
  Serial.print("\t SOC = ");
  Serial.println(charge);
  }
  else if((cnt=='m')||((voltage*5/1023)>3.9)||(timex>=1800000)){
    if(timex>=1800000)
    {
      timex=0; 
    }
  String txtMsg = "SOC = " + String(charge) + " ; Voltage = "+ String(voltage*5/1023) + "\nEnjoy";
  Serial.println("SENDING");
  Serial.println();
  Serial.println("Message:");
  Serial.println(txtMsg);

  // send the message
  sms.beginSMS(remoteNum);
  sms.print(txtMsg);
  sms.endSMS();
  Serial.println("\nCOMPLETE!\n");
   if(cnt!='m')
   {
      delay(5000);
      timex+=5000;
   }
}
  voltage= analogRead(AnalogIn);
  if(voltage>798){
    charge=0.49*voltage-316;
    }
  else if(voltage<798 && voltage>750){
    charge=1.166*voltage-856;
    }
  else if(voltage<750 && voltage>409) {
    charge=0.14*voltage-86;
    }
  else{
    charge=0;
    }  
 // analogWrite(AnalogOut, voltage);
   
  delay(10);
  timex+=10;
}

int readSerial(char result[]) {
  int i = 0;
  while (1) {
    while (Serial.available() > 0) {
      char inChar = Serial.read();
      if (inChar == '\n') {
        result[i] = '\0';
        Serial.flush();
        return 0;
      }
      if (inChar != '\r') {
        result[i] = inChar;
        i++;
      }
    }
  }
}
