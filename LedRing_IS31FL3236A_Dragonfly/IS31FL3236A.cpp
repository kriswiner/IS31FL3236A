#include "IS31FL3236A.h"


IS31FL3236A::IS31FL3236A(){
  }


  void IS31FL3236A::reset() // return to default registers/conditions
{
  writeByte(IS31FL3236A_ADDRESS, IS31FL3236A_RESET, 0x00);
}


  void IS31FL3236A::powerDown()
  {
  writeByte(IS31FL3236A_ADDRESS, IS31FL3236A_SD, 0x00); //clear bit 0 to shut down
  }


  void IS31FL3236A::powerUp()
  {
  writeByte(IS31FL3236A_ADDRESS, IS31FL3236A_SD, 0x01); //set bit 0 to enable
  }


  void IS31FL3236A::init(uint8_t freq, uint8_t outCurrent)
 {

  for(uint8_t ii = 0x26; ii <= 0x49; ii++)
  {
    writeByte(IS31FL3236A_ADDRESS, ii, (outCurrent << 1) | 0x01);  // enable all leds
  }

  for(uint8_t ii = 0x01; ii <= 0x24; ii++)
  {
    writeByte(IS31FL3236A_ADDRESS, ii, 0x00);  // set PWM for all leds to 0
  }
    
  _outCurrent = outCurrent;
  writeByte(IS31FL3236A_ADDRESS, IS31FL3236A_UPDATE, 0x00); // update led, PWM and control registers
  writeByte(IS31FL3236A_ADDRESS, IS31FL3236A_SD, 0x01); //set bit 0 to enable normal operation
 }


 void IS31FL3236A::setPWM(uint8_t channel, uint8_t PWMLevel)
 {
  writeByte(IS31FL3236A_ADDRESS, channel, PWMLevel);  // set PWM level (0 - 255) for specified led channel
 }


  void IS31FL3236A::setFreq(uint8_t freq)
 {
  if(freq == 3) {
    writeByte(IS31FL3236A_ADDRESS, IS31FL3236A_FREQ, 0x00);  // set PWM frequency to 3 kHz (default)
  } 
  else if(freq == 22) {
    writeByte(IS31FL3236A_ADDRESS, IS31FL3236A_FREQ, 0x01);  // set PWM frequency to 22 kHz
  }
 }


 void IS31FL3236A::setRunMode()
 {
  writeByte(IS31FL3236A_ADDRESS, IS31FL3236A_CTRL, 0x00);  // set device in normal run mode (default)
 }


 void IS31FL3236A::setStopMode()
 {
  writeByte(IS31FL3236A_ADDRESS, IS31FL3236A_CTRL, 0x01);  // shutdown all leds
 }


 void IS31FL3236A::setLEDOnOff(uint8_t channel, uint8_t OnOff)
 {
    if(OnOff == 0x00 || OnOff == 0x01)
    {
      writeByte(IS31FL3236A_ADDRESS, channel, OnOff);  // enable leds
    }
    else
    {
      Serial.println("Illegal LED OnOff value selected!");
    }
 }


  void IS31FL3236A::PWMUpdate()
{
  writeByte(IS31FL3236A_ADDRESS, IS31FL3236A_UPDATE, 0x00); // update led array
}


// I2C scan function
void IS31FL3236A::I2Cscan()
{
// scan for i2c devices
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for(address = 1; address < 127; address++ ) 
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmission to see if
    // a device did acknowledge to the address.
//    Wire.beginTransmission(address);
//    error = Wire.endTransmission();
      error = Wire.transfer(address, NULL, 0, NULL, 0);
      
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error==4) 
    {
      Serial.print("Unknown error at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");  
}


// I2C read/write functions  

        void IS31FL3236A::writeByte(uint8_t address, uint8_t subAddress, uint8_t data) {
        Wire.beginTransmission(address); // starts transaction
        Wire.write(subAddress); // sends register address
        Wire.write(data      ); // sends data
        Wire.endTransmission(); // stop transmitting
        }
