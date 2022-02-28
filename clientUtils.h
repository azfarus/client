#pragma once
#pragma once
#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <Windows.h>
#include <conio.h>

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define ipaddress "192.168.10.101"

#pragma comment (lib, "ws2_32.lib")

typedef struct _Info
{
	char name[50], address[100] , department[10];
	unsigned long long int phone_no;
	int flag ;
	

} info;


typedef struct _emergency {
	char service[50];
	unsigned long long int contact;
	bool flag;
} EmergencyServices;



SOCKET connectToServer(std::string ipAddress, unsigned int port);
void faculties(SOCKET sock);
void services(SOCKET sock); //New function for printing services
void introScreen(char* str);
void searchFaculties_client(SOCKET sock);



using namespace std;

