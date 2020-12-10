#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../header/network.h"
#include "../header/alert.h"
 
#define PIN 28

int endOfSystem = 0;
int threadfinish1 = 999;
int threadfinish2 = 999;

int main()
{
    int return_EOS;

    pthread_t thread_1;
    pthread_t thread_2;
   
    readToOtherSystem();

    pthread_create(&thread_2, NULL, writeToOtherSystem, NULL);
    pthread_create(&thread_1, NULL, main_lcd, NULL);
    return_EOS = main_buzzer();
    printf("%d\n", return_EOS);
    blockModule();
    return 0;
}