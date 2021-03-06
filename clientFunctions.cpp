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
	printf("\n\n     \033[4;36m                         Services                            \033[0m \n\n");
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
		if(service.contact>999 )printf_s("   %3d) Service Name: %20s Contact no: %-11.11llu\n", i++, service.service, service.contact);
		else printf_s("   %3d) Service Name: %20s Contact no: %11llu\n", i++, service.service, service.contact);



	} while (byte_recv > 0);
	return;
}

void faculties(SOCKET sock)
{
	info faculty;
	int byte_recv, i = 1;
	char dept[10];


	ZeroMemory(dept, 10);
	printf_s("\033[4;33m");
	printf("Faculties are:\n");
	printf_s("\033[0m");
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
			printf_s("\033[0;36m");
			printf("  %4s : \n\n", dept);
			printf_s("\033[0m");
			
		}

		byte_recv = recv(sock, (char*)&faculty, sizeof(faculty), 0);
		printf_s("       %3d) Name: %25s Address: %15s Department: %5s Phone no: %-11.11llu\n", i++, faculty.name, faculty.address, faculty.department, faculty.phone_no);



	} while (byte_recv > 0);
	return;
}


void Portal(SOCKET sock , studentPortal * loggedStud , int * loginS)
{
	studentPortal student;
	ZeroMemory(&student, sizeof(student));
	if (*loginS != 0 ) student = *loggedStud;

	/*int byte_recv, i = 1;*/

	/*printf("Student Details: \n\n");
	do {
		byte_recv = recv(sock, (char*)&student, sizeof(student), MSG_PEEK);
		if ((student.roll) == 0)
		{
			recv(sock, (char*)&student, sizeof(student), 0);
			break;
		}

		byte_recv = recv(sock, (char*)&student, sizeof(student), 0);

		



	} while (byte_recv > 0);*/
	printf("\n\n\n\n\n\t\t\t\t\033[0;36mWelcome To IUT Student Portal\n");
	printf("\t\t\t\t-----------------------------\033[0m\n\n");

	/*printf_s(" Roll: %llu\n Name: %s\n Email: %s\n Father's Name: %s\n Mother's Name: %s\n Dept: %s\n CG: %.2lf\n", student.roll, student.name, student.email, student.father, student.mother, student.dept, student.CG);
	printf_s("Bank Balance : %d\n", loggedStud->balance);*/

	printf("\033[0;33mRoll         :\033[0m  %-10llu\n", student.roll);
	printf("\033[0;33mName	     :\033[0m  %-20s\n", student.name);
	printf("\033[0;33mEmail        :\033[0m  %-20s\n", student.email);
	printf("\033[0;33mFather's Name:\033[0m  %-20s\n", student.father);
	printf("\033[0;33mMother's Name:\033[0m  %-20s\n", student.mother);
	printf("\033[0;33mDepartment   :\033[0m  %-10s\n", student.dept);
	printf("\033[0;33mCGPA         :\033[0m  %-.2lf\n", student.CG);
	printf("\033[0;33mBank Balance :\033[0m  %-10llu\n", loggedStud->balance);
	return;
}
void introScreen(char* str , int log_Stat)
{


	char c;
    int i = 0, featureCount = 6;
	char* arrow = (char*)calloc(featureCount, sizeof(char));

	if(log_Stat)  featureCount = 8;
	memset(arrow, ' ', featureCount );
	arrow[i] = '>';

	while (true) {
		if (_kbhit())
		{
			//Loop e add kore nis Help option ta
			c = _getch();
			if (c == 'w') i--;
			if (c == 's') i++;
			if (i < 0) i = 0;
			if (i >= featureCount - 1) i = featureCount - 1;
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
				strcpy(str, "login");
				break;
			case 4:
				strcpy(str, "admission");
				break;
			case 5:
				strcpy(str, "chat");
				break;
			case 6:
				strcpy(str, "Portal");
				break;
			case 7: 
				strcpy(str, "cafe");
				break;
			default:
				break;

			}
			if (c == 'x')
			{
				system("cls");
				return;
			}
			memset(arrow, ' ', featureCount );
			arrow[i] = '>';
		}

				      printf("\n\n\n\n\n\n\n\n\n\n\n");
				      printf("                          ||      IUT Virtual Assistant   ||\n\n");
					  printf("                               %c 1) List faculties\n", arrow[0]);
					  printf("                               %c 2) Search faculties\n", arrow[1]);
					  printf("                               %c 3) Emergency Services\n", arrow[2]);
					  printf("                               %c 4) Login Window\n", arrow[3]);
					  printf("			       %c 5) Admission Portal\n", arrow[4]);
					  printf("			       %c 6) Chat with a Virtual Assistant\n", arrow[5]);
					  if (log_Stat)
					  {
						  printf("                               %c 7) Student Portal\n", arrow[6]);
						  printf("			       %c 8) Buy Cafe Tickets\n", arrow[7]);
					  }
		
		//Sleep(150);
		//system("cls");
		gotoxy(0, 0);
	}





}

