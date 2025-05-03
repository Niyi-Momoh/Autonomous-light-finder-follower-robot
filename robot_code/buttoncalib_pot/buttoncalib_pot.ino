#include <ezButton.h>

#include "DHT.h"
#define DHTPIN A3
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

unsigned long speed_interval =5000;
unsigned long calibrate_time =5000;
unsigned long end_time = 0;
int lastBtnState = 1;
int btnState;

const int pot_pin = A2;
int pot_value = 0;
int calibrate = 0;

ezButton button(4);  // create ezButton object that attach to pin 4;
int c;
//int temp_hum_sensor(c);
void setup() 
{
  Serial.begin(9600);
  button.setDebounceTime(50); // set debounce time to 50 milliseconds

  pinMode(pot_pin, INPUT);

  dht.begin();
}

void loop() 
{
  button.loop(); // MUST call the loop() function first
  
  
  //Serial.println(btnState);

  /*unsigned long currentTime = millis();
  while (millis() <= speed_interval)
  {
    do
    {
      i++;
      while(button.isPressed())
      {
        Serial.println("Calibration time");
      }
      if(!button.isPressed()) 
      {
        Serial.println("skipping calibration"); 
      }
    }while (i < 100);
    
  }
  
  if(button.isPressed())
    {Serial.println("Calibration time");}
  delay(1000);
  //Serial.println("click button to calibrate in the next 5 seconds");
  
  
  if(millis() < 5000)
  {
    
    Serial.println("not");
    lastBtnState = btnState;
    btnState = button.getState();

    if (btnState == 0 && lastBtnState == 1)
    {
      Serial.println("Calibration time");
    }
    //delay(50);
  }*/

  Serial.println("click button to calibrate in the next 5 seconds");

  unsigned long current_time = millis();

  if (current_time < calibrate_time)
  {
    while (button.isPressed() && millis() < 5000)
    {
      Serial.println("Calibration begins");
      pot_value = analogRead(pot_pin);
      calibrate = map (pot_value, 0, 1023, -10, 10);
      temp_hum_sensor(calibrate);

       if (current_time - end_time > calibrate_time)
       {
        continue;
       }
    }
    if(!(button.isPressed() || button.isReleased()))
    {
      Serial.println("Skipping calibration");
    }
  }
  end_time = current_time;
}


int temp_hum_sensor(int c)
{
  float hprev = dht.readHumidity();
  float h = hprev + calibrate;
  float tprev = dht.readTemperature();
  float t = tprev + calibrate;
  float fprev = dht.readTemperature(true);
  float f = fprev + calibrate;

  //float hif = dht.computeHeatIndex(f, h);
  //float hic = dht.computeHeatIndex(t, h, false);

  /*Serial.print("LEFT LDR - ");
  Serial.print(left_LDRVal);
  Serial.print("\t");
  Serial.print("RIGHT LDR - ");
  Serial.print(right_LDRVal);
  Serial.print("\t");
  Serial.print("PoT - ");
  Serial.print(pot_value);
  Serial.print("\t");*/
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  /*Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));*/
  //return h;
}