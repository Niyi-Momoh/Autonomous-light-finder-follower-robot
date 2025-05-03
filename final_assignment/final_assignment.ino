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

int xx=40;
int yy=0;
int tt=0;

// functions to diisplay celebration gi
// '_a_frm26,50', 50x50px
const unsigned char epd_bitmap__a_frm26_50 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x73, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x63, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x61, 0xc0, 0xe0, 0x00, 
	0x00, 0x00, 0x00, 0x30, 0xe1, 0xf0, 0x00, 0x00, 0x00, 0x1c, 0x38, 0x73, 0xb8, 0x00, 0x00, 0x00, 
	0x3f, 0x1c, 0x33, 0x18, 0x00, 0x00, 0x00, 0x73, 0xce, 0x3b, 0x18, 0x00, 0x00, 0x00, 0x60, 0xf7, 
	0x1b, 0x18, 0x00, 0x00, 0x00, 0x70, 0x7f, 0x1f, 0x18, 0x00, 0x00, 0x00, 0x38, 0x1f, 0x8f, 0x18, 
	0x00, 0x00, 0x00, 0x1e, 0x07, 0x8f, 0x18, 0x00, 0x00, 0x00, 0x0f, 0x83, 0x8f, 0x18, 0x00, 0x00, 
	0x00, 0x03, 0xe3, 0x8f, 0x18, 0x00, 0x00, 0x00, 0x00, 0xe1, 0xc7, 0x18, 0x00, 0x00, 0x00, 0x00, 
	0x30, 0x87, 0x18, 0x00, 0x00, 0x00, 0x00, 0x38, 0x07, 0x18, 0x00, 0x00, 0x00, 0x01, 0xfc, 0x03, 
	0x18, 0x00, 0x00, 0x00, 0x03, 0xfc, 0x00, 0x18, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x18, 0x00, 
	0x00, 0x00, 0x0e, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 
	0x70, 0x60, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x60, 0xff, 0x00, 0x0e, 0x00, 0x00, 0x00, 0xe1, 0xff, 
	0x80, 0x07, 0x00, 0x00, 0x00, 0xc3, 0x81, 0xc0, 0x03, 0x00, 0x00, 0x00, 0xe7, 0x00, 0xc0, 0x01, 
	0x80, 0x00, 0x00, 0x7e, 0x00, 0xe0, 0x01, 0xc0, 0x00, 0x00, 0x7e, 0x00, 0x60, 0x00, 0xc0, 0x00, 
	0x00, 0xff, 0x00, 0x70, 0x00, 0xc0, 0x00, 0x00, 0xe3, 0x80, 0x30, 0x00, 0xc0, 0x00, 0x00, 0x61, 
	0xc0, 0x70, 0x00, 0xc0, 0x00, 0x00, 0x70, 0xc0, 0xe0, 0x00, 0xc0, 0x00, 0x00, 0x30, 0xf9, 0xc0, 
	0x00, 0xc0, 0x00, 0x00, 0x38, 0x7f, 0x80, 0x00, 0xc0, 0x00, 0x00, 0x18, 0x0f, 0x00, 0x00, 0xc0, 
	0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 
	0x0e, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x03, 0xc0, 
	0x3f, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0xf1, 0xff, 0xfc, 0xc0, 0x00, 0x00, 0x00, 0x7f, 0xe0, 0x3f, 
	0xc0, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// '_a_frm27,50', 50x50px
