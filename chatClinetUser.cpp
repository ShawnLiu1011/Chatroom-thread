#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#include <process.h>

#define    BUFLEN        2000
#define WSVERS        MAKEWORD(2, 0)
#pragma comment(lib,"ws2_32.lib")


    SOCKET    sock,sockets[100] = {NULL};
    char    *packet = NULL;
    char *input;
    HANDLE hThread;
    unsigned threadID;

unsigned int __stdcall Chat(PVOID PM )
{

       char buf[2000];

while(1)
{
    int cc = recv(sock, buf, BUFLEN, 0);
    if(cc == SOCKET_ERROR|| cc == 0)
    {
        printf("Error: %d.----",GetLastError());
        printf("Connection failed!\n");
        CloseHandle(hThread);
        (void)closesocket(sock);
        break;
    }
    else if(cc > 0)
        printf("%s\n",buf);
}
    return 0;
}

int main(int argc, char *argv[])
{

    char    *host = "127.0.0.1";
    char *service = "5050";
    struct  sockaddr_in sin;
    WSADATA wsadata;
    WSAStartup(WSVERS, &wsadata);

    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons((u_short)atoi(service));
    sin.sin_addr.s_addr = inet_addr(host);

    sock = socket(PF_INET, SOCK_STREAM,0);

    connect(sock, (struct sockaddr *)&sin, sizeof(sin));

    printf("\t\t\t\t       Chatroom_(clinet) \n");
    printf("Please input your username: ");
    char name[100];
    gets(name);
    send(sock,name, sizeof(name), 0);
    hThread = (HANDLE)_beginthreadex(NULL, 0,Chat, NULL, 0, &threadID);
while(1)
{
    char buf1[2000];

    gets(buf1);
    if(!strcmp(buf1 ,"exit"))
     break;

    (void) send(sock,buf1, sizeof(buf1), 0);
    printf(" Successful send!\n\n");
}

end:    CloseHandle(hThread);
        closesocket(sock);
        WSACleanup();
    return 0;
}
