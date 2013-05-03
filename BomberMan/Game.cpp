#include "Game.h"

#include <iostream>

#include <Windows.h>
//#include <winsock2.h>

void CGame::setWindowPointer(sf::RenderWindow* ptr)
{
	m_windowPtr = ptr;
}

void CGame::setGameState(EGameStates state)
{
	m_state = state;
	std::cout << m_state << std::endl;
}

void CGame::draw()
{
	for(auto& it: m_controls)
	{
		if(it->getState() == m_state)
			it->draw(m_windowPtr);
	}
}

void CGame::handleEvent(sf::Event& ev)
{
	switch(ev.type)
	{
		case sf::Event::MouseButtonPressed :
			for(auto& it: m_controls)
			{
				if(it->getState() == m_state)
					it->mousePressed(ev.mouseButton);
			}
			break;
	}
}

void CGame::addControl(CControl* control)
{
	m_controls.push_back(control);
}

void CGame::serwer()
{
	m_listeningSocket = socket(AF_INET, SOCK_STREAM, 0); //1h of looking for a bug cos i forgot to add this line-.- I'm stupid
	
	bind(m_listeningSocket, (sockaddr FAR*)&m_socketAddres, sizeof(m_socketAddres));
	listen(m_listeningSocket, 5);

	SOCKET tmp;
	struct sockaddr_in satmp;
	int lenc = sizeof(satmp);
	//while(!m_stopServer)
	//{
		tmp = accept(m_listeningSocket, (sockaddr FAR*)&satmp, &lenc);
		send(tmp, "LOL", 4, 0);
		std::cout << "wyslalem" << std::endl;
		//Sleep(1000);
		closesocket(tmp);
		//std::cout << "LOL" << std::endl;
		//Sleep(100);
	//}
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

CGame::CGame(void)
{
	m_serverThread = nullptr;
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
		delete it;
	}
	m_controls.clear();

	WSACleanup();
}