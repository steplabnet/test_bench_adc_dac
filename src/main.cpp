#include <Arduino.h>
#include <Wire.h>
#include <ADS1115_WE.h>
#include <Adafruit_MCP4725.h>

// put function declarations here:
#define ADC1_ADDRESS 0x48
#define DAC_ADDRESS 0x60

Adafruit_MCP4725 dac;
ADS1115_WE adc1 = ADS1115_WE(ADC1_ADDRESS);

float readChannel(ADS1115_MUX channel);

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.setPins(6, 7); //(9,10)
  Wire.begin();

  if (!adc1.init())
  {
    Serial.println("ADS1115 not connected");
  }
  adc1.setVoltageRange_mV(ADS1115_RANGE_6144); // comment line/change parameter to change range
  adc1.setMeasureMode(ADS1115_CONTINUOUS);     // comment line/change parameter to change mode
}

void loop()
{
  float voltage = 0.0;

  Serial.print("0: ");
  voltage = readChannel(ADS1115_COMP_0_GND);
  Serial.print(voltage);

  Serial.print(",   1: ");
  voltage = readChannel(ADS1115_COMP_1_GND);
  Serial.print(voltage);

  Serial.print(",   2: ");
  voltage = readChannel(ADS1115_COMP_2_GND);
  Serial.print(voltage);

  Serial.print(",   3: ");
  voltage = readChannel(ADS1115_COMP_3_GND);
  Serial.println(voltage);

  delay(1000);
}

float readChannel(ADS1115_MUX channel)
{
  float voltage = 0.0;
  adc1.setCompareChannels(channel);
  voltage = adc1.getResult_V(); // alternative: getResult_mV for Millivolt
  return voltage;
}