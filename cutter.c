#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define SERVO 0
#define SERVO1 1


#define BUFFER_MAX 1000
#define VALUE_MAX 1000


static int PWMUnexport(int pin)
{
   char buffer[BUFFER_MAX];
   ssize_t bytes_written;
   int fd;

   fd = open("/sys/class/pwm/pwmchip0/unexport", O_WRONLY);
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

   snprintf(path, DIRECTION_MAX, "/sys/class/pwm/pwmchip0/pwm%d/enable", pin);
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
    char s_values_str[VALUE_MAX];
    char path[VALUE_MAX];
    int fd, byte;
    snprintf(path, VALUE_MAX, "/sys/class/pwm/pwmchip0/pwm%d/period", pin);
    fd = open(path, O_WRONLY);
    if (-1 == fd)
    {
        fprintf(stderr, "Failed to open in period!\n");
        return (-1);
    }
    byte = snprintf(s_values_str, 10, "%d", value);
    if (-1 == write(fd, s_values_str, byte))
    {
        fprintf(stderr, "Failed to write value in period!\n");
        close(fd);
        return (-1);
    }
    close(fd);
    return (0);
}

static int PWMWriteDutyCycle(int pin, int value)
{
   char path[VALUE_MAX];
   int fd;

   snprintf(path, VALUE_MAX, "/sys/class/pwm/pwmchip0/pwm%d/duty_cycle", pin); // write value 
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

   fd = open("/sys/class/pwm/pwmchip0/export", O_WRONLY);
   if (-1 == fd) {
       fprintf(stderr, "Failed to open export for writing!\n");
       return(-1);
   }

   bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
   write(fd, buffer, bytes_written);
   close(fd);
   return(0);
}

int main(void)
{
  double pos = 5;
  int ttt;
  int sock = socket(PF_INET, SOCK_STREAM, 0);
  printf("%d\n", sock);
  printf("AAAAA\n");
  char ip[] = "192.168.0.82";
  struct sockaddr_in sockip;
  memset(&sockip, 0, sizeof(sockip));
  sockip.sin_family = AF_INET;
  sockip.sin_addr.s_addr = inet_addr(ip);
  sockip.sin_port = htons(8888);
  do{
    ttt = connect(sock, (struct sockaddr *)&sockip, sizeof(sockip));
    printf("ttt=%d\n",ttt);
  }while(ttt==-1);
  printf("%d\n",ttt);
  char msg[100];
  int kt;
  while(1)
  {
    kt = read(sock, msg, sizeof(msg) - 1);
    printf("%d\n",kt);
    printf("%s\n",msg);
    if(!strcmp("1",msg))
    {
      break;
    }
    //    if (!strcmp("1", msg))
    //    {
    //      printf("IIIIIII");
    //    }
    //    else
    //    {
    //      printf("B\n");
    //    }

  }
  close(sock);

  PWMExport(0);
  PWMWritePeriod(0,200);
  pos=17.5;
  PWMWriteDutyCycle(0,pos);
  PWMEnable(0);
  // softPwmCreate(SERVO, 0, 200);
  // softPwmCreate(SERVO1, 0, 200);
  // softPwmWrite(SERVO,pos);
  // delay(1000);
  // softPwmWrite(SERVO,pos);
  // delay(1000);
//  pos=5;
//  softPwmWrite(SERVO,pos);
//  delay(1000);

  // pos=5;
  // softPwmWrite(SERVO1,pos);
  // delay(1000);
  // pos=17.5;
  // softPwmWrite(SERVO1,pos);
  // delay(1000);
//  pos=5;
//  softPwmWrite(SERVO1,pos);
//  delay(1000);

  return 0;
}
