void setup() {
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  pinMode(8,INPUT_PULLUP);
}

unsigned long startTime, stopTime, reacTime;
float reacTimeSec;

void loop() {
  delay(2000);
  Serial.println("Klar");
  delay(random(1000,3000));
  digitalWrite(13,HIGH);
  startTime = millis();
  while(digitalRead(8)==LOW){
    stopTime = millis();
    Serial.println("Loop");
  }
  reacTime = stopTime - startTime;
  Serial.println(reacTime);
  Serial.println("Millisekunder.");
  reacTimeSec = (float)reacTime / 1000.0;
  Serial.println(reacTimeSec);
  Serial.println("Sekunder.");
  delay(2000);
}
