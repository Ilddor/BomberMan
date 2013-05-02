#include "Game.h"

#include <iostream>
#include <Windows.h>

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
	while(!m_stopServer)
	{
		std::cout << "LOL" << std::endl;
		Sleep(100);
	}
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
}


CGame::~CGame(void)
{
	for(auto& it: m_controls)
	{
		delete it;
	}
	m_controls.clear();
}