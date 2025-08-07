int sw = 7;

void setup() {
  Serial.begin(115200);
  pinMode(sw, INPUT_PULLUP);
  delay(1000);

}

void loop() {
  Serial.print("X축 : ");
  Serial.println(analogRead(A0));
  Serial.print("\t");
  Serial.print("Y축 : ");
  Serial.println(analogRead(A1));
  Serial.print("\t");
  Serial.print("스위치 : ");
  Serial.println(analogRead(sw));
  delay(100);

}
