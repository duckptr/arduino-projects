int led1=3;

void setup() {
  Serial.begin(115200);
  pinMode(3,OUTPUT);
  digitalWrite(3,LOW);
}

void loop() {
  if(Serial.available())
  {
    delay(1000);
    Serial.println("LED on");
    digitalWrite(3,HIGH);
  }
}