#define Stor 20
int data;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int counter = 0;
  char udskriveren[Stor] = "";  
  int udskriveren2[Stor];
    while (true)
  {
    if (Serial.available() > 0) 
    {
        udskriveren[counter] = (char) Serial.read();
        udskriveren2[counter] = (int) udskriveren[counter];
        if (udskriveren[counter] == '\r') 
        {
          break;
        }
        counter++;
    }
  }
    while (true)
    {
        
    }
  Serial.println(udskriveren);
  Serial.println((int)udskriveren);
}
