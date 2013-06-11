#pragma once

#include <iostream>
#include <Windows.h>
#include <SFML\System.hpp>
#include <list>
#include <queue>

#include "Client.h"

class CServer
{
private:
	WSADATA m_wsas;
	WORD m_version;
	sockaddr_in m_socketAddres;
	SOCKET m_listeningSocket;
	std::list<CClient*> m_clients;

	sf::Mutex m_mutexBroadcaster;
	std::queue<std::string> m_broadcastQueue;

	//int m_connected;

	sf::Thread* m_acceptingThread;
	std::list<sf::Thread*> m_Listeners;
	bool m_accepting;
	sf::Thread* m_thread;
	bool m_working;
public:
	void acceptConnections();
	void clientThread();
	void server();

	CServer(void);
	~CServer(void);
};

