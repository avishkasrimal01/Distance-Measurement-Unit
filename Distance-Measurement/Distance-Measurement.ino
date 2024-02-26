//include libraries
#include <Adafruit_TFTLCD.h> 
#include <Adafruit_GFX.h>    
#include <TouchScreen.h>

//define pins of the display
#define LCD_CS A3 
#define LCD_CD A2 
#define LCD_WR A1 
#define LCD_RD A0 
#define LCD_RESET A4

//calibration of the display
#define TS_MINX 122
#define TS_MINY 111
#define TS_MAXX 942
#define TS_MAXY 890

//deifne pins of the touch screen
#define YP A3 
#define XM A2
#define YM 9
#define XP 8

//define colors using for the display
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

//define pin using by library
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

//Ultrasonic Sensor
const int VCC = 13;
const int trigPin = 11;
const int echoPin = 12;

//Define Variables
long duration = 0;
long distance = 0;
long distanceOld = 0;

void setup(void){
  //initialize setup
  tft.reset();
  uint16_t identifier = tft.readID();
  tft.begin(identifier);
  
  //setting background of the display
  //tft.setRotation(1);   //rotation of the display
  tft.fillScreen(BLACK);  //color of the display
  tft.setTextWrap(true);  

  //define pin modes
  pinMode(VCC, OUTPUT);   
  pinMode(trigPin, OUTPUT); //sets the trigPin as an Output
  pinMode(echoPin, INPUT);  //sets the echoPin as an Input
  digitalWrite(VCC, HIGH);  // +5V - Pin 13 as VCC

  tft.setTextSize(2);       //text size
  tft.setTextColor(YELLOW); //text color
  tft.setCursor(70,15);      //point of the text
  tft.print("Distance\n\n    Measurement\n\n        Unit"); //print the text
  
  tft.setTextSize(2);
  tft.setTextColor(RED);
  tft.setCursor(30,280);
  tft.print(" Avishka Srimal");
}

void loop(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034/2;

  if(distance!=distanceOld){
    getDistance(distanceOld, BLACK);
    getDistance(distance, WHITE);
  }

  distanceOld = distance;
  delay(1000);
}

void getDistance(long distance, int color){

  int x;
  if(distance < 10 ) x=41;
  else if((distance < 100) || (distance >= 1000)) x=28;
  else x=19;

  tft.setCursor(x, 135);
  tft.setTextColor(color);
  tft.setTextSize(6);

  if(distance < 1000) {
     tft.print(distance);
     tft.print(" cm");
  }
  else {
  tft.print(".....");
  }
}
