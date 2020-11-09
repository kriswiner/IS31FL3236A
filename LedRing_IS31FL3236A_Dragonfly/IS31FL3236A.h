/* 06/16/2017 Copyright Tlera Corporation
 *  
 *  Created by Kris Winer
 *  
 This sketch uses SDA/SCL on pins 42/43 (back pads), respectively, and it uses the Dragonfly STM32L476RE Breakout Board.
 The BME280 is a simple but high resolution pressure/humidity/temperature sensor, which can be used in its high resolution
 mode but with power consumption of 20 microAmp, or in a lower resolution mode with power consumption of
 only 1 microAmp. The choice will depend on the application.
 
 Library may be used freely and without limit with attribution.
 
*/
  
#ifndef IS31FL3236A_h
#define IS31FL3236A_h

#include "Arduino.h"
#include <Wire.h>

/* IS31FL3236A registers
*  
*/
#define IS31FL3236A_SD      0x00

#define IS31FL3236A_PWM01   0x01
#define IS31FL3236A_PWM02   0x02
#define IS31FL3236A_PWM03   0x03
#define IS31FL3236A_PWM04   0x04
#define IS31FL3236A_PWM05   0x05
#define IS31FL3236A_PWM06   0x06
#define IS31FL3236A_PWM07   0x07
#define IS31FL3236A_PWM08   0x08
#define IS31FL3236A_PWM09   0x09
#define IS31FL3236A_PWM10   0x0A
#define IS31FL3236A_PWM11   0x0B
#define IS31FL3236A_PWM12   0x0C
#define IS31FL3236A_PWM13   0x0D
#define IS31FL3236A_PWM14   0x0E
#define IS31FL3236A_PWM15   0x0F
#define IS31FL3236A_PWM16   0x10
#define IS31FL3236A_PWM17   0x11
#define IS31FL3236A_PWM18   0x12
#define IS31FL3236A_PWM19   0x13
#define IS31FL3236A_PWM20   0x14
#define IS31FL3236A_PWM21   0x15
#define IS31FL3236A_PWM22   0x16
#define IS31FL3236A_PWM23   0x17
#define IS31FL3236A_PWM24   0x18
#define IS31FL3236A_PWM25   0x19
#define IS31FL3236A_PWM26   0x1A
#define IS31FL3236A_PWM27   0x1B
#define IS31FL3236A_PWM28   0x1C
#define IS31FL3236A_PWM29   0x1D
#define IS31FL3236A_PWM30   0x1E
#define IS31FL3236A_PWM31   0x1F
#define IS31FL3236A_PWM32   0x20
#define IS31FL3236A_PWM33   0x21
#define IS31FL3236A_PWM34   0x22
#define IS31FL3236A_PWM35   0x23
#define IS31FL3236A_PWM36   0x24

#define IS31FL3236A_UPDATE  0x25

#define IS31FL3236A_LED01   0x26
#define IS31FL3236A_LED02   0x27
#define IS31FL3236A_LED03   0x28
#define IS31FL3236A_LED04   0x29
#define IS31FL3236A_LED05   0x2A
#define IS31FL3236A_LED06   0x2B
#define IS31FL3236A_LED07   0x2C
#define IS31FL3236A_LED08   0x2D
#define IS31FL3236A_LED09   0x2E
#define IS31FL3236A_LED10   0x2F
#define IS31FL3236A_LED11   0x30
#define IS31FL3236A_LED12   0x31
#define IS31FL3236A_LED13   0x32
#define IS31FL3236A_LED14   0x33
#define IS31FL3236A_LED15   0x34
#define IS31FL3236A_LED16   0x35
#define IS31FL3236A_LED17   0x36
#define IS31FL3236A_LED18   0x37
#define IS31FL3236A_LED19   0x38
#define IS31FL3236A_LED20   0x39
#define IS31FL3236A_LED21   0x3A
#define IS31FL3236A_LED22   0x3B
#define IS31FL3236A_LED23   0x3C
#define IS31FL3236A_LED24   0x3D
#define IS31FL3236A_LED25   0x3E
#define IS31FL3236A_LED26   0x3F
#define IS31FL3236A_LED27   0x40
#define IS31FL3236A_LED28   0x41
#define IS31FL3236A_LED29   0x42
#define IS31FL3236A_LED30   0x43
#define IS31FL3236A_LED31   0x44
#define IS31FL3236A_LED32   0x45
#define IS31FL3236A_LED33   0x46
#define IS31FL3236A_LED34   0x47
#define IS31FL3236A_LED35   0x48
#define IS31FL3236A_LED36   0x49

#define IS31FL3236A_CTRL    0x4A
#define IS31FL3236A_FREQ    0x4B
#define IS31FL3236A_RESET   0x4F

#define IS31FL3236A_ADDRESS 0x3C // when AD = LOW (default)


class IS31FL3236A
{
  public: 
  IS31FL3236A();
  void reset();
  void powerDown();
  void powerUp();
  void init(uint8_t freq, uint8_t outCurrent);
  void setPWM(uint8_t channel, uint8_t PWMLevel);
  void setFreq(uint8_t freq);
  void setRunMode();
  void setStopMode();
  void setLEDOnOff(uint8_t channel, uint8_t OnOff);
  void PWMUpdate();
  void I2Cscan();
  void writeByte(uint8_t address, uint8_t subAddress, uint8_t data);
  private:
  uint8_t _outCurrent;
 };

#endif
