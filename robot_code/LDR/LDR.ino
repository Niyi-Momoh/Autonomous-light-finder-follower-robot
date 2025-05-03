#include "DHT.h"
#define DHTPIN A3
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

const int left_LDRPin = A0;
int left_LDRVal = 0;
const int right_LDRPin = A1;
int right_LDRVal = 0;

const int pot_pin = A2;
int pot_value = 0;

const int button_pin = 4;

void setup() 
{
  Serial.begin(9600);
  pinMode(right_LDRPin, INPUT);
  pinMode(left_LDRPin, INPUT);

  pinMode(pot_pin, INPUT);

  dht.begin();
}

void loop() 
{
  pot_value = analogRead(pot_pin);
  left_LDRVal = analogRead(left_LDRVal);
  right_LDRVal = analogRead(right_LDRPin);

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print("LEFT LDR - ");
  Serial.print(left_LDRVal);
  Serial.print("\t");
  Serial.print("RIGHT LDR - ");
  Serial.print(right_LDRVal);
  Serial.print("\t");
  Serial.print("PoT - ");
  Serial.print(pot_value);
  Serial.print("\t");
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
  delay(1000);
}
