#pragma once
#include "Control.h"
#include "GameObject.h"
#include "PlayerObject.h"
#include <list>
class CGameField :
	public CControl
{
private:
	int m_score;
	int m_lives;
	std::list<CGameObject*> m_objects;
	sf::RectangleShape m_field;
	sf::Vector2f m_position;
	sf::Vector2f m_size;
	sf::Vector2f m_startPos;
	CPlayerObject* temporaryHandleForPlayerObject;

	void generateBorder();
public:
	//Inherited foos
	bool mousePressed(sf::Event::MouseButtonEvent& mouse);
	void KeyPressed(sf::Event::KeyEvent& keyboard);
	void draw(sf::RenderWindow* window);
	bool isObjectAtPos(const sf::Vector2f& pos);
	void ticker(const sf::Clock& clock);
	CGameField(EGameStates state);
	~CGameField(void);
};