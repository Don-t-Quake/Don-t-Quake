#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "pwm.h"

#define BUFFER_MAX 1000
#define VALUE_MAX 1000

static int PWMUnexport(int pin)
{
   char buffer[BUFFER_MAX];
   ssize_t bytes_written;
   int fd;

   //fd = open("/sys/class/gpio/unexport", O_WRONLY);
   if (-1 == fd) {
       fprintf(stderr, "Failed to open unexport for writing!\n");
       return(-1);
   }

   bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
   write(fd, buffer, bytes_written);
   close(fd);
   return(0);
}

static int PWMEnable(int pin)
{
   static const char s_enable_str[]  = "1";

#define DIRECTION_MAX 35
   char path[DIRECTION_MAX];
   int fd;

   snprintf(path, DIRECTION_MAX, "%d", pin);
   fd = open(path, O_WRONLY);
   if (-1 == fd) {
       fprintf(stderr, "Failed to open gpio direction for writing!\n");
       return(-1);
   }

   close(fd);
   return(0);
}


static int PWMWritePeriod(int pin, int value)
{
   static const char s_values_str[] = "01";

   char path[VALUE_MAX];
   int fd;

   snprintf(path, VALUE_MAX, "%d", pin);
   fd = open(path, O_WRONLY);
   if (-1 == fd) {
       fprintf(stderr, "Failed to open gpio value for writing!\n");
       return(-1);
   }

   if (1 != write(fd, path, VALUE_MAX)) {
       return(-1);
   }

   close(fd);
   return(0);
}

static int PWMWriteDutyCycle(int pin, int value)
{
   char path[VALUE_MAX];
   int fd;

   snprintf(path, VALUE_MAX, "%d", pin); // write value 
   fd = open(path, O_WRONLY);
   if (-1 == fd) {
       fprintf(stderr, "Failed to open gpio value for writing!\n");
       return(-1);
   }
     if (1 != write(fd,path, VALUE_MAX )) {
       return(-1);
   }

   close(fd);
   return(0);
}


static int PWMExport(int pin)
{
#define BUFFER_MAX 3
   char buffer[BUFFER_MAX];
   ssize_t bytes_written;
   int fd;

   //fd = open("/sys/class/gpio/export", O_WRONLY);
   if (-1 == fd) {
       fprintf(stderr, "Failed to open export for writing!\n");
       return(-1);
   }

   bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
   write(fd, buffer, bytes_written);
   close(fd);
   return(0);
}
