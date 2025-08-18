#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 5
#define RST_PIN 21

#define GREEN_LED 12
#define RED_LED 13
#define BUZZER 15

MFRC522 rfid(SS_PIN, RST_PIN);

// Your valid RFID card UID
String authorizedUIDs[] = {
  "2CB8C401"
  "03181005"
};

void setup() {
  Serial.begin(115200);
  SPI.begin();
  rfid.PCD_Init();

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  Serial.println("Scan your RFID tag...");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return;
  }

  String uid = getUID();
  Serial.println("Card UID: " + uid);

  if (isAuthorized(uid)) {
    successFeedback();
  } else {
    failureFeedback();
  }

  delay(3000); // Avoid multiple reads of same tag
  rfid.PICC_HaltA();  // Stop reading
}

String getUID() {
  String uidStr = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    uidStr += String(rfid.uid.uidByte[i] < 0x10 ? "0" : "");
    uidStr += String(rfid.uid.uidByte[i], HEX);
  }
  uidStr.toUpperCase();
  return uidStr;
}

bool isAuthorized(String uid) {
  for (String validUID : authorizedUIDs) {
    if (uid == validUID) return true;
  }
  return false;
}

void successFeedback() {
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(BUZZER, HIGH);
  delay(300);
  digitalWrite(BUZZER, LOW);
  digitalWrite(GREEN_LED, LOW);
  delay(300);
  
}

void failureFeedback() {
  //digitalWrite(RED_LED, HIGH);
  for (int i = 0; i < 2; i++) {
    digitalWrite(BUZZER, HIGH); delay(150);
    digitalWrite(BUZZER, LOW); delay(150);
  }
  digitalWrite(RED_LED, LOW);
}
