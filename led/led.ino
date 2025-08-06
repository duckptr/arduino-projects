int led1=7;

void setup() {
  pinMode(7, OUTPUT);

}

void loop() {
  digitalWrite(led1, HIGH);
  delay(500);

  digitalWrite(led1, LOW);
  delay(500);
}
