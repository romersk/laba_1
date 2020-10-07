#include <winsock2.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

using namespace std;


int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");
    WORD wVersion;
    WSADATA wsaData;
    wVersion = MAKEWORD(2,2);
    WSAStartup(wVersion, &wsaData);

    char message[80], buf[80];
    struct sockaddr_in addr;
    int len = sizeof(addr);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1280);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    SOCKET sd = socket(AF_INET, SOCK_DGRAM, 0);
    cout << "Enter str: " << endl;
    cin.getline(message, 80, '\n');
    sendto(sd, message, sizeof(message), 0, (struct sockaddr*) &addr, len);
    recvfrom(sd, buf, 80, 0, (struct sockaddr*) &addr, &len);
    buf[strlen(message)] = '\0';
    cout << "Answer = " << buf << endl;

    system("pause");
    closesocket(sd);
    WSACleanup();
    return 0;
}
