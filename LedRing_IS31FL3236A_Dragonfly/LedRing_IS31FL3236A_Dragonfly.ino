/* 
 * 02/23/2019 Copyright Tlera Corporation
 *  
 *  Created by Kris Winer
 *  
 *  The IS31FL3236A is a 36-channel led controller (http://www.issi.com/WW/pdf/IS31FL3236A.pdf).
 *  
 *  This sketch uses default SDA/SCL pins on the Dragonfly/Butterfly development boards
 *
 *  Library may be used freely and without limit with attribution.
 */
#include "IS31FL3236A.h"

#include <avr/pgmspace.h>

byte PWM_Gamma64[64]=
{
  0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
  0x08,0x09,0x0b,0x0d,0x0f,0x11,0x13,0x16,
  0x1a,0x1c,0x1d,0x1f,0x22,0x25,0x28,0x2e,
  0x34,0x38,0x3c,0x40,0x44,0x48,0x4b,0x4f,
  0x55,0x5a,0x5f,0x64,0x69,0x6d,0x72,0x77,
  0x7d,0x80,0x88,0x8d,0x94,0x9a,0xa0,0xa7,
  0xac,0xb0,0xb9,0xbf,0xc6,0xcb,0xcf,0xd6,
  0xe1,0xe9,0xed,0xf1,0xf6,0xfa,0xfe,0xff
};

uint8_t freq = 22;          // set PWM frequency, either 3 kHz (default) or 22 kHz allowed
uint8_t outCurrent = 0x03; // choices are 0x00 (IMax = 16 mA), 0x01 (IMax/2), 0x02 (IMax/3), and 0x03 (IMax/4)

IS31FL3236A IS31FL3236A; // instantiate IS31FL3236A class

void setup() {
  Serial.begin(115200);
  delay(4000);
  
  Wire.begin(TWI_PINS_20_21); // set master mode 
  Wire.setClock(400000); // I2C frequency at 400 kHz  
  delay(1000);
 
  IS31FL3236A.I2Cscan();

  IS31FL3236A.init(freq, outCurrent); // set PWM frequency and output current for all leds

  Serial.println("End of Setup!");

} /* end of Setup */

void loop() {

  IS31FL3236A.setRunMode();
  
  // Turn on leds slowly from 1 to 36 one at a time at 1/4 intensity
  for(uint8_t ii = 0x01; ii <=0x24; ii++)
  {
    IS31FL3236A.setPWM(ii, 64);
    IS31FL3236A.PWMUpdate();
    delay(100);
  }
  delay(1000);
  Serial.println("End of Test 1!");

  
  // Turn off leds slowly from 1 to 36 one at a time  
  for(uint8_t ii = 0x01; ii <=0x24; ii++)
  {
    IS31FL3236A.setPWM(ii, 0);
    IS31FL3236A.PWMUpdate();
    delay(100);
  }
  delay(1000);
  Serial.println("End of Test 2!");


  // Turn on leds quickly from 1 to 36 one at a time at 1/2 intensity
    for(uint8_t ii = 0x01; ii <=0x24; ii++)
  {
    IS31FL3236A.setPWM(ii, 128);
    IS31FL3236A.PWMUpdate();
    delay(50);
  }
  delay(1000);
  
  // Turn off leds quickly from 1 to 36 one at a time  
  for(uint8_t ii = 0x01; ii <=0x24; ii++)
  {
    IS31FL3236A.setPWM(ii, 0);
    IS31FL3236A.PWMUpdate();
    delay(50);
  }
  delay(1000);
  Serial.println("End of Test 3!");


    // Turn on leds very quickly from 1 to 36 one at a time at full intensity
    for(uint8_t ii = 0x01; ii <=0x24; ii++)
  {
    IS31FL3236A.setPWM(ii, 255);
    IS31FL3236A.PWMUpdate();
    delay(25);
  }
  delay(1000);
  
  // Turn off leds very quickly from 1 to 36 one at a time  
  for(uint8_t ii = 0x01; ii <=0x24; ii++)
  {
    IS31FL3236A.setPWM(ii, 0);
    IS31FL3236A.PWMUpdate();
    delay(50);
  }
  delay(1000);
  Serial.println("End of Test 4!");

  // Breath all leds slowly
  allLEDFadeOn(100);
  allLEDFadeOff(100);
  // then faster
  allLEDFadeOn(50);
  allLEDFadeOff(50);
  //then faster still
  allLEDFadeOn(10);
  allLEDFadeOff(10);
  //then smooth blink
  allLEDFadeOn(5);
  allLEDFadeOff(5);
  allLEDFadeOn(5);
  allLEDFadeOff(5);
  allLEDFadeOn(5);
  allLEDFadeOff(5);
  delay(1000);
  Serial.println("End of Test 5!");

  // Fade on and fade off leds 1 to 36 one at a time
  for(uint8_t ii = 0x01; ii <=0x24; ii++)
  {
    for (int8_t j=0; j<=63; j++) {// one LED breath rising
      IS31FL3236A.setPWM(ii, PWM_Gamma64[j]);
      IS31FL3236A.PWMUpdate();
      delay(1);
    }
    for (int8_t j=63; j>=0; j--) {// all LED breath falling
      IS31FL3236A.setPWM(ii, PWM_Gamma64[j]);
      IS31FL3236A.PWMUpdate();
      delay(3);
    }
  }
  delay(1000);
  Serial.println("End of Test 6!");
  
  mode1(); // ISSI demo
  delay(1000);
  Serial.println("End of Test 7!");


} /* end of main loop */

