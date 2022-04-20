#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <cstring>
#include <string.h>
#include <Windows.h>
#include <conio.h>
#include <stdbool.h>
#include <ctype.h>
#include <ctime>
#include <algorithm>



#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define ipaddress "127.0.0.1"
#define xthresh 450
#define ythresh 200

#pragma comment (lib, "ws2_32.lib")

class Button {
public:
	int buttpos_x, buttpos_y;
	int buttwidth, buttheight;
	sf::RectangleShape butt;
	sf::Texture n, f, p, jama;
	sf::SoundBuffer buf;
	sf::Sound click;


	void create(int x, int y, int w, int h , std::string Nn, std::string Ff, std::string Pp)
	{
		butt.setSize(sf::Vector2f(w, h));

		//butt.setOrigin(sf::Vector2f(w / 2.0, h / 2.0));
		butt.setPosition(sf::Vector2f(x, y));
		buttpos_x = x; buttpos_y = y;
		buttwidth = w; buttheight = h;
		n.loadFromFile(Nn);
		f.loadFromFile(Ff);
		p.loadFromFile(Pp);
		buf.loadFromFile("mouse2.wav");
		click.setBuffer(buf);
		butt.setTexture(&n);

	}
	int onButton(sf::RenderWindow& window , char * userInput , const char * set)
	{
		sf::Vector2i mousepos(sf::Mouse::getPosition(window));
		int mouse_x = mousepos.x;
		int mouse_y = mousepos.y;

		if ((buttpos_x < mouse_x && buttpos_x + buttwidth > mouse_x) && (buttpos_y < mouse_y && buttpos_y + buttheight > mouse_y))
		{
			butt.setTexture(&f);
			//std::cout << "Button hovering\n";

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{

				butt.setTexture(&p);
				strcpy(userInput, set);
				window.draw(butt);
				window.display();
				click.play();
				Sleep(200);
				window.close();
				
				return 2;
			}
			return 1;
		}
		else
		{
			butt.setTexture(&n);
			return 0;
		}


	}

	void setTexture(std::string filename)
	{

		if (!jama.loadFromFile(filename))
		{
			std::cout << "Failed to load texture\n";
		}
		butt.setTexture(&jama);
		return;

	}
	void drawButton(sf::RenderWindow& window)
	{
		window.draw(butt);
	}
};


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
	long long int balance;
}studentPortal;

typedef struct _logininfo
{
	unsigned long long id;
	unsigned long long hash;
}logininfo;

enum IN {

	IN_BACK = 8,
	IN_RET = 13

};




SOCKET connectToServer(std::string ipAddress, unsigned int port);
void faculties(SOCKET sock);
void services(SOCKET sock); //New function for printing services
void introScreen(char* str, int log_Stat);
void searchFaculties_client(SOCKET sock);
void Portal(SOCKET sock, studentPortal* loggedStud, int* loginS);
void login_client(SOCKET sock , int *log_Stat, studentPortal* loggedStud);//New function addded
void introScreen2(char* str, int log_stat);
unsigned long long Hash(const char* str);
void TicketPrint(SOCKET sock, studentPortal* logged);


//New Function
void admission(SOCKET sock);

void chat(SOCKET sock);



using namespace std;