void introScreen2(char* str, int log_stat , studentPortal * studlog)
{ 

	sf::RenderWindow win(sf::VideoMode(1280, 720), "Virtual Assistant");
	sf::RectangleShape background(sf::Vector2f(750.0f, 900.0f));
	background.setPosition(260.0f, 0.0f);
	sf::Texture iutTexture;
	iutTexture.loadFromFile("iut x.png");
	background.setTexture(&iutTexture);

	sf::SoundBuffer buffer;
	buffer.loadFromFile("sound.wav");
	sf::Sound mousepop;
	mousepop.setBuffer(buffer);

	sf::Font font;
	font.loadFromFile("Montserrat.ttf");


	string loginthings;
	char temp[30];

	if (log_stat)
	{
		sprintf(temp, "%d", studlog->roll);
		loginthings = temp;
	}
	else
	{
		loginthings = "Not Logged in";
	}
	sf::Text text;
	text.setFont(font);
	text.setString(loginthings);
	text.setCharacterSize(18);
	text.setFillColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);
	text.setPosition(1100.0f, 680.0f);


	Button search, list, adms, cafe, chat, login, stdportal, emergency;

	system("cls");
	list.create(xthresh, ythresh + 80 * 0, 200, 80, "search2.png", "search1.png", "search3.png");
	search.create(xthresh, ythresh  + 80 * 1 + 10, 200, 80, "list2.png", "list1.png", "list3.png");
	adms.create(xthresh, ythresh + 80 * 2 +20, 200, 80, "adms2.png", "adms1.png", "adms3.png");
	emergency.create(xthresh, ythresh + 80 * 3+ 30, 200 , 80, "emergency2.png", "emergency1.png", "emergency3.png");

	chat.create(xthresh+210, ythresh + 80 * 0, 200, 80, "chat2.png", "chat1.png", "chat3.png");
	login.create(xthresh+210, ythresh + 80 * 1+ 10, 200, 80, "login2.png", "login1.png", "login3.png");
	stdportal.create(xthresh+210, ythresh + 80 * 2 +20, 200, 80, "stdportal2.png", "stdportal1.png", "stdportal3.png");
	cafe.create(xthresh+210, ythresh + 80 * 3 +30, 200, 80, "cafe2.png", "cafe1.png", "cafe3.png");

	int x[2] = { 0 };
	int y[2] = { 0 };
	int z[2] = { 0 };
	int a[2] = { 0 };
	int b[2] = { 0 };
	int c[2] = { 0 };
	int d[2] = { 0 };
	int e[2] = { 0 };


	while (win.isOpen())
	{
		sf::Event eve;
		while (win.pollEvent(eve))
		{
			x[0] = search.onButton(win, str, "searchfaculty");
			if (x[0] == 1 && x[1] == 0)
			{
				mousepop.play();
				
			} 
			x[1] = x[0];
			
			
			y[0] = list.onButton(win, str, "faculty");
			if (y[0] == 1 && y[1] == 0)
			{
				mousepop.play();
			}
			y[1] = y[0];

			z[0] = adms.onButton(win, str, "admission");
			if (z[0] == 1 && z[1] == 0)
			{
				mousepop.play();
			}
			z[1] = z[0];

			a[0] = emergency.onButton(win, str, "help");
			if (a[0] == 1 && a[1] == 0)
			{
				mousepop.play();
			}
			a[1] = a[0];
			b[0] = login.onButton(win, str, "login");
			if (b[0] == 1 && b[1] == 0)
			{
				mousepop.play();
			}
			b[1] = b[0];
			c[0] = chat.onButton(win, str, "chat");
			if (c[0] == 1 && c[1] == 0)
			{
				mousepop.play();
			}
			c[1] = c[0];
			

			if (log_stat == 1)
			{
				
				d[0] = stdportal.onButton(win, str, "Portal");
				if (d[0] == 1 && d[1] == 0)
				{
					mousepop.play();
				}
				d[1] = d[0];

				e[0] = cafe.onButton(win, str, "cafe");
				if (e[0] == 1 && e[1] == 0)
				{
					mousepop.play();
				}
				e[1] = e[0];
			}
			if (eve.type == sf::Event::Closed)
			{
				win.close();
				introScreen(str, log_stat);
			}


		}
		win.clear(sf::Color::Black);
		win.draw(background);
		search.drawButton(win);
		list.drawButton(win);
		adms.drawButton(win);
		emergency.drawButton(win);
		chat.drawButton(win);
		login.drawButton(win);
		stdportal.drawButton(win);
		cafe.drawButton(win);
		win.draw(text);
		win.display();
	}
}

