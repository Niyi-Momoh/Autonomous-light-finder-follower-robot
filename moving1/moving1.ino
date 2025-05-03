#include <Button.h>
Button button1(4);

//#include <ezButton.h>

#include "DHT.h"
#define DHTPIN A3
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
float t;
float h;
int i;

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16

bool sensor_calibrated = false;
bool motor_calibrated = false;
bool scanning = false;

unsigned long speed_interval =3300;
unsigned long calibrate_time =7000;
unsigned long end_time = 0;

const int pot_pin = A2;
int pot_value = 0;
int calibrate = 0;

int RightForward = 5; 
int RightBack = 3; 
int LeftForward = 6;
int LeftBack = 9;
int Rmotor_speed = 50;
int Lmotor_speed = 50;

const int left_ldr = A0;
const int right_ldr = A1;
int left_ldrval;
int right_ldrval;
int max_bright;
int min_bright = 1023;
int thresh;
int diff;
int prev_max_bright;
bool find_light = true;

int distance;

const int TRIG_PIN = 7;
const int ECHO_PIN = 8;
long duration_us;
int distance_cm;

const int left_led = 11;
const int right_led = 10;
int left_led_bright;
int right_led_bright;
bool is_blinking = false;
unsigned long previousled_millis = 0;

void setup() 
{
  Serial.begin(9600);

  pinMode(pot_pin, INPUT);

  pinMode(RightForward, OUTPUT);
  pinMode(RightBack, OUTPUT);
  pinMode(LeftForward, OUTPUT);
  pinMode(LeftBack, OUTPUT);

  pinMode(right_ldr, INPUT);
  pinMode(left_ldr, INPUT);

  dht.begin();
  button1.begin();

  pinMode(TRIG_PIN, OUTPUT); // Sets the trigPin as an Output
  pinMode(ECHO_PIN, INPUT); // Sets the echoPin as an Input

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) 
  {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.display();
  delay(2000); 
  display.clearDisplay();
  display.drawPixel(10, 10, SSD1306_WHITE);

  pinMode(left_led, OUTPUT);
  pinMode(right_led, OUTPUT);
}

void loop() 
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.print("lets begin!");
  display.display();
  delay(500);

  display.clearDisplay();
  
  for(i=display.width()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, i, 0, SSD1306_WHITE);
    display.display();
    delay(1);
    }
  for(i=display.height()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, 0, i, SSD1306_WHITE);
    display.display();
    delay(1);
  }
  delay(250);
  display.clearDisplay();

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
      blink_led();
      delay(500);
      if(button1.pressed())
      {
        Serial.println("Skipping calibration process");
        stop_blinking();
        break;
      }

      sensor_calibrate();
  
      current_time = millis();

    }while (current_time < end_time);
    
  }
  stop_blinking();
  sensor_calibrated = true;

  //motor calibration
  current_time = millis();
  i = 0;
  if(motor_calibrated == false)
  { 
    Serial.println("Starting right motor calibration press button for 1 second to cancel");
    
    end_time = current_time + calibrate_time;
    do
    {
      blink_right_led();
      delay(500);
      if(button1.pressed())
      {
        Serial.println("Skipping calibration process");
        stop_blinking();
        break;
      }

      
      Rmotor_calibrate();

      current_time = millis();
    }while (current_time < end_time);
    stop_blinking();
  }

  current_time = millis();
  i = 0;
  if(motor_calibrated == false)
  {
    Serial.println("Starting left motor calibration press button for 1 second to cancel");
    
    end_time = current_time + calibrate_time;
    do
    {
      blink_left_led();
      delay(500);
      if(button1.pressed())
      {
        Serial.println("Skipping calibration process");
        stop_blinking();
        break;
      }
      
      Lmotor_calibrate();

      current_time = millis();
    }while (current_time < end_time);
    stop_blinking();
  }
  motor_calibrated = true;

  current_time = millis();
  if(scanning == false)
  {
    Serial.println();
    Serial.print("scanning ongoing...");
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.print("scanning ongoing... ");
    display.display();
    delay(100);
    
    
    end_time = current_time + speed_interval;
    do
    {
      blink_led();
      Rotate360();
      Serial.println("reading LDRs");
      ldr_reading();
      Ultrasonic();
      current_time = millis();
    }while (current_time < end_time);
    Stop();
    stop_blinking();
  }
  scanning = true;

  while (distance_cm > 5 || right_ldrval < max_bright)
  {
    ldr_reading();
    if (right_ldrval > thresh && left_ldrval > thresh)
    {
      Forward();
      ldr_reading();
      Ultrasonic();
      temp_hum_sensor(calibrate);

      if (find_light)
      {
        prev_max_bright = thresh;
        find_light = false;
      }
      int light_intensity = map(distance_cm, 0, 110, 170, 0);
      analogWrite(right_led, light_intensity);
      analogWrite(left_led, light_intensity);
    }
    else if (right_ldrval < thresh && left_ldrval > thresh)
    {
      Left();
      ldr_reading();
      Ultrasonic();
      temp_hum_sensor(calibrate);
      digitalWrite(right_led, LOW);
      analogWrite(left_led, 150);
    }
    else if (right_ldrval > thresh && left_ldrval < thresh)
    {
      Right();
      ldr_reading();
      Ultrasonic();
      temp_hum_sensor(calibrate);
      analogWrite(right_led, 150);
      digitalWrite(left_led, LOW);
    }
    else
    {
      Rotate360(); 
      ldr_reading(); 
      Ultrasonic();
      temp_hum_sensor(calibrate);
      if(!find_light)
      {
        max_bright = prev_max_bright;
      }
      digitalWrite(right_led, LOW);
      digitalWrite(left_led, LOW);
    }
    
    //celebration routine
    if(distance_cm < 6 && right_ldrval >= (max_bright - 10))
    {
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.print("Hurray!! ");
      display.display();
      delay(100);

      exit(0);
      Stop();
    }
  }
}


