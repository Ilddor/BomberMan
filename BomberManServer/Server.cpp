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
		//std::cout << "check" << std::endl;
		//if(select(1, &socketTests, nullptr, nullptr, &timeout) > 0)
		{
			lenc = sizeof(socketClientAddr);
			tmp = new CClient();
			tmp->m_socket = accept(m_listeningSocket, (sockaddr FAR*)&socketClientAddr, &lenc);
			m_clients.push_back(tmp);
			m_Listeners.push_back(new sf::Thread(&CServer::clientThread, this));
			m_Listeners.back()->launch();
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
	char buf2[bufSize];
	char msg[bufSize];
	
	while(client->m_connected)
	{
		if(recv(client->m_socket, buf, bufSize, 0) > 0)
		{
			std::cout << "Income: " << buf << std::endl;
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
				memcpy(buf2, &buf[3], strlen(buf)-3);
				sprintf(msg, "MOV%02d%s", client->m_id, buf2);
				m_mutexBroadcaster.lock();
				m_broadcastQueue.push(msg);
				m_mutexBroadcaster.unlock();
			}
			if(strcmp(key, "BMB") == 0)
			{
				memcpy(buf2, &buf[3], strlen(buf)-3);
				sprintf(msg, "BMB%s", buf2);
				m_mutexBroadcaster.lock();
				m_broadcastQueue.push(msg);
				m_mutexBroadcaster.unlock();
			}
			if(strcmp(key, "DTH") == 0)
			{
				memcpy(buf2, &buf[3], strlen(buf)-3);
				sprintf(msg, "DTH%02d", client->m_id);
				m_mutexBroadcaster.lock();
				m_broadcastQueue.push(msg);
				m_mutexBroadcaster.unlock();
			}
		}
	}
}

void CServer::server()
{
	while(m_working)
	{
		while(m_game)
		{
			if(m_broadcastQueue.size() > 0)
			{
				std::string msg = m_broadcastQueue.front();
				m_mutexBroadcaster.lock();
				m_broadcastQueue.pop();
				m_mutexBroadcaster.unlock();
				for(auto it: m_clients)
				{
					send(it->m_socket, msg.c_str(), msg.length(), 0);
				}
			}
		}
		std::cout << "Players connected: " << m_clients.size() << std::endl;
		std::string connectedMSG = "PPL"+m_clients.size();
		for(auto it: m_clients)
		{
			send(it->m_socket, connectedMSG.c_str(), connectedMSG.length()+1, 0);
		}
		for(auto it: m_clients)
		{
			std::cout << "Player: " << it->m_name << std::endl;
		}
		bool rdy = true;
		for(auto it: m_clients)
		{
			if(!it->m_ready)
				break;
		}
		if(rdy && m_clients.size() == 4)
		{
			m_game = true;
			Sleep(1000);
			int i = 0;
			for(auto it: m_clients)
			{
				it->m_id = i++;
				send(it->m_socket, "STR", 4, 0);
			}
			std::cout << "Game started" << std::endl;
		}
		Sleep(1000);
	}
}

void CServer::waitTillEnd()
{
	m_thread->wait();
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
	m_game = false;

	m_acceptingThread = new sf::Thread(&CServer::acceptConnections, this);
	m_acceptingThread->launch();

	m_thread = new sf::Thread(&CServer::server, this);
	m_thread->launch();
	std::cout << "Server started" << std::endl;
}

CServer::~CServer(void)
{
	std::cout << "Server stopping" << std::endl;
	m_accepting = false;
	m_working = false;

	m_acceptingThread->wait();
	m_thread->wait();
	closesocket(m_listeningSocket);
}
