#include <Servo.h>

// digital pin test //

int led1 = 6;
int led2 = 7;

void setup() {
  pinMode(led1,OUTPUT); // 6번 핀을 출력으로 설정
  pinMode(led2,OUTPUT); // 7번 핀을 출력으로 설정

  Serial.begin(9600);
  Serial.println("시리얼 통신 시작");

}

void loop() 
{
  if(Serial.available())
  {
    char a;
    a=Serial.read();
    if(a=='1')
    {
      digitalWrite(6,HIGH);
      digitalWrite(7,HIGH);
      Serial.println("LED ON");
    }
    if(a=='0')
    {
      digitalWrite(6,LOW);
      digitalWrite(7,LOW);
      Serial.println("LED OFF");
    }
  }
}
