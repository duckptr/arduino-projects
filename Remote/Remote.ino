#include <IRremote.hpp>  // 최신 버전에서는 .hpp 사용

int RECV_PIN = 11;
int LED1 = 7;
int LED2 = 8;

void setup() {
  Serial.begin(115200);
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK); // 수신기 초기화
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop() {
  if (IrReceiver.decode()) {
    // 받은 값 출력
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);

    // 버튼 코드 판별
    uint32_t value = IrReceiver.decodedIRData.decodedRawData;

    if (value == 0xFFA25D) {
      digitalWrite(LED1, HIGH);
    }
    if (value == 0xFFE21D) {
      digitalWrite(LED1, LOW);
    }

    if (value == 0xFF22DD) {
      digitalWrite(LED2, HIGH);
    }
    if (value == 0xFFC23D) {
      digitalWrite(LED2, LOW);
    }

    IrReceiver.resume(); // 다음 신호 수신 준비
  }
}
