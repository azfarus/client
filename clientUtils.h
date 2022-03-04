#pragma once
#pragma once
#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <Windows.h>
#include <conio.h>

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define ipaddress "127.0.0.1"

#pragma comment (lib, "ws2_32.lib")

typedef struct _Info
{
	char name[50], address[100], department[10];
	unsigned long long int phone_no;
	int flag;


} info;


typedef struct _emergency {
	char service[50];
	unsigned long long int contact;
	bool flag;
} EmergencyServices;

typedef struct _student {
	unsigned long long hash;
	unsigned long long roll;
	char name[100], email[50], father[100], mother[100], dept[4];
	double CG;
}studentPortal;

SOCKET connectToServer(std::string ipAddress, unsigned int port);
void faculties(SOCKET sock);
void services(SOCKET sock); //New function for printing services
void introScreen(char* str);
void searchFaculties_client(SOCKET sock);
void Portal(SOCKET sock); //New function addded



using namespace std;

