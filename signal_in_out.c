#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int endOfSystem = 0;
int threadfinish1 = 999;
int threadfinish2 = 999;

void transferSignalToBlockModule()
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
    Transfer Signal to Other System;
}

int *alert(void *arg)
{
    Speaker Sensor Activation;
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
        if(WaveSignaltoOtherSystem)
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
