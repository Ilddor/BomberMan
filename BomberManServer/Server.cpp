#include "Server.h"

void CServer::acceptConnections()
{
	fd_set socketTests;
	timeval timeout;
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;

	while(m_accepting && m_connected < 4)
	{
		if(select(1, &socketTests, nullptr, nullptr, &timeout) > 0)
		{

		}
	}
}

void CServer::server()
{
	while(m_working)
	{

	}
}

CServer::CServer(void)
{
	m_version = MAKEWORD(1,1);
	WSAStartup(m_version, &m_wsas);
	memset(&m_socketAddres, 0, sizeof(m_socketAddres));
	m_socketAddres.sin_family = AF_INET;
	m_socketAddres.sin_port = htons(9999);
	m_socketAddres.sin_addr.s_addr = htonl(INADDR_ANY);

	m_listeningSocket = socket(AF_INET, SOCK_STREAM, 0);

	bind(m_listeningSocket, (sockaddr FAR*)&m_socketAddres, sizeof(m_socketAddres));
	listen(m_listeningSocket, 5);

	m_connected = 0;

	m_accepting = true;
	m_working = true;

	m_acceptingThread = new sf::Thread(&CServer::acceptConnections, this);
	m_acceptingThread->launch();

	m_thread = new sf::Thread(&CServer::server, this);
	m_thread->launch();
}


CServer::~CServer(void)
{
	m_accepting = false;
	m_working = false;

	m_acceptingThread->wait();
	m_thread->wait();
}
