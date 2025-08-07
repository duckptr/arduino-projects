int led = 9;

void setup() 
{
  pinMode(led,OUTPUT);
  Serial.begin(115200);  
}

void loop() 
{
  int value = analogRead(A2); // 소리감지 센서값을 읽어서 변수 value에 저장해줍니다.
  // map() 함수 사용, map(value, fromLow, fromHigh, toLow, toHigh)
  // 변환할 수, 현재 범위 값의 하한, 현재 범위 값의 상한, 목표 범위값의 하한, 목표 범위값의 상한
  // 읽어들인 값으로 LED의 밝기를 구하고, LED 밝기를 새로고침 합니다.
  int adjust = map(value,0,1024,0,255);
  analogWrite(led,adjust);
  Serial.println(value);
  delay(100);
}
