double y=0;
void setup() {
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  y= analogRead(A3);
  delay(20);
Serial.println(y);
}
//A5- Battery
//A4- SoC
//A3- Plotter
