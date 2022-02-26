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


	SOCKET sock = connectToServer("192.168.0.106", 54000);

	char buf[4096];
	string userInput;
	info siuuu;

	do
	{
		// Prompt the user for some text
		cout << "> ";
		getline(cin, userInput);

		if (userInput.size() > 0)		// Make sure the user has typed in something
		{
			// Send the text
			int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);

			if (!strncmp(userInput.c_str(), "faculty", 6))
			{
				if (sendResult != SOCKET_ERROR)
				{
					// Wait for response
					faculties(sock);
				}
			}

		}
			
		

	} while (userInput.size() > 0);

	// Gracefully close down everything
	closesocket(sock);
	WSACleanup();
}
