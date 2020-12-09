#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main()
{
    int serv_sock, clnt_sock = -1;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_addr_size;
    int sock = socket(PF_INET, SOCK_STREAM, 0);

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));

    struct sockaddr_in sockip;
    sockip.sin_family = AF_INET;
    sockip.sin_addr.s_addr = inet_addr("192.168.0.74");
    sockip.sin_port = htons(8888);

    int kk = 0;
    int a = listen(serv_sock, 5);
    if (a == -1)
        error_handling("listen() error");
    if (clnt_sock < 0)
    {
        clnt_addr_size = sizeof(clnt_addr);
        clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr,
                           &clnt_addr_size);
        printf("%d\n", clnt_addr.sin_addr.s_addr);
        if (clnt_sock == -1)
            error_handling("accept() error");
    }
    char msg[100] = "0";
    while (1)
    {
        scanf("%s", msg);
        write(clnt_sock, msg, sizeof(msg));
        printf("msg = %s\n", msg);
    }
}