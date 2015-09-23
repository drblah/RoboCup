void setup() 
{
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  pinMode(8,INPUT_PULLUP);
}

unsigned long startTime, stopTime, reacTime;
float reacTimeSec;
#define T 10
float timeArray [T];
int i;

void loop() 
{
  for(int i = 0; i < T; i++)
  {
    startRandomTimer();
    waitForButtonPress();
    getreacTime();
    waitForReconnect();
    printArrayTime();
  }
  printFinalArray();
}

void startRandomTimer() 
{
  Serial.println("Klar.");
  delay(1000);  
  Serial.println("Start.");
  delay(random(1000,3000));
  digitalWrite(13,HIGH);
  startTime = millis();
}

void waitForButtonPress() 
{
  while(digitalRead(8)==LOW)
  {
  stopTime = millis();    
  }
}

void getreacTime() 
{
  reacTime = stopTime - startTime;
  reacTimeSec = (float)reacTime / 1000.0;
  Serial.println("Reaktions tid er:");
  Serial.print(reacTime);
  Serial.println(" millisekunder");
  Serial.print(reacTimeSec);
  Serial.println(" sekunder");
}

void waitForReconnect() 
{
  while(digitalRead(8)==HIGH)
  {
    digitalWrite(13,LOW);
    Serial.println("Waiting for reconnect!");
    delay(1000);  
  }
}

void printArrayTime() 
{
  timeArray[i] = reacTimeSec;
  Serial.println(timeArray[i]);
  Serial.print(i+1);
  Serial.print(". kasse");
  delay(500);
  Serial.println(" ");  
}

void printFinalArray() 
{
  for(int i = 0; i < T; i++)
  {
    Serial.print("Tid ");
    Serial.print(i+1);
    Serial.print(": ");
    Serial.println(timeArray[i]);
    Serial.print(" sekunder");  
  }
}
