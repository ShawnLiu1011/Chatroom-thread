#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <math.h>
#include <map>
#include <string>

using namespace std;
#define QLEN       5
#define    WSVERS    MAKEWORD(2, 0)
#define    BUFLEN    2000
#pragma comment(lib,"ws2_32.lib")

    SOCKET    msock, ssock;
    SOCKET    sockets[100] = {NULL};

     int cc;
     char buf[2000];
     char *input;
     HANDLE hThread1,hThread[100] = {NULL};
    unsigned int threadID,ThreadID[100],number;

    struct    sockaddr_in fsin;
    struct    sockaddr_in Sin;
    map<int, char*> username;
    map<int, char*>::iterator it;
unsigned int __stdcall Chat(PVOID PM)
{

    char buf1[2000];
    char buf2[2000];
    char buf3[2000];
    char buf4[2000];
    sockets[number] = ssock;
    SOCKET    sock = ssock;
    ThreadID[number] = threadID;

    unsigned int threadid = threadID;

    char name[100];
    (void) recv(sock,name, BUFLEN, 0);
    username[threadid]=name;

    sprintf(buf1,"[Threadid: %d ]\n",threadid);
    (void) send(sock,buf1, sizeof(buf1), 0);

    sprintf(buf2," User <%s> <IP:%s PORT:%d>  Enter!  \n",username[threadid],inet_ntoa(fsin.sin_addr),fsin.sin_port);
    printf("%s ",buf2);
    //printf("\t message will send to all user! \n");
    for(int i=0;i<=number;i++)
    {
        if(sockets[i] != NULL && sockets[i] != sock)
        {
            (void) send(sockets[i],buf2, sizeof(buf2), 0);
        }
    }
    printf("\nAll user list: ");
    it = username.begin();
    int cnt =1;
    while(it != username.end())
    {
        printf("<user%d: %s>  ",cnt,it->second);
        it ++;
        cnt ++;
    }
    printf("\n");


flag1:cc = recv(sock, buf3, BUFLEN, 0);
    if(cc == SOCKET_ERROR|| cc == 0)
    {
        sprintf( buf3," User <%s>   Leave!  \n",username[threadid]);
        sock = NULL;
        sockets[number] = NULL;
        CloseHandle(hThread[number]);
        username.erase(threadid);
        printf("%s ", buf3);

        for(int i=0;i<=number;i++)
        {
            if(sockets[i] != NULL && sockets[i] != sock)
                (void) send(sockets[i], buf3, sizeof(buf3), 0);
        }

        printf("\nAll user list: ");
        it = username.begin();
        cnt =1;
        while(it != username.end())
        {
            printf("<user%d: %s>  ",cnt,it->second);
            it ++;
            cnt ++;
        }
    printf("\n");
    }

    else if(cc > 0)
    {
        char cn[20]="/changename ";
        if(buf3[0]=='/')
        {
            int flag=1;
            for(int i=1;i<12;i++)
            {
                if(buf3[i]!=cn[i])
                    flag = 0;
                    break;
            }
            if(flag)
            {
                sprintf("%s",username[threadid]);
                string buffer = buf3;
                username[threadid]=(char*)buffer.substr(12).c_str();
                sprintf(buf4," change username to %s \n",username[threadid]);
            }

        }

        else
            sprintf(buf4," User <%s> said : %s  \n",username[threadid],buf3);

        printf("%s ",buf4);
        for(int i=0;i<=number;i++)
        {
            if(sockets[i] != NULL && sockets[i] != sock)
                (void) send(sockets[i], buf4, sizeof(buf4), 0);
        }
        printf(" \n");

        goto flag1;
    }
        (void) closesocket(sock);

        return 0;
}



int main(int argc, char *argv[])

{
    int     alen;
    WSADATA wsadata;
    char    *service = "5050";
    WSAStartup(WSVERS, &wsadata);
    msock = socket(PF_INET, SOCK_STREAM, 0);
    memset(&Sin, 0, sizeof(Sin));
    Sin.sin_family = AF_INET;
    Sin.sin_addr.s_addr = INADDR_ANY;
    Sin.sin_port = htons((u_short)atoi(service));
    bind(msock, (struct sockaddr *)&Sin, sizeof(Sin));
    listen(msock, 5);
    printf("\t\t\t\t       Chatroom_(Server) \n");
        number = -1;
    while(1)
    {
        alen = sizeof(struct sockaddr);
        ssock = accept(msock, (struct sockaddr *)&fsin, &alen);
        number ++;
        hThread[number] = (HANDLE)_beginthreadex(NULL, 0,Chat,NULL, 0, &threadID);
    }
    (void) closesocket(msock);
    WSACleanup();
}

