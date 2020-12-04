#include <stdio.h>
#include <errno.h>
#include <string.h>
 
#include <wiringPi.h>
#include <softTone.h>
 
#define PIN 28
 
int scale [23] = { 659, 659, 0, 659, 0, 523, 659, 0, 784, 0,0,0, 392, 0,0,0, 523, 0,0, 392, 0,0,330 } ;

//int alert[2] = { 261, 294, 329, 349, 392, 440, 493, 523 };

int meteor1[16] = { 440, 440, 493, 493, 329, 329, 261, 261, 440, 440, 493, 493, 329, 329, 261, 261 };

int meteor2[28] = {329, 294, 329, 329, 329, 329, 294, 294, 294, 294, 392, 392, 349, 392, 294, 294, 294, 294, 294, 294, 294, 294, 329, 294, 392, 392, 349, 392};
int main ()
{
  int i ;
  wiringPiSetup () ;
  softToneCreate (PIN) ;
  for (i = 0 ; i < 16 ; ++i)
    {
      printf ("%3d\n", i) ;
      softToneWrite (PIN, meteor1[i]) ;
      delay (200) ;
    }
    for (i = 0 ; i < 28 ; ++i)
    {
      printf ("%3d\n", i) ;
      softToneWrite (PIN, meteor2[i]) ;
    }
}