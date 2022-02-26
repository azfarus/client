#pragma once
#pragma once
#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <Windows.h>
#include <conio.h>

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment (lib, "ws2_32.lib")

typedef struct _Info
{
	char name[50], address[100] , department[10];
	unsigned long long int phone_no;
	int flag ;
	

} info;

SOCKET connectToServer(std::string ipAddress, unsigned int port);
void faculties(SOCKET sock);
void introScreen(char* str);


using namespace std;

