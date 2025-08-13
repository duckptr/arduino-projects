// === IRremote (v3/v4) + 115200, UNO/Nano 예제 ===
// 배선: IR 수신기 OUT -> A0, VCC -> 5V, GND -> GND
// LED: D7, D8, D9

#include <IRremote.hpp>

// -------------------- 핀 설정 --------------------
const int RECV_PIN = A0;   // 필요시 D2/D3로 바꿔 테스트
const int LED1     = 7;
const int LED2     = 8;
const int LED3     = 9;

// -------------------- 리모컨 코드 상수 --------------------
// 1) 먼저 스케치를 올리고 시리얼(115200)에서 수신 값을 확인하세요.
// 2) 아래 상수들을 당신 리모컨 값으로 교체하세요.

// (권장) NEC 프로토콜일 때 command 값(1바이트)으로 분기
const uint8_t CMD_LED1_ON  = 0x45;  // ⬅️ 시리얼에서 본 command로 교체
const uint8_t CMD_LED1_OFF = 0x46;  // ⬅️ 교체
const uint8_t CMD_LED2_ON  = 0x47;  // ⬅️ 교체
const uint8_t CMD_LED2_OFF = 0x44;  // ⬅️ 교체
const uint8_t CMD_LED3_ON  = 0x40;  // ⬅️ 교체
const uint8_t CMD_LED3_OFF = 0x43;  // ⬅️ 교체

// (옵션) 프로토콜 혼재시 raw 데이터(32비트)로 분기하고 싶을 때
const uint32_t RAW_LED1_ON  = 0xFF9867; // ⬅️ 필요 시 교체
const uint32_t RAW_LED1_OFF = 0xFFA25D; // ⬅️ 필요 시 교체
const uint32_t RAW_LED2_ON  = 0xFF629D; // ⬅️ 필요 시 교체
const uint32_t RAW_LED2_OFF = 0xFFE21D; // ⬅️ 필요 시 교체
const uint32_t RAW_LED3_ON  = 0xFF22DD; // ⬅️ 필요 시 교체
const uint32_t RAW_LED3_OFF = 0xFF02FD; // ⬅️ 필요 시 교체

void setup() {
  Serial.begin(115200);
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK); // 탭(세션)에서만 LED 피드백
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);

  Serial.println(F("IRremote ready @115200. Press any remote button..."));
}

void loop() {
  if (!IrReceiver.decode()) return;

  // --- 디버그 출력: 프로토콜/주소/커맨드/리핏 + raw 값 ---
  IrReceiver.printIRResultShort(&Serial);
  Serial.print(F("  raw=0x"));
  Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);

  auto &d = IrReceiver.decodedIRData;

  // 리핏 프레임(버튼 길게 누름 시) 무시하고 싶다면:
  if (d.flags & IRDATA_FLAGS_IS_REPEAT) {
    IrReceiver.resume();
    return;
  }

  // === (1) NEC 프로토콜 + command로 분기 (권장) ===
  if (d.protocol == NEC) {
    switch (d.command) {
      case CMD_LED1_ON:  digitalWrite(LED1, HIGH); break;
      case CMD_LED1_OFF: digitalWrite(LED1, LOW);  break;
      case CMD_LED2_ON:  digitalWrite(LED2, HIGH); break;
      case CMD_LED2_OFF: digitalWrite(LED2, LOW);  break;
      case CMD_LED3_ON:  digitalWrite(LED3, HIGH); break;
      case CMD_LED3_OFF: digitalWrite(LED3, LOW);  break;
      default: break;
    }
  }

  // === (2) (옵션) raw 데이터로 분기 ===
  switch (d.decodedRawData) {
    case RAW_LED1_ON:  digitalWrite(LED1, HIGH); break;
    case RAW_LED1_OFF: digitalWrite(LED1, LOW);  break;
    case RAW_LED2_ON:  digitalWrite(LED2, HIGH); break;
    case RAW_LED2_OFF: digitalWrite(LED2, LOW);  break;
    case RAW_LED3_ON:  digitalWrite(LED3, HIGH); break;
    case RAW_LED3_OFF: digitalWrite(LED3, LOW);  break;
    default: break;
  }

  // 수신 확인용 내장 LED 토글
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

  IrReceiver.resume(); // 다음 신호 수신 준비
}
