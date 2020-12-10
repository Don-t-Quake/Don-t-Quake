#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "header/network.h"
#include "header/alert.h"
 
#define PIN 28

int endOfSystem = 0;
int threadfinish1 = 999;
int threadfinish2 = 999;

int main()
{
    int return_thrd1;    
    int return_thrd2;
    int return_EOS;

    pthread_t thread_1; // etc
    pthread_t thread_2; // OtherSystem
   
    pthread_create(&thread_1, NULL, detectModule, NULL);
    //pthread_create(&thread_2, NULL, readToOtherSystem, NULL);

    pthread_join(thread_1, (void **)&return_thrd1);
    //pthread_join(thread_2, (void **)&return_thrd2);

    while(1)
    {
        if(return_thrd1 == 0 || return_thrd2 == 0)
        {
            printf("in if\n");
            blockModule();
            //pthread_create(&thread_2, NULL, writeToOtherSystem, NULL);
            pthread_create(&thread_1, NULL, main_lcd, NULL);
            return_EOS = main_buzzer();
            printf("%d\n", return_EOS);
            blockModule();
            return 1;
        }
    }
    return 0;
}