#ifndef __NETWORK_H__
#define __NETWORK_H__

extern int *detectModule();
extern int *readToOtherSystem();
extern int *writeToOtherSystem();
extern int blockModule();
extern pthread_t thread_1;
extern pthread_t thread_2;

#endif