//functions 
int sensor_calibrate()
{
  pot_value = analogRead(pot_pin);
  calibrate = map (pot_value, 0, 1023, -10, 10);
  temp_hum_sensor(calibrate);
  //Serial.println("sensor function used");
  while(i< 50)
  {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 3);
    display.print("press button to exit temp calibration");
    display.display();
    i ++;
    delay(10);
  }
}

int Rmotor_calibrate()
{
  pot_value = analogRead(pot_pin);
  calibrate = map (pot_value, 0, 1023, 0, 100);
  Rmotor_speed = 120 + calibrate;
  Serial.print("Rmotor speed is- ");
  Serial.println(Rmotor_speed);
  
  while(i < 50)
  {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 3);
    display.print("press button to exit Rmotor calibration");
    display.display();
    i++;
    delay(10);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Rmotor speed: ");
  display.print(Rmotor_speed);
  display.display();
  delay(100);
}

int Lmotor_calibrate()
{
  pot_value = analogRead(pot_pin);
  calibrate = map (pot_value, 0, 1023, 0, 100);
  Lmotor_speed = 120 + calibrate;
  Serial.print("Lmotor speed is- ");
  Serial.println(Lmotor_speed);

  while(i < 50)
  {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 3);
    display.print("press button to exit Lmotor calibration");
    display.display();
    i++;
    delay(10);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Lmotor speed: ");
  display.print(Lmotor_speed);
  display.display();
  delay(100);
}

int temp_hum_sensor(int c)
{

  float hprev = dht.readHumidity();
  h = hprev + calibrate;
  float tprev = dht.readTemperature();
  t = tprev + calibrate;
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
  Serial.println(F("°C "));
  /*Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));*/
  //return h;
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Temperature: ");
  display.print(t);
  display.println("C");
  display.print("Humidity: ");
  display.print(h);
  display.display();
  delay(100);
}

void Forward()
{
  analogWrite(RightForward, Rmotor_speed);
  digitalWrite(RightBack, LOW);
  Serial.print("Right motor Forward");
  Serial.print(Rmotor_speed);
  Serial.print("\t");
  analogWrite(LeftForward, Lmotor_speed);
  digitalWrite(LeftBack, LOW);  
  Serial.print("Left motor Forward");
  Serial.print(Lmotor_speed);
  Serial.print("\t");
}

void Reverse()
{
  digitalWrite(RightForward, LOW); 
  analogWrite(RightBack, Rmotor_speed);
  Serial.print("Right motor Reverse");
  Serial.print(Rmotor_speed);
  Serial.print("\t");
  digitalWrite(LeftForward, LOW); 
  analogWrite(LeftBack, Lmotor_speed);
  Serial.print("Left motor Reverse");
  Serial.print(Lmotor_speed);
  Serial.print("\t");
}

