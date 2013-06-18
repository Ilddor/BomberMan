#pragma once
#include "Control.h"
#include "GameObject.h"
#include "PlayerObject.h"
#include <list>
#include <map>
#include "TextureBase.h"
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
	CTextureBase m_textureBase;
	//CPlayerObject* temporaryHandleForPlayerObject;

	std::map<int, CPlayerObject*> m_players;

	void generateMap();
public:
	int m_myPlayer;
	//Inherited foos
	bool mousePressed(sf::Event::MouseButtonEvent& mouse);
	void KeyPressed(sf::Event::KeyEvent& keyboard);
	void draw(sf::RenderWindow* window);
	bool isObjectAtPos(const sf::Vector2f& pos);
	void ticker(const sf::Clock& clock);

	void bomb(int x, int y);
	void playerMove(int x, int y, int playerID);
	void addPlayer(int id, int x, int y);
	void setPlayerPos(int x, int y, int playerID);
	sf::Vector2f getPlayerPos();
	bool isPlayerMoving();
	CGameField(EGameStates state);
	~CGameField(void);
};