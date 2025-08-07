const int LED1 = 2;
const int LED2 = 3;
const int LED3 = 4;
const int switch1 = 5;
const int switch2 = 6;

int key_count = 0;
bool prev1 = false;
bool prev2 = false;

void setup() 
{
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(switch1, INPUT);
  pinMode(switch2, INPUT);

  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
}

void loop() 
{
  // 현재 스위치 상태 읽기
  bool curr1 = digitalRead(switch1);
  bool curr2 = digitalRead(switch2);

  // 이전에는 안 눌렸고 지금 눌렸으면 → 상태 전이 감지
  if (curr1 && !prev1) {
    key_count++;
  }
  if (curr2 && !prev2) {
    key_count--;
  }

  // 이전 상태 저장
  prev1 = curr1;
  prev2 = curr2;

  // key_count 순환
  if (key_count < 0) key_count = 5;
  if (key_count > 5) key_count = 0;

  // 현재 key_count에 따른 동작 실행
  rainbow(key_count);

  delay(50);  // 빠른 응답을 위해 짧게
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
