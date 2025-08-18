  The Smart Attendance System is a low-cost and efficient project that uses RFID technology to track attendance and automatically log it into an Excel or CSV file. It eliminates manual record-keeping, reduces errors, and ensures reliable time-stamped entries.

Features

RFID-based Identification: Each user is assigned a unique RFID tag that acts as their ID card.

Automatic Logging: Upon scanning, details such as ID, date, and time are stored in an Excel or CSV sheet.

Real-Time Clock (RTC): Provides accurate timestamps for each record.

Feedback Display (optional): An LCD screen can be used to display successful scans or errors.

Scalability: Can be adapted for schools, offices, or events requiring attendance monitoring.

 Tech Stack

Arduino Uno – main microcontroller.

RC522 RFID Module – reads unique tag IDs.

RTC Module – ensures real-time clock accuracy.

Excel/CSV Logging – handled via Python script or Arduino serial connection with Excel macros.

LCD Display (optional) – provides instant feedback.

⚙️ How it Works

Each user is issued an RFID tag/card linked to their identity.

When the tag is scanned, the RFID module transmits its unique ID to the Arduino.

Arduino processes the ID, fetches the current date and time from the RTC module, and sends the data to a computer.

A Python script or Excel macro receives the data and logs it into an attendance sheet in real time.

The LCD (if included) shows whether the scan was successful or if the tag is unauthorized.

📂 Applications

Schools and Universities – student attendance tracking.


ARDUINO CODES

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


Offices – employee check-in/check-out system.

Events – quick and automated participant registration.

This project demonstrates the practical use of RFID technology in creating efficient, automated, and paperless systems. It is beginner-friendly yet scalable for larger implementations.