void Stop()
{
    digitalWrite(RightForward, LOW);
    digitalWrite(RightBack, LOW);
    Serial.print("Right motor Stop");
    
    Serial.print("\t");
    digitalWrite(LeftForward, LOW);
    digitalWrite(LeftBack, LOW);
    Serial.print("Left motor Stop");
    
    Serial.print("\t");
}

void Rotate360()
{
  Serial.print("ROTATING  ");
  digitalWrite(RightForward, LOW);
  analogWrite(RightBack, Rmotor_speed);
  Serial.print("Right motor B- ");
  Serial.print(Rmotor_speed);
  Serial.print("\t");
  analogWrite(LeftForward, Lmotor_speed);
  digitalWrite(LeftBack, LOW);
  Serial.print("Left motor F- ");
  Serial.print(Lmotor_speed);
  Serial.print("\t");
}

void Left()
{
  Serial.print("LEFT  ");
  analogWrite(RightForward, Rmotor_speed);
  digitalWrite(RightBack, LOW);
  Serial.print("Right motor F- ");
  Serial.print(Rmotor_speed);
  Serial.print("\t");
  digitalWrite(LeftForward, LOW);
  analogWrite(LeftBack, Lmotor_speed);
  Serial.print("Left motor B- ");
  Serial.print(Lmotor_speed);
  Serial.print("\t");
}

void Right()
{
  Serial.print("RIGHT  ");
  digitalWrite(RightForward, LOW);
  analogWrite(RightBack, Rmotor_speed);
  Serial.print("Right motor B- ");
  Serial.print(Rmotor_speed);
  Serial.print("\t");
  analogWrite(LeftForward, Lmotor_speed);
  digitalWrite(LeftBack, LOW);
  Serial.print("Left motor F- ");
  Serial.print(Lmotor_speed);
  Serial.print("\t");
}

int ldr_reading()
{
  //max_bright = 0;
  right_ldrval = analogRead(right_ldr);
  left_ldrval = analogRead(left_ldr );
  Serial.print("R-LDR - ");
  Serial.print(right_ldrval);
  Serial.print("\t");
  Serial.print("L-LDR - ");
  Serial.print(left_ldrval);
  Serial.print("\t");
  if (right_ldrval < min_bright)
  {
    min_bright = right_ldrval;
  }
  else if (left_ldrval < min_bright)
  {
    min_bright = left_ldrval;
  }
  if (right_ldrval > max_bright)
  {
    max_bright = right_ldrval;
  }
  else if (left_ldrval > max_bright)
  {
    max_bright = left_ldrval;
  }
  diff = max_bright - min_bright;
  thresh = max_bright - (0.2 * diff);
}

int Ultrasonic()
{
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure duration of pulse from ECHO pin
  duration_us = pulseIn(ECHO_PIN, HIGH);
  
   // Calculate the distance
  distance_cm = 0.017 * duration_us;
  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.print("cm");
  Serial.print("\t");

  //display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 24);
  display.print("Distance: ");
  display.print(distance_cm);
  display.println("cm");
  display.display();
  delay(100);
}

void blink_led() 
{
  if (!is_blinking) 
  {
    is_blinking = true;
    previousled_millis = millis();
  }
  
  unsigned long current_millis = millis();
  if (current_millis - previousled_millis >= 500)
  {
    previousled_millis = current_millis;
    digitalWrite(right_led, !digitalRead(right_led)); 
    digitalWrite(left_led, !digitalRead(left_led));   
  }
}

void stop_blinking() 
{
  is_blinking = false;
  digitalWrite(right_led, LOW); 
  digitalWrite(left_led, LOW); 
}

void blink_right_led() 
{
  if (!is_blinking) 
  {
    is_blinking = true;
    previousled_millis = millis();
  }
  
  unsigned long current_millis = millis();
  if (current_millis - previousled_millis >= 500)
  {
    previousled_millis = current_millis;
    digitalWrite(right_led, !digitalRead(right_led));   
  }
}

void blink_left_led() 
{
  if (!is_blinking) 
  {
    is_blinking = true;
    previousled_millis = millis();
  }
  
  unsigned long current_millis = millis();
  if (current_millis - previousled_millis >= 500)
  {
    previousled_millis = current_millis;
    digitalWrite(left_led, !digitalRead(left_led));   
  }
}