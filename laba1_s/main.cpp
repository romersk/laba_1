#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    WORD wVersion;
    WSADATA wsaData;
    wVersion = MAKEWORD(2,2);
    WSAStartup(wVersion, &wsaData);

    SOCKET sd = socket(AF_INET, SOCK_STREAM, 0);
    int sock, bytes_read;
    char buf[80];
    struct sockaddr_in local;
    int localLen = sizeof(local);
    local.sin_family = AF_INET;
    local.sin_port = htons(1280);
    local.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(bind(sd, (sockaddr*)&local, localLen) < 0)
    {
        perror("Ошибка инициализации сокета.");
        exit(2);
    }

    cout << "Сервер запущен" << endl;
    int r = listen(sd, 5);

    while(1)
    {
        SOCKET s2 = accept(sd, (struct sockaddr*) &local, &localLen);
        bytes_read = recv(s2, buf, 80, 0);
        if(bytes_read <= 0)
            break;
        buf[strlen(buf)+1] = '\0';
        cout << buf << endl;
        for(int i=3; i<strlen(buf); i+=4)
        {
            buf[i]='%';
        }
        send(s2, buf, bytes_read, 0);
        closesocket(s2);

    }
    closesocket(sd);
    WSACleanup();
    return 0;
}
