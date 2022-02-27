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
	int phone_no;
	int flag ;
	

} info;

typedef struct _emergency {
	char service[50];
	int contact, flag;
} EmergencyServices;

SOCKET connectToServer(std::string ipAddress, unsigned int port);
void faculties(SOCKET sock);
void introScreen(char* str);
void Emergency(SOCKET sock);

using namespace std;