const unsigned char epd_bitmap__a_frm27_50 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x73, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x63, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x61, 0xc0, 0xe0, 0x00, 
	0x00, 0x00, 0x00, 0x30, 0xe1, 0xf0, 0x00, 0x00, 0x00, 0x1c, 0x38, 0x73, 0xb8, 0x00, 0x00, 0x00, 
	0x3f, 0x1c, 0x33, 0x18, 0x00, 0x00, 0x00, 0x73, 0xce, 0x3b, 0x18, 0x00, 0x00, 0x00, 0x60, 0xf7, 
	0x1b, 0x18, 0x00, 0x00, 0x00, 0x70, 0x7f, 0x1f, 0x18, 0x00, 0x00, 0x00, 0x38, 0x1f, 0x8f, 0x18, 
	0x00, 0x00, 0x00, 0x1e, 0x07, 0x8f, 0x18, 0x00, 0x00, 0x00, 0x0f, 0x83, 0x8f, 0x18, 0x00, 0x00, 
	0x00, 0x03, 0xe3, 0x8f, 0x18, 0x00, 0x00, 0x00, 0x00, 0xe1, 0xc7, 0x18, 0x00, 0x00, 0x00, 0x00, 
	0x30, 0x87, 0x18, 0x00, 0x00, 0x00, 0x00, 0x38, 0x07, 0x18, 0x00, 0x00, 0x00, 0x01, 0xfc, 0x03, 
	0x18, 0x00, 0x00, 0x00, 0x03, 0xfc, 0x00, 0x18, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x18, 0x00, 
	0x00, 0x00, 0x0e, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 
	0x70, 0x60, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x60, 0xff, 0x00, 0x0e, 0x00, 0x00, 0x00, 0xe1, 0xff, 
	0x80, 0x07, 0x00, 0x00, 0x00, 0xc3, 0x81, 0xc0, 0x03, 0x00, 0x00, 0x00, 0xe7, 0x00, 0xc0, 0x01, 
	0x80, 0x00, 0x00, 0x7e, 0x00, 0xe0, 0x01, 0xc0, 0x00, 0x00, 0x7e, 0x00, 0x60, 0x00, 0xc0, 0x00, 
	0x00, 0xff, 0x00, 0x70, 0x00, 0xc0, 0x00, 0x00, 0xe3, 0x80, 0x30, 0x00, 0xc0, 0x00, 0x00, 0x61, 
	0xc0, 0x70, 0x00, 0xc0, 0x00, 0x00, 0x70, 0xc0, 0xe0, 0x00, 0xc0, 0x00, 0x00, 0x30, 0xf9, 0xc0, 
	0x00, 0xc0, 0x00, 0x00, 0x38, 0x7f, 0x80, 0x00, 0xc0, 0x00, 0x00, 0x18, 0x0f, 0x00, 0x00, 0xc0, 
	0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 
	0x0e, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x03, 0xc0, 
	0x3f, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0xf1, 0xff, 0xfc, 0xc0, 0x00, 0x00, 0x00, 0x7f, 0xe0, 0x3f, 
	0xc0, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// '_a_frm25,40', 50x50px
const unsigned char epd_bitmap__a_frm25_40 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x73, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x63, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x61, 0xc0, 0xe0, 0x00, 
	0x00, 0x00, 0x00, 0x30, 0xe1, 0xf0, 0x00, 0x00, 0x00, 0x1c, 0x38, 0x73, 0xb8, 0x00, 0x00, 0x00, 
	0x3f, 0x1c, 0x33, 0x18, 0x00, 0x00, 0x00, 0x73, 0xce, 0x3b, 0x18, 0x00, 0x00, 0x00, 0x60, 0xf7, 
	0x1b, 0x18, 0x00, 0x00, 0x00, 0x70, 0x7f, 0x1f, 0x18, 0x00, 0x00, 0x00, 0x38, 0x1f, 0x8f, 0x18, 
	0x00, 0x00, 0x00, 0x1e, 0x07, 0x8f, 0x18, 0x00, 0x00, 0x00, 0x0f, 0x83, 0x8f, 0x18, 0x00, 0x00, 
	0x00, 0x03, 0xe3, 0x8f, 0x18, 0x00, 0x00, 0x00, 0x00, 0xe1, 0xc7, 0x18, 0x00, 0x00, 0x00, 0x00, 
	0x30, 0x87, 0x18, 0x00, 0x00, 0x00, 0x00, 0x38, 0x07, 0x18, 0x00, 0x00, 0x00, 0x01, 0xfc, 0x03, 
	0x18, 0x00, 0x00, 0x00, 0x03, 0xfc, 0x00, 0x18, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x18, 0x00, 
	0x00, 0x00, 0x0e, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 
	0x70, 0x60, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x60, 0xff, 0x00, 0x0e, 0x00, 0x00, 0x00, 0xe1, 0xff, 
	0x80, 0x07, 0x00, 0x00, 0x00, 0xc3, 0x81, 0xc0, 0x03, 0x00, 0x00, 0x00, 0xe7, 0x00, 0xc0, 0x01, 
	0x80, 0x00, 0x00, 0x7e, 0x00, 0xe0, 0x01, 0xc0, 0x00, 0x00, 0x7e, 0x00, 0x60, 0x00, 0xc0, 0x00, 
	0x00, 0xff, 0x00, 0x70, 0x00, 0xc0, 0x00, 0x00, 0xe3, 0x80, 0x30, 0x00, 0xc0, 0x00, 0x00, 0x61, 
	0xc0, 0x70, 0x00, 0xc0, 0x00, 0x00, 0x70, 0xc0, 0xe0, 0x00, 0xc0, 0x00, 0x00, 0x30, 0xf9, 0xc0, 
	0x00, 0xc0, 0x00, 0x00, 0x38, 0x7f, 0x80, 0x00, 0xc0, 0x00, 0x00, 0x18, 0x0f, 0x00, 0x00, 0xc0, 
	0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 
	0x0e, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x03, 0xc0, 
	0x3f, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0xf1, 0xff, 0xfc, 0xc0, 0x00, 0x00, 0x00, 0x7f, 0xe0, 0x3f, 
	0xc0, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


