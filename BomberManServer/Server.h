#pragma once

#include <iostream>
#include <Windows.h>
#include <SFML\System.hpp>

class CServer
{
private:
	WSADATA m_wsas;
	WORD m_version;
	sockaddr_in m_socketAddres;
	SOCKET m_listeningSocket;

	int m_connected;

	sf::Thread* m_acceptingThread;
	bool m_accepting;
	sf::Thread* m_thread;
	bool m_working;
public:
	void acceptConnections();
	void server();

	CServer(void);
	~CServer(void);
};