void searchFaculties_client(SOCKET sock)
{
	info faculty;
	int byte_recv, i = 1;
	char searchTermBuf[128], dept[10];
	cout << "Enter search term (non space separated) : " << endl;
	printf_s("\033[0;34m >>> \033[0m");

	scanf("%s", searchTermBuf);

	int sendbytes = send(sock, searchTermBuf, 128, 0);
	if (sendbytes == 0 || sendbytes == SOCKET_ERROR)
	{
		cerr << "FAILED TO SEARCH. RETURNING..." << endl;
		return;
	}


	printf_s("\033[4;33m");
	printf("\n\nResults found are:\n");
	printf_s("\033[0m");
	
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
			
			printf_s("\033[0;36m");
			printf("  %4s : \n\n", dept);
			printf_s("\033[0m");
		}

		byte_recv = recv(sock, (char*)&faculty, sizeof(faculty), 0);
		printf_s("   %3d) Name: %20s Department: %20s Phone no: %-11.11llu\n", i++, faculty.name, faculty.department, faculty.phone_no);



	} while (byte_recv > 0);
	getchar();
	return;
}

unsigned long long Hash(const char* str)
{
	unsigned long long x = 0;

	for (int i = 0; str[i] != '\0'; i++)
	{
		x = str[i] + (x << 6) + (x << 16) - x; 
		//or multiplying by 65599
		//SDBM hash
	}
	return x;
}

std::string takePasswdFromUser(char sp = '*')
{
	fflush(stdin);
	// Stores the password
	string passwd = "";
	char ch_ipt;

	// Until condition is true
	while (true) {

		ch_ipt = _getch();

		// if the ch_ipt
		if (ch_ipt == IN::IN_RET) {
			cout << endl;
			return passwd;
		}
		else if (ch_ipt == IN::IN_BACK
			&& passwd.length() != 0) {
			passwd.pop_back();

			// Cout statement is very
			// important as it will erase
			// previously printed character
			cout << "\b \b";

			continue;
		}

		// Without using this, program
		// will crash as \b can't be
		// print in beginning of lines
		else if (ch_ipt == IN::IN_BACK
			&& passwd.length() == 0) {
			continue;
		}

		passwd.push_back(ch_ipt);
		cout << sp;
	}
}



