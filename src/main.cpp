#include <Arduino.h>

#include <M5StickCPlus.h>
#include <M5_DLight.h>

const bool test_with_stubbed_sensors=true;

const int PIR_GPIO = 36;
M5_DLight light_sensor;

uint16_t lux=0, old_lux=0;
const uint16_t lux_threshold=10000;
bool lux_threshold_exceeded=false;
bool old_lux_threshold_exceeded=true;
bool lux_change=false;

int pir_trigger_count=0,old_pir_trigger_count=0,pir_triggered=0,old_s=-1;

uint32_t next_pir_trigger = 0;
const int time_between_pir_triggers = 2000;

uint32_t next_lux_read = 0;
const int time_between_lux_reads = 250;

char info[256];

#define USB_SERIAL Serial

void setup()
{
  M5.begin();

  USB_SERIAL.begin(115200);

  M5.Lcd.setRotation(1);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextWrap(false);
  M5.Lcd.setCursor(0, 0, 4);

  pinMode(PIR_GPIO, INPUT_PULLUP);

  light_sensor.begin();

  // CONTINUOUSLY_H_RESOLUTION_MODE
  // CONTINUOUSLY_H_RESOLUTION_MODE2
  // CONTINUOUSLY_L_RESOLUTION_MODE
  // ONE_TIME_H_RESOLUTION_MODE
  // ONE_TIME_H_RESOLUTION_MODE2
  // ONE_TIME_L_RESOLUTION_MODE
  light_sensor.setMode(CONTINUOUSLY_H_RESOLUTION_MODE);
}

void loop()
{
  uint32_t now = millis();

  if (now > next_pir_trigger)
  {
    if (test_with_stubbed_sensors)
      pir_triggered = 1;
    else
      pir_triggered = digitalRead(36);

    if (pir_triggered)
    {
      pir_trigger_count++;
      next_pir_trigger = now + time_between_pir_triggers;
    }
  }
  else
  {
    pir_triggered=0;
  }

  if (now > next_lux_read)
  {
    if (test_with_stubbed_sensors)
      lux = random(0,65535);
    else
      lux = light_sensor.getLUX();

    lux_threshold_exceeded = (lux > lux_threshold);
    next_lux_read = now + time_between_lux_reads;    
  }

  int32_t s = (now / 1000 ) % 60;
  int32_t m = (now / 60000 ) % 60;
  int32_t h = (now / 3600000 );

  if (pir_trigger_count != old_pir_trigger_count)
  {
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.setTextColor(TFT_GREEN,TFT_BLACK);
    sprintf(info, "T.%d",pir_trigger_count);
    M5.Lcd.print(info);
    old_pir_trigger_count = pir_trigger_count;
  }

  if (old_lux != lux)
  {
    M5.Lcd.setCursor(0, 44);
    M5.Lcd.setTextColor(TFT_YELLOW, TFT_BLACK);
    sprintf(info, "Lux.%d            ", lux);
    M5.Lcd.print(info);

    lux_change = (lux >  lux_threshold && !old_lux_threshold_exceeded ||
                  lux <= lux_threshold &&  old_lux_threshold_exceeded);
                  
    old_lux = lux;
    old_lux_threshold_exceeded = lux_threshold_exceeded;
  }

  if (old_s != s)
  {
    M5.Lcd.setCursor(0, 93);
    M5.Lcd.setTextColor(TFT_CYAN, TFT_BLACK);
    sprintf(info, "%02d:%02d:%02d",h, m, s);
    M5.Lcd.print(info);
    old_s = s;
  }

  if (lux_change || pir_triggered)
  {
    sprintf(info, "%d,%d,%d,%02d:%02d:%02d",pir_triggered,pir_trigger_count,lux,h,m,s);
    USB_SERIAL.println(info);

    lux_change = false;
    pir_triggered = 0;
  }
}
