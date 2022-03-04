#include <iostream>
#include <string>
#include <WS2tcpip.h>
#include "clientUtils.h"
#pragma comment(lib, "ws2_32.lib")



using namespace std;

void main()
{
	// Initialize WinSock
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0)
	{
		cerr << "Can't start Winsock, Err #" << wsResult << endl;
		return;
	}


	SOCKET sock = connectToServer(ipaddress, 54000);

	char buf[4096];
	char userInput[500];
	char control;
	info siuuu;

	introScreen(userInput);

	do
	{

		// Send the text
		int sendResult = send(sock, userInput, sizeof(userInput) + 1, 0);

		if (!strncmp(userInput, "faculty", 7))
		{
			if (sendResult != SOCKET_ERROR)
			{
				// Wait for response
				faculties(sock);
			}
		}

		else if (!strncmp(userInput, "searchfaculty", 13))
		{
			if (sendResult != SOCKET_ERROR)
			{
				searchFaculties_client(sock);
			}
		}

		//Newly Implemented addition
		else if (!strncmp(userInput, "help", 4))
		{
			if (sendResult != SOCKET_ERROR)
			{
				services(sock);
			}
		}

		//Newly Implemented addition
		else if (!strncmp(userInput, "Portal", 6))
		{
			if (sendResult != SOCKET_ERROR)
			{
				Portal(sock);
			}
		}

		printf("Press enter to go back : ");
		getchar();
		introScreen(userInput);






	} while (true);

	// Gracefully close down everything
	closesocket(sock);
	WSACleanup();
}
