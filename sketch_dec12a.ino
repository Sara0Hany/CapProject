
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define SENSOR_PIN 12 // ESP32 pin GPIO18 connected to OUT pin of IR obstacle avoidance sensor
int lcdColumns = 21;
int lcdRows = 22;

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

int lastState = HIGH;  // the previous state from the input pin
int currentState;      // the current reading from the input pin

void setup() {
  // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();

  pinMode(SENSOR_PIN, INPUT);
  
}

void loop() {
  // read the state of the the input pin:
  int state = digitalRead(SENSOR_PIN);
  if (state == LOW)
   lcd.print(" obstacle ");
  
  else 
   lcd.print("no obstacle ");

  delay(500);
  // save the the last state
  lastState = currentState;
}