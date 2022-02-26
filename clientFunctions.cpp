#include "clientUtils.h"

SOCKET connectToServer(std::string ipAddress, unsigned int port)
{
	// Create socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		cerr << "Can't create socket, Err #" << WSAGetLastError() << endl;
		Sleep(5000);
		WSACleanup();
		return (SOCKET)-1;
	}

	// Fill in a hint structure
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	// Connect to server
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		cerr << "Can't connect to server, Err #" << WSAGetLastError() << endl;
		Sleep(5000);
		closesocket(sock);
		WSACleanup();
		return (SOCKET)-1;
	}

	return sock;
}

void faculties(SOCKET sock)
{
	info faculty;
	int byte_recv, i = 1;
	

	printf("Faculties are: \n");
	do {
		byte_recv = recv(sock, (char*)&faculty, sizeof(faculty), 0);
		
		if (faculty.flag == 0) break;
		printf_s("   %d) Name: %s Department: %s Phone no: %-.11d\n",i++, faculty.name, faculty.department, faculty.phone_no);


		
	} while (byte_recv > 0);
	return;
}

void introScreen(char* str)
{
	

	char c ;
	unsigned int i = 0 , featureCount= 2;
	char * arrow = (char*)calloc(featureCount, sizeof(char));
	

	memset( arrow, ' ', sizeof(char));
	arrow[i] = '>';

	while (true) {
		if (_kbhit())
		{
			
			c = _getch();
			if (c == 'w') i--;
			if (c == 's') i++;
			if (i < 0) i = 0;
			if (i > featureCount - 1) i = featureCount - 1;
			switch (i)
			{
			case 0:
				strcpy(str, "faculty");
				break;
			case 1:
				strcpy(str, "searchfaculty");
				break;

			default:
				break;

			}
			if (c == 'x') return;
			memset(arrow, ' ', sizeof(arrow));
			arrow[i] = '>';
		}

		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
		printf("                          ||          IUT HELPLINE        ||\n\n");
		printf("                               %c 1) List faculties\n",arrow[0]);
		printf("                               %c 2) Search faculties", arrow[1]);
		Sleep(3);
		system("cls");
	}

	



}