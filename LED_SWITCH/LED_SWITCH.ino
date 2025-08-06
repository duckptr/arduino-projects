const int sw = 8;
const int led = 7;
const unsigned long holdTime = 3000;

void setup() {
  pinMode(sw,INPUT_PULLUP);
  pinMode(led,OUTPUT);
  digitalWrite(led, LOW);
}

void loop() 
{
  if(digitalRead(sw)== LOW)
  {
    digitalWrite(led,HIGH);
    delay(holdTime);
    digitalWrite(led,LOW);

    while (digitalRead(sw) == LOW) {
        delay(10);
    
   }  
  }

}
