#pragma once

#include <Windows.h>

#include <SFML\Graphics.hpp>

class CPlayer
{
private:
	bool m_host;
	sf::String m_name;
	int m_id;
	bool m_alive;

	sf::Vector2f m_position;
	sf::Vector2f m_destination;
public:
	sf::Font m_font;
	sf::Text m_text;
	sf::Mutex m_mutex;
	SOCKET m_connectedSocket;
	sf::Thread* m_thread;

	void setName(sf::String name);
	void setPosition(sf::Vector2f pos);
	void setDestination(sf::Vector2f dst);

	sf::String getName();
	sf::Vector2f getPosition();
	sf::Vector2f getDestination();
	bool isMoving();

	void receivePackets();

	CPlayer(SOCKET socket);
	CPlayer(void);
	~CPlayer(void);
};