void login_client(SOCKET sock , int * log_Stat , studentPortal * loggedStud)
{
	logininfo log;
	string pass;
	char success_status;
	
	//Login TUI
	printf("\n\n\n\n\n\n\t\t\t\t\033[0;36mPlease Login With Your Student Account to Enable Student Portal:\n");
	printf("\t\t\t\t----------------------------------------------------------------\033[0m\n\n");
	std::cout << "\n\t\t\t\t\033[0;33mPlease Enter your ID and password to log in : \033[0m\n";
	std::cout << "\n\t\t\t\t\033[0;33mID : \033[0m";
	cin >> log.id; getchar();
	cout << "\n\t\t\t\t\033[0;33mPassword : \033[0m";
	//scanf("%s", password); getchar();
	pass = takePasswdFromUser();

	int p_l = pass.length();

	// declaring character array
	char password[100];

	// copying the contents of the
	// string to char array
	strcpy(password, pass.c_str());

	/*
		// Function that accepts the password
		string takePasswdFromUser(char sp = '*')
		{
			// Stores the password
			string passwd = "";
			char ch_ipt;
 
			// Until condition is true
			while (true) {
 
				ch_ipt = getch();
 
				// if the ch_ipt
				if (ch_ipt == IN::IN_RET) {
					cout << endl;
					return passwd;
				}
				else if (ch_ipt == IN::IN_BACK
						 && passwd.length() != 0) {
					passwd.pop_back();
 
					// Cout statement is very
					// important as it will erase
					// previously printed character
					cout << "\b \b";
 
					continue;
				}
 
				// Without using this, program
				// will crash as \b can't be
				// print in beginning of line
				else if (ch_ipt == IN::IN_BACK
						 && passwd.length() == 0) {
					continue;
				}
 
				passwd.push_back(ch_ipt);
				cout << sp;
			}
		}
 
		// Driver Code
		int main()
		{
			string input;
			cout << "@root>>> ";
 
			// Function call
			input = takePasswdFromUser();
			cout << input << endl;
		}
	
	*/

	log.hash = Hash(password);

	int sendbytes = send(sock, (char*)&log, sizeof(logininfo), 0);
	if (sendbytes == 0)
	{
		cout << "Error couldnt LOGIN . Server Disconnected.";
		return;
	}

	int recv_bytes = recv(sock, &success_status, sizeof(success_status), 0);
	if (recv_bytes == 0)
	{
		cout << "Error couldnt LOGIN . Server Disconnected.";
		return;
	}


	if (success_status == 'S')
	{
		
		int r = recv(sock, (char *)loggedStud , sizeof(studentPortal), 0);
		cout << "\n\t\t\t\t\033[0;32mSuccessfully Logged in!\033[0m\n";
		*log_Stat = 1;
		Sleep(2000);
	}
	else if (success_status == 'F')
	{
		cout << "\n\t\t\t\t\033[0;31mCheck your credentials, login failed!\033[0m\n";
		 *log_Stat = 0;
		Sleep(2000);
	}
	else
	{
		cout << "Couldnt connect" << endl;
	}
	return;





}

void TicketPrint(SOCKET sock , studentPortal * logged)
{
start:
	printf("\n\n\n\n\t\t\t\t\Purchase Cafe Tickets:\n");
	printf("\t\t\t\t\033[0;33m----------------------\033[0m\n\n\n");
	printf("\t\t\t\t\033[0;36m1)\033[0m Lunch Ticket \033[0;33m( 70 taka )\033[0m \n\n");
	printf("\t\t\t\t\033[0;36m2)\033[0m Dinner Ticket \033[0;33m( 80 taka )\033[0m\n\n");
	cout << "\t\t\t\t\033[0;31m>> \033[0m";
	int choice;
	scanf("%d", &choice);

	if (choice == 1)
	{
		char buff = 'L';

		send(sock, &buff, sizeof(buff), 0);

		recv(sock, &buff, sizeof(buff), 0);

		if (buff == 'N')
		{
			cout << "\nYou don't have sufficient balance.\n";
			getchar();
			return;
		}
		else if (buff == 'Y')
		{
			cout << "\nYour Lunch ticket has been purchased successfully\n";
			string id; char idT[20];
			sprintf_s(idT, "%llu", logged->roll);
			logged->balance -= 70;
			id = idT;
			

			time_t ttime = time(0);

			string dt = ctime(&ttime);
			// convert string to upper case
			std::for_each(dt.begin(), dt.end(), [](char& c) {
				c = ::toupper(c);
				});

			sf::RenderWindow window(sf::VideoMode(1000, 400), "Lunch Ticket");
			sf::Font font;
			font.loadFromFile("Montserrat.ttf");

			sf::Text text;
			text.setFont(font);
			text.setString(id);
			text.setCharacterSize(28);
			text.setFillColor(sf::Color::Black);
			text.setStyle(sf::Text::Bold);
			text.setPosition(133.0f, 182.0f);

			sf::Font font2;
			font2.loadFromFile("Montserrat.ttf");

			sf::Text text2;
			text2.setFont(font2);
			text2.setString(dt);
			text2.setCharacterSize(13);
			text2.setFillColor(sf::Color::Black);
			text2.setPosition(120.0f, 252.0f);

			
			
			sf::RectangleShape lunchticket(sf::Vector2f(900.0f, 300.0f));
			lunchticket.setPosition(50.0f, 50.0f);
			sf::Texture lunch;
			lunch.loadFromFile("lunch.png");
			lunchticket.setTexture(&lunch);

			while (window.isOpen())
			{
				sf::Event event;
				while (window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						window.close();
				}

				window.clear();
				window.draw(lunchticket);
				window.draw(text);
				window.draw(text2);
				window.display();
			}


			getchar();
			return;
		}
	}
	else if (choice == 2)
	{
		char buff = 'S';

		send(sock, &buff, sizeof(buff), 0);
		recv(sock, &buff, sizeof(buff), 0);

		if (buff == 'N')
		{
			cout << "\nYou don't have sufficient balance.\n";
			getchar();
			return;
		}
		else if (buff == 'Y')
		{
			cout << "\nYour Dinner ticket has been purchased successfully\n";
			logged->balance -= 80;
			string id; char idT[20];
			sprintf_s(idT, "%llu", logged->roll);

			id = idT;

			time_t ttime = time(0);

			string dt = ctime(&ttime);
			// convert string to upper case
			std::for_each(dt.begin(), dt.end(), [](char& c) {
				c = ::toupper(c);
				});

			sf::RenderWindow window(sf::VideoMode(1000, 400), "Dinner Ticket");
			sf::Font font;
			font.loadFromFile("Montserrat.ttf");

			sf::Text text;
			text.setFont(font);
			text.setString(id);
			text.setCharacterSize(28);
			text.setFillColor(sf::Color::White);
			text.setStyle(sf::Text::Bold);
			text.setPosition(133.0f, 182.0f);

			sf::Font font2;
			font2.loadFromFile("Montserrat.ttf");

			sf::Text text2;
			text2.setFont(font2);
			text2.setString(dt);
			text2.setCharacterSize(13);
			text2.setFillColor(sf::Color::White);
			text2.setPosition(120.0f, 252.0f);



			sf::RectangleShape dinnerticket(sf::Vector2f(900.0f, 300.0f));
			dinnerticket.setPosition(50.0f, 50.0f);
			sf::Texture dinner;
			dinner.loadFromFile("dinner.png");
			dinnerticket.setTexture(&dinner);

			while (window.isOpen())
			{
				sf::Event event;
				while (window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						window.close();
				}

				window.clear();
				window.draw(dinnerticket);
				window.draw(text);
				window.draw(text2);
				window.display();
			}

			getchar();
			return; 
		}

	}
	else
	{
		cerr << "Invalid Choice\n";
		getchar();
		goto start;
		return;
	}
	getchar();
	
}

