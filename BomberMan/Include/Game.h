#pragma once

#include <SFML\Graphics.hpp>
#include <map>
#include <vector>
#include <Windows.h>

#include "Misc.h"
#include "Control.h"
#include "Player.h"

class CGame
{
private:
	EGameStates m_state;
	sf::RenderWindow* m_windowPtr;
	sf::Thread* m_serverThread;
	std::map<std::string, CControl*> m_controls;
	CControl* m_focusedControl;

	WSADATA m_wsas;
	WORD m_version;
	sockaddr_in m_socketAddres;
	SOCKET m_listeningSocket;

	bool m_stopServer;

	SOCKET m_joinSocket;
	sockaddr_in m_joinAddres;
	bool m_joined;

	std::vector<CPlayer*> m_players;
public:
	void setWindowPointer(sf::RenderWindow* ptr);
	void setGameState(EGameStates state);

	CControl* getControlById(std::string id);

	void draw();
	void ticker(const sf::Clock& clock);
	void handleEvent(sf::Event& ev);

	void addControl(std::string id, CControl* control);

	void serwer();
	void startServer();
	void stopServer();
	
	void connectToServer();
	void disconnect();

	CGame(void);
	~CGame(void);
};

