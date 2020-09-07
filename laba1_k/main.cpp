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
    int Exit = 1;
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1280);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    SOCKET sd = socket(AF_INET, SOCK_STREAM, 0);

    if(connect(sd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("Error connecting to server");
        exit(2);
    }

    while(Exit)
    {
        cout << "Enter str: " << endl;
        scanf("%s", message);
        send(sd, message, sizeof(message)+1, 0);
        recv(sd, buf, sizeof(buf), 0);
        cout << "The Answer = " << buf << endl;
        cout << "Continue?" << endl << "1 - yes" << endl << "0 - no" << endl;;
        scanf("%d", &Exit);

    }
    closesocket(sd);
    return 0;

}
