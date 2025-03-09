#include <Arduino.h>

#include <M5StickCPlus.h>
//#include <M5_DLight.h>

const int PIR_GPIO = 36;
//M5_DLight light_sensor;
uint16_t lux;
int trigger_count=0;

char info[256];

#define USB_SERIAL Serial

void setup()
{
  M5.begin();

  M5.Lcd.fillScreen(WHITE);
  delay(500);
  M5.Lcd.fillScreen(RED);
  delay(500);
  M5.Lcd.fillScreen(GREEN);
  delay(500);
  M5.Lcd.fillScreen(BLUE);
  delay(500);
  M5.Lcd.fillScreen(BLACK);
  delay(500);
/*

  USB_SERIAL.begin(115200);

  M5.Lcd.setCursor(0,0,2);
  M5.Lcd.setRotation(0);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.println("PIR TEST");
  USB_SERIAL.println("PIR TEST");

  // PIR Pin on HAT
  pinMode(PIR_GPIO, INPUT_PULLUP);

  //light_sensor.begin();

  // CONTINUOUSLY_H_RESOLUTION_MODE
  // CONTINUOUSLY_H_RESOLUTION_MODE2
  // CONTINUOUSLY_L_RESOLUTION_MODE
  // ONE_TIME_H_RESOLUTION_MODE
  // ONE_TIME_H_RESOLUTION_MODE2
  // ONE_TIME_L_RESOLUTION_MODE
//  light_sensor.setMode(CONTINUOUSLY_H_RESOLUTION_MODE);
*/
}

void loop()
{
  /*
  int triggered=0;
//  lux = light_sensor.getLUX();
//  triggered = digitalRead(36);
  triggered = 1;
  lux = 312;

  trigger_count += triggered;

  M5.Lcd.setCursor(60, 0, 4);
  sprintf(info, "Triggered: %d\nLux: %d\n",trigger_count,lux);
  M5.Lcd.println(info);

  sprintf(info, "%d,%d,%d",triggered,trigger_count,lux);

  USB_SERIAL.println(info);
  delay(500);
  */
}
