#include "Game.h"

#include <iostream>
#include <regex>

#include <Windows.h>

#include "TextField.h"

void CGame::setWindowPointer(sf::RenderWindow* ptr)
{
	m_windowPtr = ptr;
}

void CGame::setGameState(EGameStates state)
{
	m_state = state;
	m_focusedControl = nullptr;
	std::cout << m_state << std::endl;
}

CControl* CGame::getControlById(std::string id)
{
	return m_controls.find(id)->second;
}

void CGame::draw()
{
	for(auto& it: m_controls)
	{
		if(it.second->getState() == m_state)
			it.second->draw(m_windowPtr);
	}
}

void CGame::handleEvent(sf::Event& ev)
{
	switch(ev.type)
	{
		case sf::Event::MouseButtonPressed :
			for(auto& it: m_controls)
			{
				if(it.second->getState() == m_state)
				{
					if(it.second->mousePressed(ev.mouseButton))
					{
						m_focusedControl = it.second;
						break;
					}
					else
						m_focusedControl = nullptr;
				}
			}
			break;
		case sf::Event::KeyPressed :
			if(m_focusedControl != nullptr)
				m_focusedControl->KeyPressed(ev.key);
			break;
	}
}

void CGame::addControl(std::string id, CControl* control)
{
	m_controls.insert(std::make_pair(id, control));
}

void CGame::serwer()
{
	m_listeningSocket = socket(AF_INET, SOCK_STREAM, 0); //1h of looking for a bug cos i forgot to add this line-.- I'm stupid
	
	bind(m_listeningSocket, (sockaddr FAR*)&m_socketAddres, sizeof(m_socketAddres));
	listen(m_listeningSocket, 5);

	SOCKET tmp;
	struct sockaddr_in satmp;
	int lenc = sizeof(satmp);
	fd_set socketTests;
	
	timeval timeout;
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;
	while(!m_stopServer)
	{
		socketTests.fd_count = 1;
		socketTests.fd_array[0] = m_listeningSocket;

		if(select(1, &socketTests, nullptr, nullptr, &timeout) > 0)		//used to check if there are connections in queue, we dont want to block thread by accept
		{
			tmp = accept(m_listeningSocket, (sockaddr FAR*)&satmp, &lenc);
			//send(tmp, "LOL", 4, 0);
			//std::cout << "wyslalem" << std::endl;
			closesocket(tmp);
		}
	}
	closesocket(m_listeningSocket);
}

void CGame::startServer()
{
	if(m_serverThread == nullptr)
	{
		m_stopServer = false;
		m_serverThread = new sf::Thread(&CGame::serwer, this);
		m_serverThread->launch();
	}
}

void CGame::stopServer()
{
	if(m_serverThread != nullptr)
	{
		m_stopServer = true;
		m_serverThread->wait();
		delete m_serverThread;
		m_serverThread = nullptr;
	}
}

void CGame::connectToServer()
{
	sf::String ip = ((CTextField*)getControlById("ip(JOIN)"))->getString();

	std::regex regex ("^([[:digit:]]{1,3}.){3}[[:digit:]]{1,3}$");

	if(std::regex_match(ip.toAnsiString(), regex))
	{
		m_joinAddres.sin_family = AF_INET;
		m_joinAddres.sin_port = htons(9999);
		m_joinAddres.sin_addr.s_addr = inet_addr(ip.toAnsiString().c_str());

		m_joinSocket = socket(AF_INET, SOCK_STREAM, 0);
		int result = connect(m_joinSocket, (sockaddr FAR*)&m_joinAddres, sizeof(m_joinAddres));
		if(result == SOCKET_ERROR)
		{
			MessageBox(NULL, L"Pod podanym adresem nie znajduje siê serwer gry.", L"B³¹d", MB_OK);
		}
		else
		{
			setGameState(EGameStates::GS_JOINED);
		}
	}
	else
	{
		MessageBox(NULL, L"Podany adres ip jest nieprawid³owy.", L"B³¹d", MB_OK);
	}
}

void CGame::disconnect()
{
	closesocket(m_joinSocket);
}

CGame::CGame(void)
{
	m_serverThread = nullptr;
	m_focusedControl = nullptr;
	m_state = EGameStates::GS_MENU;
	m_windowPtr = nullptr;
	m_stopServer = true;

	//Socket initialization
	m_version = MAKEWORD(1,1);
	WSAStartup(m_version, &m_wsas);
	memset(&m_socketAddres, 0, sizeof(m_socketAddres));
	m_socketAddres.sin_family = AF_INET;
	m_socketAddres.sin_port = htons(9999);
	m_socketAddres.sin_addr.s_addr = htonl(INADDR_ANY);
}


CGame::~CGame(void)
{
	for(auto& it: m_controls)
	{
		delete it.second;
	}
	m_controls.clear();

	WSACleanup();
}