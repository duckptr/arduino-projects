int led1 = 7;
int led2 = 6;
int led3 = 5;

void setup() {
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);

  Serial.begin(115200);
  Serial.println("시리얼 통신을 시작합니다.");
}

void loop() 
{
  if(Serial.available())
  {
    char a;
    a=Serial.read();
    if(a=='1')
    {
      digitalWrite(5,HIGH);
      digitalWrite(6,HIGH);
      digitalWrite(7,HIGH);

      Serial.println("LED ON");
    }
    if(a=='0')
    {
      digitalWrite(5,LOW);
      digitalWrite(6,LOW);
      digitalWrite(7,LOW);

      Serial.println("LED OFF");
    }
   }
}
