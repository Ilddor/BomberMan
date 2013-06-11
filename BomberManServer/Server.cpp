#include "Server.h"

void CServer::acceptConnections()
{
	fd_set socketTests;
	timeval timeout;
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;
	sockaddr_in socketClientAddr;
	int lenc;
	
	socketTests.fd_count = 1;
	socketTests.fd_array[0] = m_listeningSocket;

	CClient* tmp;

	while(m_accepting && m_clients.size() < 4)
	{
		if(select(1, &socketTests, nullptr, nullptr, &timeout) > 0)
		{
			lenc = sizeof(socketClientAddr);
			tmp = new CClient();
			tmp->m_socket = accept(m_listeningSocket, (sockaddr FAR*)&socketClientAddr, &lenc);
			m_clients.push_back(tmp);
			m_Listeners.push_back(new sf::Thread(&CServer::clientThread, this));
			Sleep(100);
		}
	}
}

void CServer::clientThread()
{
	CClient* client = m_clients.back();

	const int bufSize = 80;
	char buf[bufSize];
	char key[4];
	key[3] = '\0';
	
	while(client->m_connected)
	{
		if(recv(client->m_socket, buf, bufSize, 0) > 0)
		{
			memcpy(key, buf, 3);
			if(strcmp(key, "NME") == 0)
			{
				client->m_name = &buf[3];
			}
			if(strcmp(key, "RDY") == 0)
			{
				client->m_ready = true;
			}
			if(strcmp(key, "DSC") == 0)
			{
				client->m_connected = false;
			}
			if(strcmp(key, "MOV") == 0)
			{
				//TODO move
			}
			if(strcmp(key, "BMB") == 0)
			{
				//TODO bomb
			}
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

	//m_connected = 0;

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
