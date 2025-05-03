#include <ezButton.h>

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

ezButton button(4);

const int left_LED = 11;
int ledState  = HIGH;

int buttonState;             // the current reading from the input pin
int lastbuttonState = LOW;   // the previous reading from the input pin
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time

void setup() 
{
  Serial.begin(9600);
  pinMode(left_LDRPin, INPUT);
  pinMode(right_LDRPin, INPUT);
  

  pinMode(pot_pin, INPUT);

  pinMode(left_LED, OUTPUT);

//  pinMode(button_pin, INPUT_PULLUP);
  button.setDebounceTime(50);

  dht.begin();
}

void loop() 
{
  /*int reading = digitalRead(button_pin);
  if (reading != lastbuttonState)
  {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    if (reading != buttonState)
    {
      buttonState = reading;
      if(buttonState == HIGH)
      {
        ledState = !ledState;
      }
      //else{digitalWrite(left_LED, LOW);}
    }
  }
  digitalWrite(left_LED, ledState);
  lastbuttonState = reading;*/


  button.loop();

  // Calibrate 
  if(button.isPressed())
    Serial.println("The button is pressed");

  if(button.isReleased())
    Serial.println("The button is released");

  pot_value = analogRead(pot_pin);
  left_LDRVal = analogRead(left_LDRVal);
  right_LDRVal = analogRead(right_LDRPin);
  int d = map (left_LDRVal, 0,1023, 0, 24);

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
  Serial.println(d);
  delay(1000);
}
