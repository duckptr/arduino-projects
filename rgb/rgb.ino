int LED1 = 9;
int LED2 = 10;
int LED3 = 11;
int switch1 = 3;
int switch2 = 2;
int key_count = 0;


void setup() 
{
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(switch1,INPUT);
  pinMode(switch2,INPUT);

  digitalWrite(LED1,HIGH);
  digitalWrite(LED2,LOW);
  digitalWrite(LED3,LOW);
}

void loop() 
{
 if(digitalRead(switch1) == 1)
 {
  key_count++;
 }
 if(digitalRead(switch2) == 1)
 {
  key_count--;
 }
 
 if(key_count < 0) key_count = 5;
 if(key_count > 5) key_count = 0;
 rainbow(key_count);
 delay(200);

}

void rainbow(int kc)
{
  if(kc==0) // 빨강
  {
    digitalWrite(LED1,HIGH);
    digitalWrite(LED2,LOW);
    digitalWrite(LED3,LOW);
  }
  else if (kc==1) // 노랑
  {
    digitalWrite(LED1,HIGH);
    digitalWrite(LED2,HIGH);
    digitalWrite(LED3,LOW);
  }
  else if (kc==2) // 초록
  {
    digitalWrite(LED1,LOW);
    digitalWrite(LED2,HIGH);
    digitalWrite(LED3,LOW);
  }
  else if (kc==3) // 하늘
  {
    digitalWrite(LED1,LOW);
    digitalWrite(LED2,HIGH);
    digitalWrite(LED3,HIGH);
  }
  else if (kc==4) // 파랑
  {
    digitalWrite(LED1,LOW);
    digitalWrite(LED2,LOW);
    digitalWrite(LED3,HIGH);
  }
  else if (kc==5) // 자주
  {
    digitalWrite(LED1,HIGH);
    digitalWrite(LED2,LOW);
    digitalWrite(LED3,HIGH);
  }
}