void admission(SOCKET sock)
{
	printf("\n\n\n");
	printf("\t\t\t\tWelcome to the Admission Portal of IUT\n");
	printf("\t\t\t\t\033[0;33m--------------------------------------\033[0m\n\n");
	printf("\t\t\t\t1) Programmes and Seats\n\n");
	printf("\t\t\t\t2) Minimum Requirements\n\n");
	printf("\t\t\t\t\033[0;31m3) Apply Now!\033[0m\n\n");

	int choice;
	cout << "\n\t\t\t\t\>> ";
	scanf("%d", &choice);

	if (choice < 1 && choice > 3)
	{
		cerr << "Invalid Choice!\n";
		getchar();
		return;
	}

	if (choice == 1)
	{
		system("cls");
		printf("\n\n\n\n\t\t\t\tIUT PROGRAMMES  Available Seats \n");
		printf("\t\t\t\t\033[0;33m--------------------------------\033[0m\n\n");
		printf("\t\t\t\t\033[0;33m1)CSE\033[0m\t\t  ---> \033[0;36m 120 Seats\033[0m \n\n");
		printf("\t\t\t\t\033[0;33m2)EEE\033[0m\t\t  ---> \033[0;36m 180 Seats\033[0m \n\n");
		printf("\t\t\t\t\033[0;33m3)ME \033[0m\t\t  ---> \033[0;36m 120 Seats\033[0m \n\n");
		printf("\t\t\t\t\033[0;33m4)SWE\033[0m\t\t  ---> \033[0;36m  60 Seats\033[0m \n\n");
		printf("\t\t\t\t\033[0;33m5)CEE\033[0m\t\t  ---> \033[0;36m 120 Seats\033[0m \n\n");
		printf("\t\t\t\t\033[0;33m6)BTM\033[0m\t\t  ---> \033[0;36m  60 Seats\033[0m \n\n");
		printf("\t\t\t\t\033[0;33m7)IPE\033[0m\t\t  ---> \033[0;36m  60 Seats\033[0m \n\n");

		getchar();
		return;
	}

	else if (choice == 2)
	{
		system("cls");

		printf("\n\n\n\t\t\t\tMinimum Requirements For Admission : \n");
		printf("\t\t\t\t\033[0;33m----------------------------------\033[0m  \n\n");
		printf("\033[0;33mStudent From Host Country:\033[0m\n");
		printf("\033[0;33m--------------------------\033[0m\n\n");
		printf("\033[0;36mSSC Equivalent: \n");
		printf("--------------\033[0m\n\n");
		printf("1) Student From only Science Group can Apply\n");
		printf("2) Minimum GPA 4.50 out of 5.00\n\n");
		printf("\033[0;36mHSC Equivalent: \n");
		printf("--------------\033[0m\n\n");
		printf("1) Student From Only Science Group Can Apply\n");
		printf("2) Minimum GPA 4.50 out of 5.00\n");
		printf("3) Must have A+ grade in Following Subjects:\n");
		printf("\ti)   Physics\n");
		printf("\tii)  Chemistry\n");
		printf("\tiii) Mathematics\n");
		printf("4) Must have A grade in Following Subject:\n");
		printf("\ti)   English\n");

		getchar();
		return;
		
	}

	else if (choice == 3)
	{
		system("cls");
		printf("\n\n\t\t\t\tADMISSION APPLICATION\n");
		printf("\t\t\t\t\033[0;33m---------------------\033[0m\n\n");

		double GPA_SSC, GPA_HSC;
		long long int roll_SSC, roll_HSC;
		string grade_PHY, grade_CHEM, grade_MATHS, grade_ENGLISH;
		string name, Father, Mother, Address, School, College;

		cout << "\033[0;33mEnter Your SSC roll number: \033[0m\n";
		cin >> roll_SSC;

		cout << "\033[0;33mEnter Your HSC roll number: \033[0m\n";
		cin >> roll_HSC;
		gpstart:
		cout << "\033[0;33mEnter Your SSC GPA: \033[0m\n >> ";
		cin >> GPA_SSC;
		if (GPA_SSC < 0 || GPA_SSC > 5)
		{
			cerr << "Invalid Input\n";
			goto gpstart;
			getchar();
			return;
		}

		cout << "\033[0;33mEnter Your HSC GPA: \033[0m\n >> ";
		cin >> GPA_HSC;
		if (GPA_HSC < 0 || GPA_HSC > 5)
		{
			cerr << "Invalid Input\n";
			goto gpstart;
			getchar();
			return;
		}
		grade:
		cout << "\033[0;36m\nEnter your grades for the following subjects:\033[0m\n\n";
		cout << "\033[0;33mPhysics \033[0m>> ";
		cin >> grade_PHY;

		if (grade_PHY[0] < 'A' || grade_PHY[0] > 'F')
		{
			cerr << "Invalid Grade Input\n";
			goto grade;
			getchar();
			return;
		}
		cout << "\033[0;33mChemistry \033[0m>> ";
		cin >> grade_CHEM;
		if (grade_CHEM[0] < 'A' || grade_CHEM[0] > 'F')
		{
			cerr << "Invalid Grade Input\n";
			goto grade;
			getchar();
			return;
		}

		cout << "\033[0;33mMathematics\033[0m >> ";
		cin >> grade_MATHS;
		if (grade_MATHS[0] < 'A' || grade_MATHS[0] > 'F')
		{
			cerr << "Invalid Grade Input\n";
			goto grade;
			getchar();
			return;
		}
		cout << "\033[0;33mEnglish \033[0m>> ";
		cin >> grade_ENGLISH;
		if (grade_ENGLISH[0] < 'A' || grade_ENGLISH[0] > 'F')
		{
			cerr << "Invalid Grade Input\n";
			goto grade;
			getchar();
			return;
		}

		

		//Checking eligibility

		if (GPA_HSC >= 4.50 && GPA_SSC >= 4.50)
		{
			if (grade_PHY == "A+" && grade_CHEM == "A+" && grade_MATHS == "A+" && (grade_ENGLISH == "A+" || grade_ENGLISH == "A"))
			{
				system("cls");
				cout << "\033[0;31m\t\t\t\tCongratulations you are Eligible For Admission Application!\033[0m\n";
				printf_s("\n\n\n");
				for (int i = 0; i < 2; i++)
				{
					for (int j = 0; j < 120; j++)
					{
						printf("-");
						Sleep(7);
					}
					printf("Redirecting to the Data Entry Page....\n");

				}
				fflush(stdin);
				system("cls");
				printf("\n\n");
				cout << "\033[0;33mEnter Student name: \033[0m";
				getchar();
				getline(cin, name);

				cout << "\033[0;33mEnter Father's name: \033[0m";
				getline(cin, Father);

				cout << "\033[0;33mEnter Mother's name: \033[0m";
				getline(cin, Mother);

				cout << "\033[0;33mEnter Address: \033[0m";
				getline(cin, Address);
				
				cout << "\033[0;33mEnter School: \033[0m";
				getline(cin, School);

				cout << "\033[0;33mEnter College: \033[0m";
				getline(cin, College);
				printf("\n\n\n");
				printf("\t\t\t\t\033[0;31mREGISTRATION COMPLETED! Press any key to see details...\033[0m\n");
				getchar();

				system("cls");

				printf("\n\n\n\n\t\t\t\t\033[0;33mDETAILS OF REGISTERED STUDENT\n");
				printf("\t\t\t\t-----------------------------\033[0m\n\n");

				cout << "\033[0;36mStudent Name : \033[0m" << name << endl;
				cout << "\033[0;36mFather's Name: \033[0m" << Father << endl;
				cout << "\033[0;36mMother's Name: \033[0m" << Mother << endl;
				cout << "\033[0;36mAddress      : \033[0m" << Address << endl;
				cout << "\033[0;36mSchool       : \033[0m" << School << endl;
				cout << "\033[0;36mCollege      : \033[0m" << College << endl;
				cout << "\033[0;36mSSC Roll     : \033[0m" << roll_SSC << endl;
				cout << "\033[0;36mHSC roll     : \033[0m" << roll_HSC << endl;
				getchar();
				return;
			}
			else
			{
				system("cls");
				cerr << "\033[0;31m\n\n\n\t\t\t\tSorry! You do not meet the minimum requirement of subject grades!\033[0m\n";
				getchar();
				return;
			}
		}
		else
		{
			system("cls");
			cerr << "\033[0;31m\n\n\n\t\t\t\tSorry! You do not meet the minimum requirement SSC and HSC GPA!\033[0m\n";
			getchar();
			return;
		}
	}
}

