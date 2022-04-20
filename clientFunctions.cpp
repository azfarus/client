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

	printf_s(" Roll: %llu\n Name: %s\n Email: %s\n Father's Name: %s\n Mother's Name: %s\n Dept: %s\n CG: %.2lf\n", student.roll, student.name, student.email, student.father, student.mother, student.dept, student.CG);
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
			if (c == 'x') return;
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
		
		Sleep(150);
		system("cls");
	}





}

void introScreen2(char* str, int log_stat)
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

		win.display();
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

	std::cout << "\n\n\n\n\n\n\n\n\t\t\t\tPlease Enter your ID and password to log in : \n";
	std::cout << "\n\t\t\t\tID : ";
	cin >> log.id; getchar();
	cout << "\n\t\t\t\tPassword : ";
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
		cout << "\n\t\t\t\tSuccessfully Logged in\n";
		*log_Stat = 1;
		Sleep(2000);
	}
	else if (success_status == 'F')
	{
		cout << "\n\t\t\t\tCheck your credentials, login failed.\n";
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
	printf("Purchase: \n 1) Lunch Ticket (TK. 70)\n 2) Dinner Ticket (Tk. 80)\n");
	int choice;
	cout << " >> ";
	cin >> choice;

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

			string id;
			cout << "Please enter your id: ";
			cin >> id;

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
		return;
	}
	getchar();
	
}

void admission(SOCKET sock)
{
	printf("Welcome to the Admission Portal of IUT\n");
	printf("1) Programmes and Seats\n");
	printf("2) Minimum Requirements\n");
	printf("3) Apply Now!\n");

	int choice;
	cout << " >> ";
	cin >> choice;

	if (choice == 1)
	{
		system("cls");
		printf("        IUT PROGRAMMES   Available Seats \n");
		printf("	----------------------------------\n");
		printf("          1)CSE\t\t  --> 120 Seats \n");
		printf("          2)EEE\t\t  --> 180 Seats \n");
		printf("          3)ME \t\t  --> 120 Seats \n");
		printf("          4)SWE\t\t  -->  60 Seats \n");
		printf("          5)CEE\t\t  --> 120 Seats \n");
		printf("          6)BTM\t\t  -->  60 Seats \n");
		printf("          7)IPE\t\t  -->  60 Seats \n");

		getchar();
		return;
	}

	else if (choice == 2)
	{
		system("cls");

		printf("	Minimum Requirements For Admission:\n");
		printf("	-----------------------------------\n\n");
		printf("Student From Host Country:\n");
		printf("--------------------------\n\n");
		printf("SSC Equivalent: \n");
		printf("--------------\n");
		printf("1) Student From only Science Group can Apply\n");
		printf("2) Minimum GPA 4.50 out of 5.00\n\n");
		printf("HSC Equivalent: \n");
		printf("--------------\n");
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
		printf("\t\tADMISSION APPLICATION\n");
		printf("\t\t---------------------\n");

		double GPA_SSC, GPA_HSC;
		long long int roll_SSC, roll_HSC;
		string grade_PHY, grade_CHEM, grade_MATHS, grade_ENGLISH;
		string name, Father, Mother, Address, School, College;

		cout << "Enter Your SSC GPA: \n >> ";
		cin >> GPA_SSC;
		if (GPA_SSC < 0 || GPA_SSC > 5)
		{
			cerr << "Invalid Input\n";
			getchar();
			return;
		}

		cout << "Enter Your HSC GPA: \n >> ";
		cin >> GPA_HSC;
		if (GPA_HSC < 0 || GPA_HSC > 5)
		{
			cerr << "Invalid Input\n";
			getchar();
			return;
		}

		cout << "Enter your grades for the following subjects:\n";
		cout << "Physics >> ";
		cin >> grade_PHY;

		cout << "Chemistry >> ";
		cin >> grade_CHEM;

		cout << "Mathematics >> ";
		cin >> grade_MATHS;

		cout << "English >> ";
		cin >> grade_ENGLISH;

		cout << "SSC roll number: ";
		cin >> roll_SSC;

		cout << "HSC roll number: ";
		cin >> roll_HSC;

		//Checking eligibility

		if (GPA_HSC >= 4.50 && GPA_SSC >= 4.50)
		{
			if (grade_PHY == "A+" && grade_CHEM == "A+" && grade_MATHS == "A+" && (grade_ENGLISH == "A+" || grade_ENGLISH == "A"))
			{
				system("cls");
				cout << "Congratulations you are Eligible For Admission Application\n";
				cout << "Enter Student name: ";
				getchar();
				getline(cin, name);

				cout << "Enter Father's name: ";
				getline(cin, Father);

				cout << "Enter Mother's name: ";
				getline(cin, Mother);

				cout << "Enter Address: ";
				getline(cin, Address);
				
				cout << "Enter School: ";
				getline(cin, School);

				cout << "Enter College: ";
				getline(cin, College);
				printf("REGISTRATION COMPLETED! Press any key to see details\n");
				getchar();

				system("cls");

				printf("\t\tDETAILS OF REGISTERED STUDENT\n");
				printf("\t\t-----------------------------\n");

				cout << "Student Name : " << name << endl;
				cout << "Father's Name: " << Father << endl;
				cout << "Mother's Name: " << Mother << endl;
				cout << "Address      : " << Address << endl;
				cout << "School       : " << School << endl;
				cout << "College      : " << College << endl;
				cout << "SSC Roll     : " << roll_SSC << endl;
				cout << "HSC roll     : " << roll_HSC << endl;
				getchar();
				return;
			}
			else
			{
				system("cls");
				cerr << "Sorry, you do not meet the minimum requirement of subject grades.\n";
				getchar();
				return;
			}
		}
		else
		{
			system("cls");
			cerr << "Sorry, you do not meet the minimum requirement of SSC and HSC GPA.\n";
			getchar();
			return;
		}
	}
}

void chat(SOCKET sock)
{
	char buff[500];

	while (true)
	{
		cout << "client >> ";
		cin.getline(buff, sizeof(buff));

		if (!strncmp(buff, "bye", 3))
		{
			send(sock, (char*)&buff, sizeof(buff), 0);

			cout << "Terminating chat shortly...." << endl;

			return;
		}

		send(sock, (char*)&buff, sizeof(buff), 0);

		recv(sock, (char*)&buff, sizeof(buff), 0);
		cout << "server >> " << buff << endl;
	}

	return;
}