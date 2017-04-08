//Pin13Charging
//Pin12OverCharge
#include <GSM.h>
#include <string.h>

#define PINNUMBER ""

GSM gsmAccess;
GSM_SMS sms;

char junk;
//String inputString="";
const int AnalogIn = A0;
const int icharge = 13;
const int ocharge = 12;
int timex=0;
float voltage=0.0;
float charge=0.0;
char remoteNum[20]="7060334174";
char cnt;

void setup()                    // run once, when the sketch starts
{
 Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }            // set the baud rate to 9600, same should be of your Serial Monitor
 pinMode(13, OUTPUT);
 pinMode(12, OUTPUT);
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
}

void loop()
{
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
      charge=0;}
    if(voltage*5/1023>3.9)
    {
      digitalWrite(ocharge,HIGH);  
    }
    else
    {
      digitalWrite(ocharge,LOW);  
    }
    if(voltage*5/1023>0.0)
    {
      digitalWrite(icharge,HIGH);  
    }
    else
    {
      digitalWrite(icharge,LOW);  
    }
  if(Serial.available()){
  while(Serial.available()){
    cnt = Serial.read();
    if(cnt=='i')
    {
      Serial.println("Enter s for SOC data: ");
    }
    if(cnt=='s')
    {
      Serial.print(" voltage = ");
      Serial.print(voltage*5/1023);
      Serial.print("\t SOC = ");
      Serial.println(charge);
    }
    else if((cnt=='m')||((voltage*5/1023)>30.7)||(timex>=1800000)){
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
  }
  }}
