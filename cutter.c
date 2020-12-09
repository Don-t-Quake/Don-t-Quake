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
#define DIRECTION_MAX 45


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
    static const char s_unenable_str[] = "0";
    static const char s_enable_str[] = "1";
    char path[DIRECTION_MAX];
    int fd;
    snprintf(path, DIRECTION_MAX, "/sys/class/pwm/pwmchip0/pwm%d/enable", pin);
    fd = open(path, O_WRONLY);
    if (-1 == fd)
    {
        fprintf(stderr, "Failed to open in enable!\n");
        return -1;
    }
    write(fd, s_unenable_str, strlen(s_unenable_str));
    close(fd);
    fd = open(path, O_WRONLY);
    if (-1 == fd)
    {
        fprintf(stderr, "Failed to open in enable!\n");
        return -1;
    }
    write(fd, s_enable_str, strlen(s_enable_str));
    close(fd);
    return (0);
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
    char s_values_str[VALUE_MAX];
    int fd, byte;
    snprintf(path, VALUE_MAX, "/sys/class/pwm/pwmchip0/pwm%d/duty_cycle", pin);
    fd = open(path, O_WRONLY);
    if (-1 == fd)
    {
        fprintf(stderr, "Failed to open in duty_cycle!\n");
        return (-1);
    }
    byte = snprintf(s_values_str, 10, "%d", value);
    if (-1 == write(fd, s_values_str, byte))
    {
        fprintf(stderr, "Failed to write value! in duty_cycle\n");
        close(fd);
        return (-1);
    }
    close(fd);
    return (0);
}


static int PWMExport(int pin)
{

    char buffer[BUFFER_MAX];
    int bytes_written;
    int fd;
    fd = open("/sys/class/pwm/pwmchip0/export", O_WRONLY);
    if (-1 == fd)
    {
        fprintf(stderr, "Failed to open in export!\n");
        return (-1);
    }
    bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
    write(fd, buffer, bytes_written);
    close(fd);
    sleep(1);
    return (0);
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
  PWMWriteDutyCycle(0,0);
  PWMEnable(0);
  pos=17.5;
  PWMWriteDutyCycle(0,pos);
  usleep(3000);
  pos=5;
  PWMWriteDutyCycle(0,pos);
  usleep(1000);
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
