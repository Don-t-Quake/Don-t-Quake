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

static int
PWMExport(int pwmnum)
{
#define BUFFER_MAX 3
	char buffer[BUFFER_MAX];
	int bytes_written;
	int fd;

	fd = open("/sys/class/pwm/pwmchip0/export", O_WRONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open in export!\n");
		return(-1);
	}
	bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pwmnum);
	write(fd, buffer, bytes_written);
	close(fd);
	return(0);
}
static int
PWMUnExport(int pwmnum)
{
#define BUFFER_MAX 3
	char buffer[BUFFER_MAX];
	int bytes_written;
	int fd;

	fd = open("/sys/class/pwm/pwmchip0/unexport", O_WRONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open in unexport!\n");
		return(-1);
	}

	bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pwmnum);
	write(fd, buffer, bytes_written);
	close(fd);
}
static int
PWMUnable(int pwmnum)
{
	static const char s_unenable_str[] = "0";
	static const char s_enable_str[]  = "1";

#define DIRECTION_MAX 45
	char path[DIRECTION_MAX];
	int fd;

	snprintf(path, DIRECTION_MAX, "/sys/class/pwm/pwmchip0/pwm%d/enable", pwmnum);
	fd = open(path, O_WRONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open in enable!\n");
		return -1;
	}

	write(fd,s_unenable_str,strlen(s_unenable_str));
	close(fd);
}
static int
PWMEnable(int pwmnum)
{
	static const char s_unenable_str[] = "0";
	static const char s_enable_str[]  = "1";

#define DIRECTION_MAX 45
	char path[DIRECTION_MAX];
	int fd;

	snprintf(path, DIRECTION_MAX, "/sys/class/pwm/pwmchip0/pwm%d/enable", pwmnum);
	fd = open(path, O_WRONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open in enable!\n");
		return -1;
	}

	write(fd,s_unenable_str,strlen(s_unenable_str));
	close(fd);

	fd = open(path, O_WRONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open in enable!\n");
		return -1;
	}


	write(fd,s_enable_str,strlen(s_enable_str));
	close(fd);
	return(0);
}


static int
PWMWritePeriod(int pwmnum, int value)
{
	char s_values_str[VALUE_MAX];
	char path[VALUE_MAX];
	int fd,byte;

	snprintf(path, VALUE_MAX, "/sys/class/pwm/pwmchip0/pwm%d/period", pwmnum);
	fd = open(path, O_WRONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open in period!\n");
		return(-1);
	}

	byte = snprintf(s_values_str,10,"%d",value);

	if (-1 == write(fd, s_values_str, byte)) {
		fprintf(stderr, "Failed to write value in period!\n");
		close(fd);
		return(-1);
	}

	close(fd);
	return(0);
}

static int
PWMWriteDutyCycle(int pwmnum, int value)
{
	char path[VALUE_MAX];
	char s_values_str[VALUE_MAX];
	int fd,byte;

	snprintf(path, VALUE_MAX, "/sys/class/pwm/pwmchip0/pwm%d/duty_cycle", pwmnum);
	fd = open(path, O_WRONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open in duty_cycle!\n");
		return(-1);
	}


	byte = snprintf(s_values_str,10,"%d",value);

	if (-1 == write(fd, s_values_str, byte)) {
		fprintf(stderr, "Failed to write value! in duty_cycle\n");
		close(fd);
		return(-1);
	}

	close(fd);
	return(0);
}

int main(void)
{
  PWMExport(0);
  PWMWritePeriod(0,5000000);
  PWMWriteDutyCycle(0,0);
  PWMEnable(0);
	  PWMWriteDutyCycle(0,300000);
	 
  PWMExport(1);
  PWMWritePeriod(1,5000000);
  PWMWriteDutyCycle(1,0);
  PWMEnable(1);
	  PWMWriteDutyCycle(1,300000); 
  double pos = 5;
  int ttt;
  int sock = socket(PF_INET, SOCK_STREAM, 0);
  char ip[] = "192.168.0.92";
  struct sockaddr_in sockip;
  char msg[100];
  int kt;
  memset(&sockip, 0, sizeof(sockip));
  sockip.sin_family = AF_INET;
  sockip.sin_addr.s_addr = inet_addr(ip);
  sockip.sin_port = htons(8888);
  do{
    ttt = connect(sock, (struct sockaddr *)&sockip, sizeof(sockip));
  }while(ttt==-1);
  while(1)
  {
    kt = read(sock, msg, sizeof(msg) - 1);
	printf("%s\n",msg);
    if(!strcmp("1",msg))
    {
      break;
    }
  }
  close(sock);

  
	  PWMWriteDutyCycle(0,1300000);
	  sleep(1);
	  PWMUnable(0);
	  sock = socket(PF_INET, SOCK_STREAM, 0);
	do{
    ttt = connect(sock, (struct sockaddr *)&sockip, sizeof(sockip));
  }while(ttt==-1);
  while(1)
  {
    kt = read(sock, msg, sizeof(msg) - 1);
	printf("%s\n",msg);
    if(!strcmp("1",msg))
    {
      break;
    }
  }
	  PWMWriteDutyCycle(1,1300000);
	  sleep(1);
	  PWMUnable(1);

close(sock);

  return 0;
}
