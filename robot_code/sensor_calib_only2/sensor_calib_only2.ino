#include <Button.h>
Button button1(4);

//#include <ezButton.h>

#include "DHT.h"
#define DHTPIN A3
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

bool sensor_calibrated = false;
bool motor_calibrated = false;

unsigned long speed_interval =5000;
unsigned long calibrate_time =7000;
unsigned long end_time = 0;

const int pot_pin = A2;
int pot_value = 0;
int calibrate = 0;

int Rmotor_speed;
int Lmotor_speed;


void setup() 
{
  Serial.begin(9600);

  pinMode(pot_pin, INPUT);

  dht.begin();
  button1.begin();
}

void loop() 
{
  
  
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
  }
  ****************************************************/
  /*unsigned long current_time = millis();

  if (sensor_calibrated == false)
  {
    Serial.println("click button to calibrate sensor in the next 5 seconds");
    unsigned long calibrate_time = current_time + 5000;

    if (millis() < calibrate_time)
    {
      Serial.println("lvl 1");
      while(true)
      {
        Serial.println("lvl 2");
        current_time = millis();
        while (button.isPressed() || button.isReleased() )
        {
          Serial.println("lvl 3");
          Serial.println("Calibration begins");
          pot_value = analogRead(pot_pin);
          calibrate = map (pot_value, 0, 1023, -10, 10);
          temp_hum_sensor(calibrate);
          //delay(500);
          sensor_calibrated = true;

          if (current_time  > calibrate_time)
          {
            break;
          }
        }
        if(!(button.isPressed() ))
        {
          Serial.println("Skipping sensor calibration");
          //delay(500);
        }
      }
    }
    
  }
  //update current time
  current_time = millis();

  if(!motor_calibrated)
  {
    // calibrate motors
    Serial.println("click button to calibrate motors in the next 5 seconds");
    unsigned long calibrate_time = current_time + 5000;

    //calculate new calibration time
    calibrate_time = current_time + 5000;

    if (current_time < calibrate_time)
    {
      while (button.isPressed() && current_time < calibrate_time)
      {
        Serial.println("Calibration begins");
        pot_value = analogRead(pot_pin);
        calibrate = map (pot_value, 0, 1023, -100, 100);
        motor_speed = 255 + calibrate;
        Serial.print("Motor speed - ");
        Serial.println(motor_speed);
        //delay(500);
        motor_calibrated = true;

        if (millis() > calibrate_time)
        {
          break;
        }
      }
      if(!(button.isPressed() && button.isReleased()))
      {
        Serial.println("Skipping motor calibration");
        //delay(500);
      }
    }
    
  }

//**********************************************


  unsigned long current_time = millis();

  if (sensor_calibrated == false && (current_time < calibrate_time))
  {
    Serial.println("click button to calibrate sensors in the next 5 seconds");
    while (button.isPressed() && millis() < calibrate_time)
    {
      Serial.println("sensor Calibration begins");
      pot_value = analogRead(pot_pin);
      calibrate = map (pot_value, 0, 1023, -10, 10);
      temp_hum_sensor(calibrate);
      sensor_calibrated = true;
      current_time = millis();

      if (current_time - end_time > calibrate_time)
      {
        break;
      }
    }
    if(current_time - end_time > calibrate_time)
    {
      Serial.println("Skipping sensor calibration");
    }
    
  }
  end_time = current_time;

//motor calibation 

  current_time = millis();
  calibrate_time = current_time + calibrate_time;
  if (motor_calibrated == false && (current_time < calibrate_time))
  {
    Serial.println("click button to calibrate motors in the next 5 seconds");
    while (button.isPressed() && current_time < calibrate_time)
    {
      Serial.println("motors Calibration begins");
      pot_value = analogRead(pot_pin);
      calibrate = map (pot_value, 0, 1023, -100, 100);
      temp_hum_sensor(calibrate);
      current_time = millis();
      motor_calibrated = true;

      if (current_time  > calibrate_time)
      {
        break;
      }
    }
    if(current_time  > calibrate_time)
    {
      Serial.println("Skipping Motor calibration");
    }
    
  }
  end_time = current_time;
//***********************************************************/

//sensor calibration
unsigned long current_time = millis();
  if (sensor_calibrated == false)
  {
    Serial.println("Starting sensor calibration press button for 1 second to cancel");
    unsigned long end_time = current_time + calibrate_time;
    do
    {
      delay(500);
      if(button1.pressed())
      {
        Serial.println("Skipping calibration process");
        break;
      }

      sensor_calibrate();
  
      current_time = millis();

    }while (current_time < end_time);
  }
  sensor_calibrated = true;

  //motor calibration
  current_time = millis();
  if(motor_calibrated == false)
  {
    Serial.println("Starting right motor calibration press button for 1 second to cancel");
    end_time = current_time + calibrate_time;
    do
    {
      delay(500);
      if(button1.pressed())
      {
        Serial.println("Skipping calibration process");
        break;
      }

      Rmotor_calibrate();

      current_time = millis();
    }while (current_time < end_time);
  }

  current_time = millis();
  if(motor_calibrated == false)
  {
    Serial.println("Starting left motor calibration press button for 1 second to cancel");
    end_time = current_time + calibrate_time;
    do
    {
      delay(500);
      if(button1.pressed())
      {
        Serial.println("Skipping calibration process");
        break;
      }

      Lmotor_calibrate();

      current_time = millis();
    }while (current_time < end_time);
  }
  motor_calibrated = true;
}

//scanning routine

//functions 
int sensor_calibrate()
{
  pot_value = analogRead(pot_pin);
  calibrate = map (pot_value, 0, 1023, -10, 10);
  temp_hum_sensor(calibrate);
  Serial.println("sensor function used");
}

int Rmotor_calibrate()
{
  pot_value = analogRead(pot_pin);
  calibrate = map (pot_value, 0, 1023, -100, 100);
  Rmotor_speed = 255 + calibrate;
  Serial.println("Rmotor function used");
}

int Lmotor_calibrate()
{
  pot_value = analogRead(pot_pin);
  calibrate = map (pot_value, 0, 1023, -100, 100);
  Lmotor_speed = 255 + calibrate;
  Serial.println("Lmotor function used");
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
