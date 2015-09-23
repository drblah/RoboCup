void setup() {
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  pinMode(8,INPUT_PULLUP);
}

unsigned long startTime, stopTime, reacTime;
float reacTimeSec;
#define T 5
float tidsArray [T];
int i;

void loop() {
  for(int i=0; i<T; i++){
    delay(2000);
    Serial.println("Klar");
    delay(random(1000,3000));
    digitalWrite(13,HIGH);
    startTime = millis();
    while(digitalRead(8)==LOW){
      stopTime = millis();
      }
    reacTime = stopTime - startTime;
    reacTimeSec = (float)reacTime / 1000.0;
    Serial.println(reacTime);
    Serial.println("Millisekunder.");
    Serial.println(reacTimeSec);
    Serial.println("Sekunder.");
    delay(2000);
    while(digitalRead(8)==HIGH){
      digitalWrite(13,LOW);
      Serial.println("Waiting for recapture!");
      delay(1000);
      }
    tidsArray[i] = reacTimeSec;
    Serial.println(tidsArray[i]);
    Serial.print(i+1 );
    Serial.print(". kasse\n");
  }
  for(int i=0; i<T; i++){
    Serial.print("Tid ");
    Serial.print(i+1);
    Serial.print(": ");
    Serial.println(tidsArray[i]);
    Serial.print(" sekunder");
  }
}
