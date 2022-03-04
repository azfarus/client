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

void services(SOCKET sock)
{
	EmergencyServices service;
	int byte_recv, i = 1;
	/*char dept[10];


	ZeroMemory(dept, 10);*/
	printf("Services are: \n");
	do {
		byte_recv = recv(sock, (char*)&service, sizeof(service), MSG_PEEK);
		if ((service.contact) == 0)
		{
			recv(sock, (char*)&service, sizeof(service), 0);
			break;
		}
		/*if (strcmp(dept,faculty.department))
		{
			strcpy(dept, faculty.department);
			printf("  %4s : \n",dept);
		}*/

		byte_recv = recv(sock, (char*)&service, sizeof(service), 0);
		printf_s("   %3d) Service Name: %20s Contact no: %-11.11llu\n", i++, service.service, service.contact);



	} while (byte_recv > 0);
	return;
}

void faculties(SOCKET sock)
{
	info faculty;
	int byte_recv, i = 1;
	char dept[10];


	ZeroMemory(dept, 10);
	printf("Faculties are: \n");
	do {
		byte_recv = recv(sock, (char*)&faculty, sizeof(faculty), MSG_PEEK);
		if ((faculty.phone_no) == 0)
		{
			recv(sock, (char*)&faculty, sizeof(faculty), 0);
			break;
		}
		if (strcmp(dept, faculty.department))
		{
			strcpy(dept, faculty.department);
			printf("  %4s : \n", dept);
		}

		byte_recv = recv(sock, (char*)&faculty, sizeof(faculty), 0);
		printf_s("   %3d) Name: %20s Department: %20s Phone no: %-11.11llu\n", i++, faculty.name, faculty.department, faculty.phone_no);



	} while (byte_recv > 0);
	return;
}

void Portal(SOCKET sock)
{
	studentPortal student;
	int byte_recv, i = 1;

	printf("Student Details: \n\n");
	do {
		byte_recv = recv(sock, (char*)&student, sizeof(student), MSG_PEEK);
		if ((student.roll) == 0)
		{
			recv(sock, (char*)&student, sizeof(student), 0);
			break;
		}

		byte_recv = recv(sock, (char*)&student, sizeof(student), 0);

		printf_s(" Password: %llu\n Roll: %llu\n Name: %s\n Email: %s\n Father's Name: %s\n Mother's Name: %s\n Dept: %s\n CG: %.2lf\n", student.hash, student.roll, student.name, student.email, student.father, student.mother, student.dept, student.CG);



	} while (byte_recv > 0);
	return;
}
void introScreen(char* str)
{


	char c;
	unsigned int i = 0, featureCount = 4;
	char* arrow = (char*)calloc(featureCount, sizeof(char));


	memset(arrow, ' ', sizeof(char));
	arrow[i] = '>';

	while (true) {
		if (_kbhit())
		{
			//Loop e add kore nis Help option ta
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
			case 2:
				strcpy(str, "help");
				break;
			case 3:
				strcpy(str, "Portal");
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
		printf("                               %c 1) List faculties\n", arrow[0]);
		printf("                               %c 2) Search faculties\n", arrow[1]);
		printf("                               %c 3) Emergency Services\n", arrow[2]);
		printf("                               %c 4) Student Portal\n", arrow[3]);
		Sleep(150);
		system("cls");
	}





}


void searchFaculties_client(SOCKET sock)
{
	info faculty;
	int byte_recv, i = 1;
	char searchTermBuf[128], dept[10];
	cout << "Enter name of teacher : " << endl;

	scanf("%s", searchTermBuf);

	int sendbytes = send(sock, searchTermBuf, 128, 0);
	if (sendbytes == 0 || sendbytes == SOCKET_ERROR)
	{
		cerr << "FAILED TO SEARCH. RETURNING..." << endl;
		return;
	}



	printf("Results found are: \n");
	do {
		byte_recv = recv(sock, (char*)&faculty, sizeof(faculty), MSG_PEEK);
		if ((faculty.phone_no) == 0)
		{
			recv(sock, (char*)&faculty, sizeof(faculty), 0);
			break;
		}
		if (strcmp(dept, faculty.department))
		{
			strcpy(dept, faculty.department);
			printf("  %4s : \n", dept);
		}

		byte_recv = recv(sock, (char*)&faculty, sizeof(faculty), 0);
		printf_s("   %3d) Name: %20s Department: %20s Phone no: %-11.11u\n", i++, faculty.name, faculty.department, faculty.phone_no);



	} while (byte_recv > 0);
	getchar();
	return;
}