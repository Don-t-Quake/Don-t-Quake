#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <wiringPi.h>
#include <softTone.h>
 
#define PIN 28

int endOfSystem = 0;
int threadfinish1 = 999;
int threadfinish2 = 999;
int alert[2] = { 261, 523 };

void transferSignalToBlockModule()//Networking
{
    while(threadfinish1 && threadfinish2)
    {
        if(threadfinish1 == 0 && threadfinish2 == 0)
        {
            Transfer Signal to BlockModule;
        }
    }
}

int *transferSignalToSystem(void *arg)
{
    Transfer Signal to Other System; //Networking
}

int *alert(void *arg)
{
    int i, j = 0;
    wiringPiSetup() ;
    softToneCreate(PIN) ;
    for (i = 0 ; i < 23 ; ++i)
    {
        for(j = 0; j < 2; j++)
        {
            printf("%3d\n", j) ;
            softToneWrite(PIN, alert[j]) ;
            delay(200) ;
        }
    }
    return 1;
}

int *waveDetection(void *arg)
{
    int w_Detection = 0;
    while(w_Detection == 0)
    {
        if(WaveDetection)
        {
            w_Detection = 1;
        }
    }
}

int waveSignaltoOtherSystem(void *arg)
{
    int w_Signal = 0;
    while(w_Signal == 0)
    {
        if(WaveSignaltoOtherSystem)//Networking
        {
            w_Signal = 1;
        }
    }
}

int main()
{
    pthread_t thread_1; // waveDetection, transferSignalToSystem
    pthread_t thread_2; // waveSignaltoOtherSystem, alert
    
    pthread_create(&thread_1, NULL, waveDetection, NULL);
    pthread_create(&thread_2, NULL, waveSignaltoOtherSystem, NULL);

    threadfinish1 = pthread_create(&thread_1, NULL, transferSignalToSystem, NULL);
    threadfinish2 = pthread_create(&thread_2, NULL, alert, NULL);

    transferSignalToBlockModule();

    return 0;
}