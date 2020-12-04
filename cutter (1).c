#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#define SERVO 0
#define SERVO1 1 

int main(void)
{
    double pos=5;
    int sock = socket(PF_INET,SOCK_STREAM,0);
    printf("%d\n",sock);
    printf("AAAAA\n");
    char ip[]="192.168.0.81";
    struct sockaddr_in sockip;
    memset(&sockip,0,sizeof(sockip));
    sockip.sin_family = AF_INET;
    sockip.sin_addr.s_addr = inet_addr(ip);
    sockip.sin_port = htons(8888);
    int ttttttt = connect(sock,(struct sockaddr*)&sockip,sizeof(sockip));
    if(0==ttttttt)
    {
      while(1)
      {
    int ttttttt = connect(sock,(struct sockaddr*)&sockip,sizeof(sockip));
        char msg[100];
      int kt=read(sock,msg, sizeof(msg)-1);
      printf("%d\n",kt);
      printf("%s\n",msg);

      }
         }
    else{
      printf("B\n");
    }
    close(sock); 
    return 0;
    
}
