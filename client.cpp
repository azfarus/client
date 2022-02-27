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


	SOCKET sock = connectToServer("127.0.0.1", 54000);

	char buf[4096];
	char userInput[500];
	char control;
	info siuuu;

	introScreen(userInput);

	do
	{
		// Prompt the user for some text
		

				// Make sure the user has typed in something
		
			// Send the text
			int sendResult = send(sock, userInput, sizeof(userInput) + 1, 0);

			if (!strncmp(userInput, "faculty", 6))
			{
				if (sendResult != SOCKET_ERROR)
				{
					// Wait for response
					faculties(sock);
				}
			}

			printf("Please enter to go back : ");
		    getchar();
			introScreen(userInput);


		
			
		

	} while (true);

	// Gracefully close down everything
	closesocket(sock);
	WSACleanup();
}
