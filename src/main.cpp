/*
  This is the code for the EMMMA-K "Slave" processor. When the Master asks
  it sends the state of the remaining 6 note keys and another touch pin
  on the back of the case used to enable pitch bends.
*/

#include <touchablePin.h>

touchablePin pins[7];
uint8_t pinNumbers[] = {18,15,19,16,22,17,0};

void setup() 
{ 
  Serial2.begin(115200);

  for(int i = 0; i < 7; i++)
      pins[i].setPin(pinNumbers[i]);
}

void loop() 
{
  if(Serial2.read() == 0xA5)
  {
    uint8_t p = 0;

    for(int i = 0; i < 7; i++)
    {
      if(pins[i].isTouched())
      {
        p |= (1 << i);
      }
    }

    Serial2.write(p);
  }
}
