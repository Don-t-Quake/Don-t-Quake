#include <stdio.h>
#include <stdlib.h>

#include <wiringPi.h>
#include <softTone.h>


int alert[2] = { 261, 523 };
int main()
{
    int i, j = 0;
    wiringPiSetup() ;
    softToneCreate(28) ;
    for (i = 0 ; i < 20 ; ++i)
    {
        for(j = 0; j < 2; j++)
        {
            printf("%3d\n", j) ;
            softToneWrite(28, alert[j]) ;
            delay(200) ;
        }
    }
    return 1;
}