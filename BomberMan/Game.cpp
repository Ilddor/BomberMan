#include "Game.h"

void CGame::setWindowPointer(sf::RenderWindow* ptr)
{
	m_windowPtr = ptr;
}

void CGame::setGameState(EGameStates state)
{
	m_state = state;
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

CGame::CGame(void)
{
	m_state = EGameStates::GS_MENU;
	m_windowPtr = nullptr;
}


CGame::~CGame(void)
{
	for(auto& it: m_controls)
	{
		delete it;
	}
	m_controls.clear();
}