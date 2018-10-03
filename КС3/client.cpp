#include "HClient.h"
#pragma warning(disable : 4996)
using namespace std;

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;
    wVersionRequested = MAKEWORD(2, 2);
    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) { return; }
    SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in dest_addr;
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(1280);
    dest_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    connect(s, (sockaddr *)&dest_addr, sizeof(dest_addr));
    char buf[100], recive_buf[100];
    while (true) {
        cout << "¬ведите строку:" << endl;
		cin >> buf;
        send(s, buf, 100, 0);
        if (recv(s, recive_buf, sizeof(recive_buf), 0) != 0) {
            cout << "Poluchenaya stroka:" << endl << recive_buf << endl;
        }
        for (int i = 0; i < 100; i++) buf[i] = '\0';
		for (int i = 0; i < 100; i++) recive_buf[i] = '\0';
    }
    end:
    closesocket(s);
    WSACleanup();
}
