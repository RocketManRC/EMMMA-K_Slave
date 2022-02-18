/*
  This is the code for the EMMMA-K "Slave" processor. When the Master asks
  it sends the state of the remaining 6 note keys and another touch pin
  on the back of the case used to enable pitch bends.

  Updated on December 2, 2020 for EMMMA-K-v2 to add pin 1 - now 8 pins from 7. Also added
  a second byte to send the pushbuttons on pins 2 and 3 (pin 4 used as the ground reference).
*/

#include <touchablePin.h>

touchablePin pins[8];
uint8_t pinNumbers[] = {18,15,19,16,22,17,0,1};

void setup() 
{ 
  Serial2.begin(115200);

  for(int i = 0; i < 8; i++)
      pins[i].setPin(pinNumbers[i]);

  //pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
}

void loop() 
{
  if(Serial2.read() == 0xA5)
  {
    uint8_t p = 0;

    for(int i = 0; i < 8; i++)
    {
      if(pins[i].isTouched())
      {
        p |= (1 << i);
      }
    }

    Serial2.write(p);

    uint8_t p2 = 0;

    if(!digitalRead(3))
      p2 |= 2;

    if(!digitalRead(4))
      p2 |= 1;

    Serial2.write(p2);
  }
}
