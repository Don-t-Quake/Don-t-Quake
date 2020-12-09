#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include "pwd.h"

#define SERVO 0
#define SERVO1 1


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