//calibration variables
bool sensor_calibrated = false;
bool motor_calibrated = false;
bool scanning = false;

unsigned long speed_interval =3300;
unsigned long calibrate_time =7000;
unsigned long end_time = 0;

//potentiometer variables
const int pot_pin = A2;
int pot_value = 0;
int calibrate = 0;

//h-bridge variables
int RightForward = 5; 
int RightBack = 3; 
int LeftForward = 6;
int LeftBack = 9;
int Rmotor_speed = 0;
int Lmotor_speed = 0;
int crawl_speed = 70;

//ldr variables
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

//ultrasonic variables
const int TRIG_PIN = 7;
const int ECHO_PIN = 8;
long duration_us;
int distance_cm;

//led variables
const int left_led = 11;
const int right_led = 10;
int left_led_bright;
int right_led_bright;
bool is_blinking = false;
unsigned long previousled_millis = 0;

//buzzer declaration
const int buzzer = 12;

//interrrupt variable
#include "TimerOne.h"

const byte Motor1 = 2;
unsigned int counter1 = 0;

//speed calculation variables
float DiskSlots = 20.00;
float rotation = 0.0;
float final_distance = 0.0;
float wheel_diameter = 6.50; // Diameter of the wheel in centimeters
float wheel_circumference = wheel_diameter * PI;
bool reset = true;

//interrupt one function
void ISR_count1()
{
  counter1++; 
  //increase motor 1 counter value by 1
}

