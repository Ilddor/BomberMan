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
	if(m_state == EGameStates::GS_CREATE || m_state == EGameStates::GS_JOINED)
	{
		for(auto& it: m_players)
		{
			it->m_mutex.lock();
			m_windowPtr->draw(it->m_text);
			it->m_mutex.unlock();
		}
	}
}

void CGame::ticker(const sf::Clock& clock)
{
	for(auto& it: m_controls)
		it.second->ticker(clock);
	if(m_state == EGameStates::GS_GAME)
	{
		/*if(!m_gameField->isPlayerMoving() && (clock.getElapsedTime() - m_lastSend).asMilliseconds() > 50)
		{
			bool tmp = false;
			char msg[10] = {'\0'};
			char msg2[10] = {'\0'};
			sprintf(msg2, "POS%02d%02d", (int)m_gameField->getPlayerPos().x,  (int)m_gameField->getPlayerPos().y);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				//playerMove(0, -1, m_myPlayer);
				sprintf(msg, "MOV%02d%02d", 0, -1);
				tmp = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				//playerMove(0, 1, m_myPlayer);
				sprintf(msg, "MOV%02d%02d", 0, 1);
				tmp = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				//playerMove(-1, 0, m_myPlayer);
				sprintf(msg, "MOV%02d%02d", -1, 0);
				tmp = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				//playerMove(1, 0, m_myPlayer);
				sprintf(msg, "MOV%02d%02d", 1, 0);
				tmp = true;
			}
			if(tmp)
			{
				//m_queueMutex.lock();
				send(m_joinSocket, msg2, 10, 0);
				send(m_joinSocket, msg, 10, 0);
				//m_queueMutex.unlock();
				m_lastSend = clock.getElapsedTime();
			}
		}*/
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
			if(m_state == EGameStates::GS_GAME)
			{
				char msg[10] = {'\0'};
				if(!m_gameField->isPlayerMoving())
				{
					bool tmp = false;
					char msg[10] = {'\0'};
					char msg2[10] = {'\0'};
					sprintf(msg2, "POS%02d%02d", (int)m_gameField->getPlayerPos().x,  (int)m_gameField->getPlayerPos().y);
					if (ev.key.code == sf::Keyboard::Up)
					{
						//playerMove(0, -1, m_myPlayer);
						sprintf(msg, "MOV%02d%02d", 0, -1);
						tmp = true;
					}
					else if (ev.key.code == sf::Keyboard::Down)
					{
						//playerMove(0, 1, m_myPlayer);
						sprintf(msg, "MOV%02d%02d", 0, 1);
						tmp = true;
					}
					else if (ev.key.code == sf::Keyboard::Left)
					{
						//playerMove(-1, 0, m_myPlayer);
						sprintf(msg, "MOV%02d%02d", -1, 0);
						tmp = true;
					}
					else if (ev.key.code == sf::Keyboard::Right)
					{
						//playerMove(1, 0, m_myPlayer);
						sprintf(msg, "MOV%02d%02d", 1, 0);
						tmp = true;
					}
					/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
					{
						sprintf(msg, "BMB%02d%02d", (int)m_gameField->getPlayerPos().x, (int)m_gameField->getPlayerPos().y);
						tmp = true;
					}*/
					if(tmp)
					{
						//m_queueMutex.lock();
						send(m_joinSocket, msg2, 10, 0);
						send(m_joinSocket, msg, 10, 0);
						//m_queueMutex.unlock();
						//m_lastSend = clock.getElapsedTime();
					}
				}
				if (ev.key.code == sf::Keyboard::Space && !m_gameField->isPlayerDead())
				{
					sprintf(msg, "BMB%02d%02d", (int)m_gameField->getPlayerPos().x, (int)m_gameField->getPlayerPos().y);
					//send(m_joinSocket, msg2, 10, 0);
					//m_queueMutex.lock();
					send(m_joinSocket, msg, 10, 0);
					//m_queueMutex.unlock();
				}
			}
			/*for(auto& it: m_controls)		//you don't need to put this loop here cuz for gamefield instruction above would send key events when it has focus(imean when you click on it.
											//This loop caused problems with textfields
			{
				if(it.second->getState() == m_state)
				{
					it.second->KeyPressed(ev.key);
				}
			}  */
			break;
	}
}

void CGame::addControl(std::string id, CControl* control)
{
	m_controls.insert(std::make_pair(id, control));
	if(id == "gameField(GAME)")
		m_gameField = static_cast<CGameField*>(control);
}

