#pragma once

#include <SFML\Graphics.hpp>
#include <list>
#include <Windows.h>

#include "Misc.h"
#include "Control.h"

class CGame
{
private:
	EGameStates m_state;
	sf::RenderWindow* m_windowPtr;
	sf::Thread* m_serverThread;
	std::list<CControl*> m_controls;

	WSADATA m_wsas;
	WORD m_version;
	sockaddr_in m_socketAddres;
	SOCKET m_listeningSocket;

	bool m_stopServer;
public:
	void setWindowPointer(sf::RenderWindow* ptr);
	void setGameState(EGameStates state);

	void draw();
	void handleEvent(sf::Event& ev);

	void addControl(CControl* control);

	void serwer();
	void startServer();
	void stopServer();

	CGame(void);
	~CGame(void);
};