void chat(SOCKET sock)
{

	printf("                      ONLY ENTER TEXTS BELOW \033[1;31m 1000 \033[0m CHARACTERS\n");
	Sleep(2500);
	system("cls");
	char buff[2000]; int i = 0;
	printf("\n\n\033[1;32m                             Virtual Assistance      \033[0m \n\n");
	while (true)
	{
		//gotoxy(0, 7 + i);
		cout<<"User  >>  ";
		cin.getline(buff, sizeof(buff));
		if (strlen(buff) > 1000) printf("        \033[1;31mWARNING MAX SIZE CROSSED\033[0m");
		printf("\n\n");
		if (!strncmp(buff, "bye", 3))
		{
			send(sock, (char*)&buff, sizeof(buff), 0);

			//cout << "Terminating chat shortly...." << endl;
			printf_s("\n\n\n");
			for (int i = 0; i < 2; i++)
			{
				for (int j = 0; j < 75; j++)
				{
					printf("-");
					Sleep(7);
				}
				printf("\n");

			}
			fflush(stdin);
			return;
		}

		

		send(sock, (char*)&buff, sizeof(buff), 0);

		recv(sock, (char*)&buff, sizeof(buff), 0);
		//gotoxy(0, 8 + i);

		char temp50[53]; memset(temp50, ' ', sizeof(temp50));
		
		printf(" ");
			for (int i = 1 ,j=0; i <= strlen(buff);i++, j++)
			{
				temp50[j] = buff[i-1];
				if ((i) % 51 == 0)
				{
					temp50[j+1] = 0;
					printf_s("         %50s\n", temp50);
					memset(temp50, ' ', sizeof(temp50));
					j = 0;
					
				}
			}
			temp50[strlen(buff)%50+1 ] =0;
			if (strlen(buff) > 45) printf_s("         %-50s  ", temp50);
			else  printf_s("         %50s  ", temp50);
		printf("\033[0;33m  << assistant\033[0m\n\n\n", buff);
	}

	return; 
}

void gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}