#include "HServer.h"
#pragma warning(disable : 4996)
using namespace std;

int numcl = 0;

DWORD WINAPI ThreadFunc(LPVOID client_socket) {
    SOCKET s2 = ((SOCKET *)client_socket)[0];
	char buf[100], buf1[100], temp[2];
	int i, j, len, count = 0, free_pos = 10;
    while (true) {
        while (recv(s2, buf, sizeof(buf), 0)) {
			if (buf[0] == -52)
				continue;
			len = strlen(buf);
			itoa(len, buf1, 10);
			count = 0;
			free_pos = 10;
			if (len == 10) {
				for (i = 0; i < 10; i++) {
					if (buf[i] >= 'A' && buf[i] <= 'Z') {
						if (i < free_pos) free_pos = i;
					}
					else if (free_pos != 10) {
						buf[free_pos] = buf[i];
						buf[i] = 'A';
						i = free_pos;
						free_pos = 10;
					}
				}
				count = 10 - free_pos;
				buf[free_pos++] = ' ';
				itoa(count, temp, 10);
				buf[free_pos++] = temp[0];
				buf[free_pos++] = temp[1];
				temp[0] = temp[1] = '\0';
				for (i = free_pos; i < 13; i++) {
					buf[i] = '\0';
				}
				send(s2, buf, sizeof(buf), 0);
			}
			else
				send(s2, buf1, sizeof(buf1), 0);
			for (int i = 0; i < buf[i]!='\0'; i++) buf[i] = '\0';
			for (int i = 0; i < buf1[i]!='\0'; i++) buf1[i] = '\0';
        }
    }
    cout << "Disconnect" << numcl-- << endl;
    closesocket(s2);
    return 0;
}

void print() {
    if (numcl) printf("%d client connected\n", numcl);
    else printf("No clients connected\n");
}

void main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;
    wVersionRequested = MAKEWORD(2, 2);
    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) { return; }
    SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in local_addr;
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(1280);
    local_addr.sin_addr.s_addr = 0;
    bind(s, (sockaddr *)&local_addr, sizeof(local_addr));
    int c = listen(s, 5);
    cout << "Server receive ready" << endl;
    cout << endl;
    SOCKET client_socket;
    sockaddr_in client_addr;
    int client_addr_size = sizeof(client_addr);
    while ((client_socket = accept(s, (sockaddr *)&client_addr, &client_addr_size))) {
        numcl++;
        print();
        DWORD thID;
        CreateThread(NULL, NULL, ThreadFunc, &client_socket, NULL, &thID);
    }
}
