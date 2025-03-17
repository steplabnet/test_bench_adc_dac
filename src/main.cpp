#include <Arduino.h>
#include <Wire.h>
#include <ADS1115_WE.h>

// put function declarations here:

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.setPins(6, 7); //(9,10)
  Wire.begin();
}

void loop()
{
  byte error, address;
  int nDevices = 0;

  for (address = 1; address < 127; address++)
  {
    // Send a test write to the address to see if a device responds
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      Serial.println(address, HEX);
      nDevices++;
    }
  }

  if (nDevices == 0)
  {
    Serial.println("No I2C devices found.");
  }

  delay(5000); // Wait 5 seconds before scanning again (optional)
}