//Special customized functions *********************************************************

void mode1(void)  // Taken from ISSI Arduino code
{
  int8_t i = 0;
  int8_t j = 0;

  for(i=1; i<=12; i++) // First third
  {
    IS31FL3236A.setPWM((i*3),0xFF); //set  PWM  
    IS31FL3236A.PWMUpdate();        //update PWM & control registers
    delay(80);//100ms
  }
  delay(500); //keep 0.5s
  
  for(i=1; i<=12; i++) // Second third
  {
    IS31FL3236A.setPWM((i*3 - 1),0xFF); //set  PWM  
    IS31FL3236A.PWMUpdate();      //update PWM & congtrol registers
    delay(80);//100ms
  }
  delay(500); //keep 0.5s
  
  for(i=1; i<=12; i++) // Last third
  {
    IS31FL3236A.setPWM((i*3 - 2),0xFF); //set  PWM  
    IS31FL3236A.PWMUpdate();      //update PWM & congtrol registers
    delay(80);//100ms
  }
  delay(500); //keep 0.5s

  for (j=63; j>=0; j--) //all LED breath falling 
  {
     for(i=1;i<=0x24;i++)
    {
      IS31FL3236A.setPWM(i,PWM_Gamma64[j]); //set all PWM 
    }
    IS31FL3236A.PWMUpdate();      //update PWM & congtrol registers
    delay(30);//20ms
  } 
  delay(500); //keep 0.5s
}

void allLEDFadeOn(uint8_t speed) // fade speed in milliseconds
{
   for (int8_t j=0; j<=63; j++) // all LED breath rising
  {
     for(int8_t i=1; i<=0x24; i++)
    {
      IS31FL3236A.setPWM(i, PWM_Gamma64[j]); //set all PWM 
    }
    IS31FL3236A.PWMUpdate();      //update PWM & control registers
    delay(speed); 
  } 
    delay(500); //keep 0.5s
}

void allLEDFadeOff(uint8_t speed) // fade speed in milliseconds
{
   for (int8_t j=63; j>=0; j--) // all LED breath falling
  {
     for(int8_t i=1; i<=0x24; i++)
    {
      IS31FL3236A.setPWM(i, PWM_Gamma64[j]); //set all PWM 
    }
    IS31FL3236A.PWMUpdate();      //update PWM & control registers
    delay(speed); 
  } 
    delay(500); //keep 0.5s
}