void CGame::serwer()
{
	/*sf::Font font;

	font.loadFromFile("Resources/arial.ttf");
	sf::String name = ((CTextField*)getControlById("name(CREATE)"))->getString();
	CPlayer* ownPlayer = new CPlayer();
	ownPlayer->setName(name);

	ownPlayer->m_font = font;
	ownPlayer->m_text.setPosition(sf::Vector2f(10,10));
	ownPlayer->m_text.setString(ownPlayer->getName());
	ownPlayer->m_text.setCharacterSize(20);
	ownPlayer->m_text.setColor(sf::Color::Red);
	ownPlayer->m_text.setFont(ownPlayer->m_font);
	ownPlayer->m_text.setStyle(sf::Text::Regular);

	//player->m_thread = new sf::Thread(&CPlayer::receivePackets, ownPlayer);

	m_players.push_back(ownPlayer);*/

	//m_listeningSocket = socket(AF_INET, SOCK_STREAM, 0); //1h of looking for a bug cos i forgot to add this line-.- I'm stupid
	
	//bind(m_listeningSocket, (sockaddr FAR*)&m_socketAddres, sizeof(m_socketAddres));
	//listen(m_listeningSocket, 5);
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

void CGame::listenerThread()
{
	char buf[80]  = {'\0'};
	char buf2[80] = {'\0'};
	char key[4];
	key[3] = '\0';

	while(m_joined)
	{
		//m_queueMutex.lock();
		int res = recv(m_joinSocket, buf, 80, 0);
		//m_queueMutex.unlock();
		if(res > 0)
		{
			std::cout << buf << std::endl;
			//m_listQueue.push(buf);
			//m_queueMutex.unlock();
			memcpy(key, buf, 3);
			if(strcmp(key, "STR") == 0)
			{
				memcpy(buf2, &buf[3], 2);
				buf2[2] = '\0';
				m_gameField->m_myPlayer = atoi(buf2);
				memcpy(buf2, &buf[5], 2);
				buf2[2] = '\0';
				m_playersCount = atoi(buf2);
				setGameState(EGameStates::GS_GAME);
			}
			if(strcmp(key, "PLR") == 0)
			{
				int id, x, y;
				for(int i = 0; i < m_playersCount; ++i)
				{
					memcpy(buf2, &buf[4+(i*7+0)], 2);
					buf2[2] = '\0';
					id = atoi(buf2);
					memcpy(buf2, &buf[4+(i*7+2)], 2);
					buf2[2] = '\0';
					x = atoi(buf2);
					memcpy(buf2, &buf[4+(i*7+4)], 2);
					buf2[2] = '\0';
					y = atoi(buf2);
					m_gameField->addPlayer(id, x, y);
				}
			}
			if(strcmp(key, "MOV") == 0)
			{
				int id, x, y;
				memcpy(buf2, &buf[3], 2);
				buf2[2] = '\0';
				id = atoi(buf2);
				memcpy(buf2, &buf[5], 2);
				buf2[2] = '\0';
				x = atoi(buf2);
				memcpy(buf2, &buf[7], 2);
				buf2[2] = '\0';
				y = atoi(buf2);
				m_gameField->playerMove(x, y, id);
			}
			if(strcmp(key, "POS") == 0)
			{
				int id, x, y;
				memcpy(buf2, &buf[3], 2);
				buf2[2] = '\0';
				id = atoi(buf2);
				memcpy(buf2, &buf[5], 2);
				buf2[2] = '\0';
				x = atoi(buf2);
				memcpy(buf2, &buf[7], 2);
				buf2[2] = '\0';
				y = atoi(buf2);
				m_gameField->setPlayerPos(x, y, id);
			}
			if(strcmp(key, "BMB") == 0)
			{
				int x, y;
				memcpy(buf2, &buf[3], 2);
				buf2[2] = '\0';
				x = atoi(buf2);
				memcpy(buf2, &buf[5], 2);
				buf2[2] = '\0';
				y = atoi(buf2);
				m_gameField->bomb(x, y);
			}
		}
		//std::cout << "lol" << std::endl;
	}
}

void CGame::connectToServer()
{
	sf::String ip = ((CTextField*)getControlById("ip(JOIN)"))->getString();
	sf::String name = ((CTextField*)getControlById("name(JOIN)"))->getString();

	std::regex regex ("^([[:digit:]]{1,3}\\.){3}[[:digit:]]{1,3}$");
	std::regex regex2 ("^.+&");

	//if(std::regex_match(ip.toAnsiString(), regex) && std::regex_match(name.toAnsiString(), regex2))
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
			m_joined = true;
			m_listeningThread = new sf::Thread(&CGame::listenerThread, this);
			m_listeningThread->launch();
			std::string tmp = "NME"+name.toAnsiString();
			send(m_joinSocket, tmp.c_str(), tmp.length()+1, 0);	//TODO!
			setGameState(EGameStates::GS_JOINED);
		}
	}
	//else
	//{
	//	MessageBox(NULL, L"Podany adres ip jest nieprawid³owy, lub nie wpisano poprawnego nicku", L"B³¹d", MB_OK);
	//}
}

void CGame::disconnect()
{
	send(m_joinSocket, "DSC", 4, 0);
	m_joined = false;
	closesocket(m_joinSocket);
}

void CGame::rdy()
{
	send(m_joinSocket, "RDY", 4, 0);
}

CGame::CGame(void)
{
	m_serverThread = nullptr;
	m_focusedControl = nullptr;
	m_state = EGameStates::GS_MENU;
	m_windowPtr = nullptr;
	m_stopServer = true;
	m_joined = false;

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
	m_listeningThread->terminate();
	for(auto& it: m_controls)
	{
		delete it.second;
	}
	m_controls.clear();

	WSACleanup();
}