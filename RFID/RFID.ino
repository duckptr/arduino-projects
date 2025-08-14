#include <SPI.h>
#include <MFRC522.h>
#include <ThreeWire.h>
#include <RtcDS1302.h>

// -------------------- 핀 설정 --------------------
// RC522 (SPI)
const uint8_t SS_PIN   = 10; // RC522 SDA(SS)
const uint8_t RST_PIN  = 9;  // RC522 RST

// DS1302 (ThreeWire: IO, SCLK, CE)
const uint8_t DS1302_RST = 3; // CE
const uint8_t DS1302_DAT = 4; // I/O
const uint8_t DS1302_CLK = 5; // SCLK

// 피드백(원하면 -1로 비활성화)
const int8_t LED_OK   = 6;  // 출석 성공 LED (비활성화하려면 -1)
const int8_t LED_FAIL = 7;  // 미등록 LED   (비활성화하려면 -1)
const int8_t BUZZER   = 8;  // 부저         (비활성화하려면 -1)

// -------------------- 객체 --------------------
MFRC522 mfrc522(SS_PIN, RST_PIN);
ThreeWire myWire(DS1302_DAT, DS1302_CLK, DS1302_RST); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);

// -------------------- 헬퍼 --------------------
inline bool validPin(int8_t p) { return p >= 0; }

// UID(Byte[]) -> "XXXXXXXX" (대문자, 콜론 없음) 문자열
String uidToHex(const MFRC522::Uid &u) {
  String s;
  for (byte i = 0; i < u.size; i++) {
    if (u.uidByte[i] < 0x10) s += '0';
    s += String(u.uidByte[i], HEX);
  }
  s.toUpperCase();
  return s; // 예: "DEADBEEF"
}

// 날짜를 yyyymmdd 정수로
uint32_t yyyymmdd(const RtcDateTime& t) {
  return (uint32_t)t.Year() * 10000UL + (uint32_t)t.Month() * 100UL + (uint32_t)t.Day();
}

void beepOK() {
  if (validPin(BUZZER)) tone(BUZZER, 2000, 80);
  if (validPin(LED_OK)) { digitalWrite(LED_OK, HIGH); delay(150); digitalWrite(LED_OK, LOW); }
}
void beepFail() {
  if (validPin(BUZZER)) tone(BUZZER, 400, 200);
  if (validPin(LED_FAIL)) { digitalWrite(LED_FAIL, HIGH); delay(250); digitalWrite(LED_FAIL, LOW); }
}

// -------------------- 등록 멤버 테이블 --------------------
// 카드 찍어서 시리얼에 뜬 UID(대문자, 공백/콜론 없음)를 uidHex에 넣어주세요.
struct Member {
  const char* name;
  const char* uidHex;   // 예: "DEADBEEF"
  uint32_t    lastDate; // 마지막 출석일(yyyymmdd) - 전원 꺼지면 초기화됨
};

// 샘플(수정하세요)
Member members[] = {
  {"M1_명준",  "AAAAAAAA", 0},
  {"M2_테스트","BBBBBBBB", 0},
};
const size_t NUM_MEMBERS = sizeof(members)/sizeof(members[0]);

int findMemberIndexByUid(const String& uidHex) {
  for (size_t i = 0; i < NUM_MEMBERS; i++) {
    // 대소문자 무시 비교
    if (uidHex.equalsIgnoreCase(members[i].uidHex)) return (int)i;
  }
  return -1;
}

// -------------------- RTC 초기화 --------------------
void ensureRtcTime() {
  Rtc.Begin();

  if (!Rtc.GetIsRunning()) {
    Rtc.SetIsRunning(true);
  }

  if (!Rtc.IsDateTimeValid()) {
    // 유효한 시간이 없으면 컴파일 시간으로 세팅
    RtcDateTime compiled(__DATE__, __TIME__);
    Rtc.SetDateTime(compiled);
    Serial.println(F("[RTC] Invalid time -> set to compile time."));
  }
}

// -------------------- SETUP --------------------
void setup() {
  Serial.begin(115200);
  // Uno에선 while(!Serial) 불필요

  if (validPin(LED_OK))   pinMode(LED_OK, OUTPUT);
  if (validPin(LED_FAIL)) pinMode(LED_FAIL, OUTPUT);
  if (validPin(BUZZER))   pinMode(BUZZER, OUTPUT);

  SPI.begin();
  mfrc522.PCD_Init();
  mfrc522.PCD_AntennaOn();
  mfrc522.PCD_DumpVersionToSerial(); // RC522 칩/펌웨어 정보 출력

  ensureRtcTime();

  Serial.println(F("\n=== RFID 출석 체크 시작 ==="));
  Serial.println(F("등록되지 않은 태그를 찍으면 UID가 출력됩니다. 그 값을 코드의 members[]에 등록하세요."));
  Serial.println(F("※ RC522는 3.3V 전원 사용. D0/D1는 비워두세요."));
}

// -------------------- LOOP --------------------
void loop() {
  // 새 카드 대기 및 UID 읽기
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  String uidHex = uidToHex(mfrc522.uid);
  RtcDateTime now = Rtc.GetDateTime();
  uint32_t today = yyyymmdd(now);

  // 타임스탬프 문자열
  char ts[32];
  snprintf(ts, sizeof(ts), "%04u-%02u-%02u %02u:%02u:%02u",
           now.Year(), now.Month(), now.Day(), now.Hour(), now.Minute(), now.Second());

  // 멤버 조회
  int idx = findMemberIndexByUid(uidHex);

  if (idx >= 0) {
    // 오늘 이미 찍었는지 확인(하루 1회 인정)
    if (members[idx].lastDate == today) {
      Serial.print(F("[이미 출석됨] "));
      Serial.print(members[idx].name);
      Serial.print(F(" | UID=")); Serial.print(uidHex);
      Serial.print(F(" | ")); Serial.println(ts);
      beepOK(); // 가벼운 피드백
    } else {
      members[idx].lastDate = today;
      Serial.print(F("[출석 처리] "));
      Serial.print(members[idx].name);
      Serial.print(F(" | UID=")); Serial.print(uidHex);
      Serial.print(F(" | ")); Serial.println(ts);
      beepOK();
    }
  } else {
    Serial.print(F("[미등록] UID="));
    Serial.print(uidHex);
    Serial.print(F(" | "));
    Serial.println(ts);
    Serial.println(F("→ 위 UID를 members[]에 추가하세요."));
    beepFail();
  }

  // 카드 정리
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}
