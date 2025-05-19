#include <LiquidCrystal.h>
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11
#define gas 3
#define co 4
#define fire 5

int k, m, n;
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  dht.begin();
  pinMode(gas, INPUT);
  pinMode(co, INPUT);
  pinMode(fire, INPUT);
  lcd.setCursor(0, 0);
  lcd.print("Coal Mine Safety");
  delay(2000);
  lcd.clear();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) return;

  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  k = digitalRead(gas);
  m = digitalRead(co);
  n = digitalRead(fire);

  lcd.setCursor(0, 0);
  lcd.print("gas:");
  lcd.setCursor(4, 0);
  lcd.print(k);
  lcd.setCursor(7, 0);
  lcd.print("CO:");
  lcd.setCursor(11, 0);
  lcd.print(m);
  lcd.setCursor(0, 1);
  lcd.print("Fire:");
  lcd.setCursor(5, 1);
  lcd.print(n);
  lcd.setCursor(7, 1);
  lcd.print("Temp:");
  lcd.setCursor(12, 1);
  lcd.print(t);
  delay(1000);
  lcd.clear();

  if (k == 0) Serial.print("a");
  if (m == 0) Serial.print("b");
  if (n == 0) Serial.print("c");
  if (t > 38.00) Serial.print("d");

  delay(1000);
}
