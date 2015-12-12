#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OzOLED.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

int inputPin     = 11;
int resetPin     = 12;

int val          =  0;
long int count   =  0;
int current      =  0;
int previous     =  0;



static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

void setup()   {           
  
  Serial.begin(9600);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(1000);
  display.clearDisplay();

  pinMode (inputPin,INPUT);  
  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
}

void loop() {
  
      val = digitalRead(inputPin);
      if (val == HIGH) {
        current = 1;
      }
      else { current = 0; }

      if (current != previous && current == 1) {
        count +=1;
      }  

  long int time  = millis()/1000;

  int seconds    = time    % 60;
  int minutes    = time/60 % 60;
  int hours      = time/3600;
  
  float stdev    = sqrt(count)/time;
  float average  = (float)count/time;  

  display.clearDisplay();  
  String currentcountstr  = "Total Count:";
  String currentcount     = currentcountstr + " " + count ;
  String runtimestr       = "Run Time   ";   
  String runtime          = runtimestr + hours + ":" + minutes + ":" + seconds;
  String ratestr          = "Rate:  ";
  String pm               = "+/-";

  char tmp[15];
  dtostrf(average,1,2,tmp);
  char tmp2[15];
  dtostrf(stdev,1,2,tmp2);
  
  String rate = ratestr + tmp + " " + pm + " " + tmp2;

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(currentcount);
  display.println(runtime);
  display.println("");
  display.println(rate);
  display.display();
  
  previous = current;
   
}



