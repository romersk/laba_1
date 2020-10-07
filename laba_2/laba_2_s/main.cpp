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

    SOCKET sd = socket(AF_INET, SOCK_DGRAM, 0);
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
    bytes_read = recvfrom(sd, buf, 80, 0, (struct sockaddr*) &local, &localLen);
    cout << buf << endl;
    for(int i=0; i<strlen(buf); i++)
    {
        if (buf[i]==' ')
        {
            buf[i] = '*';
        }
    }
    sendto(sd, buf, strlen(buf), 0, (struct sockaddr*) &local, localLen);
    closesocket(sd);
    WSACleanup();
    return 0;
}
