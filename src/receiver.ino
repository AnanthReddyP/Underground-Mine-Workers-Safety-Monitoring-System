#include <LiquidCrystal.h>
#define buzz 2

String incomingByte;
LiquidCrystal lcd(8, 7, 6, 5, 4, 3);

void setup() {
  Serial.begin(9600);
  pinMode(buzz, OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Coal Mine Safety");
  delay(500);
  lcd.clear();
  digitalWrite(buzz, LOW);
}

void loop() {
  if (Serial.available() > 0) {
    incomingByte = Serial.readString();
    Serial.print(" I received:");
    Serial.println(incomingByte);

    if (incomingByte == "a") handleAlert("Dangerous gas");
    if (incomingByte == "b") handleAlert("CO is high");
    if (incomingByte == "c") handleAlert("Fire Alert");
    if (incomingByte == "d") handleAlert("High Temperature");
  }
}

void handleAlert(String message) {
  digitalWrite(buzz, HIGH);
  lcd.setCursor(0, 0);
  lcd.print(message);
  sendsms(message.c_str());
  delay(500);
  lcd.clear();
  digitalWrite(buzz, LOW);
}

void sendsms(const char *message) {
  delay(500);
  lcd.setCursor(0, 0);
  lcd.print("SENDING SMS ");
  delay(500);
  Serial.println("AT\r\n");
  delay(500);
  Serial.println("ATE0\r\n");
  delay(500);
  Serial.println("AT+CMGF=1\r\n");
  delay(500);
  Serial.println("AT+CMGS=\"+1XXXXXXXXXX\"");
  delay(500);
  Serial.print(message);
  delay(500);
  Serial.println((char)26);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SMS SENT");
  delay(1000);
}
