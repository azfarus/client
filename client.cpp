#include "clientUtils.h"
#pragma comment(lib, "ws2_32.lib")

int log_Stat = 0;
studentPortal loggedStud;


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

	

	introScreen2(userInput , log_Stat , &loggedStud);

	do
	{

		// Send the text
		int sendResult = send(sock, userInput, sizeof(userInput) + 1, 0);

		if (!strncmp(userInput, "faculty", 7))
		{
			if (sendResult != SOCKET_ERROR)
			{
				// Wait for response
				//std::cout << ">>>>>  " << log_Stat<<endl;
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
				fflush(stdin);
				Portal(sock , &loggedStud, &log_Stat);
			}
		}
		else if (!strncmp(userInput, "login", 6))
		{
			if (sendResult != SOCKET_ERROR)
			{
				fflush(stdin);
				login_client(sock , &log_Stat , &loggedStud);
			}
		}
		else if (!strncmp(userInput, "cafe", 4))
		{
			if (sendResult != SOCKET_ERROR)
			{
				fflush(stdin);
				TicketPrint(sock , &loggedStud);
			}
		}
		else if (!strncmp(userInput, "admission", 9))
		{
			if (sendResult != SOCKET_ERROR)
			{
				fflush(stdin);
				admission(sock);
			}
		}
		else if (!strncmp(userInput, "chat", 4))
		{
			if (sendResult != SOCKET_ERROR)
			{
				fflush(stdin);
				chat(sock);

			}
		}

		printf("\n\n\n\nPress enter to go back : ");
		getchar();
		introScreen2(userInput, log_Stat, &loggedStud);






	} while (true);

	// Gracefully close down everything
	closesocket(sock);
	WSACleanup();
}