void ISR_timerone()
{
  Timer1.detachInterrupt(); //to stop timer
  rotation = (counter1 / DiskSlots) * 60.00; //calc rpm for motor 1
  final_distance += (rotation / DiskSlots) * wheel_circumference;
  counter1 = 0; //reset counter to zero
  Timer1.attachInterrupt( ISR_timerone ); //enables the timer
}
void setup() 
{
  // initialize serial monitor
  Serial.begin(9600);

//intialize pot
  pinMode(pot_pin, INPUT);

//initialize h-bridge pins
  pinMode(RightForward, OUTPUT);
  pinMode(RightBack, OUTPUT);
  pinMode(LeftForward, OUTPUT);
  pinMode(LeftBack, OUTPUT);

//initialize ldr
  pinMode(right_ldr, INPUT);
  pinMode(left_ldr, INPUT);

//intialize dht pins
  dht.begin();

  //begin button library 
  button1.begin();

//intialize ultrasonic pins
  pinMode(TRIG_PIN, OUTPUT); // Sets the trigPin as an Output
  pinMode(ECHO_PIN, INPUT); // Sets the echoPin as an Input

//check if oled is connecteed 
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) 
  {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.display();
  delay(2000); 
  display.clearDisplay();
  display.drawPixel(10, 10, SSD1306_WHITE);

//intialize led pins
  pinMode(left_led, OUTPUT);
  pinMode(right_led, OUTPUT);

//intiialize buzzer pin
  pinMode(buzzer, OUTPUT);

//count interrupts of speed sensors and attach timerone
  Timer1.initialize(1000000);
  attachInterrupt(digitalPinToInterrupt(Motor1), ISR_count1, RISING); 
  Timer1.attachInterrupt( ISR_timerone ); //enables the timer
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

//sensor calibration
unsigned long current_time = millis();
  if (sensor_calibrated == false)
  {
    Serial.println("Starting sensor calibration press button for 1 second to cancel");
    unsigned long end_time = current_time + calibrate_time; // millis function to calculate time
    do
    {
      blink_led(); // blinks leds 
      tone(buzzer, 200, 1000); // buzzer at 200Hz
      delay(500);
      noTone(buzzer);
      if(button1.pressed()) //skip calibratioon once button pressed for more than 1 second
      {
        Serial.println("Skipping calibration process");
        stop_blinking();
        break;
      }

      sensor_calibrate(); //function to calculate new value of dht readings
  
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
      Serial.println("Blink 000");
      tone(buzzer, 400, 1000);
      delay(500);
      noTone(buzzer);
      if(button1.pressed()) //skip calibratioon once button pressed for more than 1 second
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
      tone(buzzer, 600, 1000);
      delay(500);
      noTone(buzzer);
      if(button1.pressed()) //skip calibratioon once button pressed for more than 1 second
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
      tone(buzzer, 800, 1000);
      delay(200);
      blink_led();
      Rotate360();
      speed_sensor();
      Serial.println("reading LDRs");
      ldr_reading();
      Ultrasonic();
      current_time = millis();
    }while (current_time < end_time);
    Stop();
    stop_blinking();
    noTone(buzzer);
    delay(1000);
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
      speed_sensor();
      temp_hum_sensor(calibrate);
      int light_intensity = map(distance_cm, 0, 110, 170, 0);
      analogWrite(right_led, light_intensity);
      analogWrite(left_led, light_intensity);
      Serial.println("Blink 111");

      if (find_light)
      {
        prev_max_bright = thresh;
        find_light = false;
      }
      
    }
    else if (right_ldrval < thresh && left_ldrval > thresh)
    {
      Left();
      ldr_reading();
      Ultrasonic();
      speed_sensor();
      temp_hum_sensor(calibrate);
      digitalWrite(right_led, LOW);
      analogWrite(left_led, 150);
    }
    else if (right_ldrval > thresh && left_ldrval < thresh)
    {
      Right();
      ldr_reading();
      Ultrasonic();
      speed_sensor();
      temp_hum_sensor(calibrate);
      analogWrite(right_led, 150);
      digitalWrite(left_led, LOW);
      Serial.println("Blink 222");
    }
    else
    {
      Rotate360(); 
      ldr_reading(); 
      Ultrasonic();
      speed_sensor();
      temp_hum_sensor(calibrate);
      if(!find_light)
      {
        max_bright = prev_max_bright;
      }
      digitalWrite(right_led, LOW);
      digitalWrite(left_led, LOW);
    }
    
    //celebration routine
    if(distance_cm < 7 && right_ldrval >= (max_bright - 10))
    {
      tone(buzzer, 1000, 1000);
      celebration_routine();
      Rotate360();
      delay(1000);

      display.clearDisplay();
      display.drawBitmap(xx, yy,epd_bitmap__a_frm25_40,50,50, 1);
      display.display();
      delay(tt);

      display.clearDisplay();
      display.drawBitmap(xx, yy,epd_bitmap__a_frm26_50,50,50, 1);
      display.display();
      delay(tt);

      display.clearDisplay();
      display.drawBitmap(xx, yy,epd_bitmap__a_frm27_50,50,50, 1);
      display.display();
      delay(tt);
      
      Stop();
      noTone(buzzer);
      exit(0);
    }
  }
}


//functions 
int sensor_calibrate()
{
  pot_value = analogRead(pot_pin);
  calibrate = map (pot_value, 0, 1023, -10, 10);
  temp_hum_sensor(calibrate);
  
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
  Rmotor_speed = crawl_speed + calibrate;
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
  Lmotor_speed = crawl_speed + calibrate;
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

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));
  
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
  right_ldrval = analogRead(right_ldr);
  left_ldrval = analogRead(left_ldr);
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

int speed_sensor()
{
  if (reset == true)
  {
    final_distance = 0.0;
    reset = false;
    Serial.println("reset");
  }
  Serial.print("mileage - ");
  Serial.print(final_distance);
  Serial.print("cm");
  Serial.print("\t");

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 16);
  display.print("Mileage: ");
  display.print(final_distance);
  display.println("cm");
  display.display();
  delay(100);
}

void celebration_routine()
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Hurray!! I found the light");
  display.display();
}