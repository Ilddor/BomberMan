#include "PlayerObject.h"
#include <iostream>
#include <string>

void CPlayerObject::KeyPressed(sf::Event::KeyEvent& keyboard)
{
		std::cout << "Ide do gory" << std::endl;
}

void CPlayerObject::animate()
{
	m_animationState += m_animationMultiplier;
	if(m_direction != EDirections::D_DEATH){
		if(m_animationState == 2)
			m_animationMultiplier = -1;
		if(m_animationState == 0)
			m_animationMultiplier = 1;
	}
	else {
		if(m_animationState == 3)
			m_animationMultiplier = -1;
		if(m_animationState == 0)
			m_animationMultiplier = 1;
	}
	if(m_direction == EDirections::D_SOUTH)
		m_sprite.setTexture(m_textures[0 + m_animationState]);	
	else if(m_direction == EDirections::D_WEST)
		m_sprite.setTexture(m_textures[3 + m_animationState]);
	else if(m_direction == EDirections::D_EAST)
		m_sprite.setTexture(m_textures[6 + m_animationState]);
	else if(m_direction == EDirections::D_NORTH)
		m_sprite.setTexture(m_textures[9 + m_animationState]);
	else
		m_sprite.setTexture(m_textures[12 + m_animationState]);		
}

void CPlayerObject::move(int x, int y)
{
	sf::Vector2f goalPos = calculatePositionOnGameField(x,y);
	sf::Vector2f moveVector(0,0);
	if(goalPos.x < m_position.x)
		moveVector.x = -1;
	else if(goalPos.x > m_position.x)
		moveVector.x = 1;
	if(goalPos.y < m_position.y)
		moveVector.y = -1;
	else if(goalPos.y > m_position.y)
		moveVector.y = 1;
	if(!isObjectAtPos(m_position + moveVector)){
		if(moveVector.x < 0)
			m_direction = EDirections::D_WEST;
		else if(moveVector.x > 0)
			m_direction = EDirections::D_EAST;
		else if(moveVector.y < 0)
			m_direction = EDirections::D_NORTH;
		else if(moveVector.y > 0)
			m_direction = EDirections::D_SOUTH;
		m_position += moveVector;
		m_sprite.setPosition(sf::Vector2f(m_fieldPos->x + 16*m_position.x, m_fieldPos->y + 16*m_position.y - 8));
	}
	m_animationState = 1;	
	animate();	
}

void CPlayerObject::draw(sf::RenderWindow* window)
{
	window->draw(m_sprite);
}

void CPlayerObject::destroy()
{

}
void CPlayerObject::loadTextures(int id)
{
	std::string path = "Resources/Game/Players/player";
	path += id + '0';
	std::string states[4] = {"down","left","right","up"};
	int counter = 1;
	int state = 0;
	for(int i = 0; i < 12; i++){
		m_textures[i].loadFromFile(path + "_" + states[state] + "_" + (char)(counter + '0') + ".png");
		counter++;
		if(counter > 3){
			counter = 1;
			state++;
		}
	}
	for(int i = 0; i < 4; i++){
		m_textures[12 + i].loadFromFile(path + "_death_" + (char)(i+'1') + ".png");
		counter++;
		if(counter > 3){
			counter = 0;
			state++;
		}
	}
	/*
		m_texture.loadFromFile("Resources/Game/Players/player1_01.png");		
player1_down_1.png
player1_down_2.png
player1_down_3.png
player1_left_1.png
player1_left_2.png
player1_left_3.png
player1_right_1.png
player1_right_2.png
player1_right_3.png
player1_up_1.png
player1_up_2.png
player1_up_3.png
player1_death_1.png
player1_death_2.png
player1_death_3.png
player1_death_4.png	   */
}
CPlayerObject::CPlayerObject(int id, sf::Vector2f* fieldPos, sf::Vector2f* startPos, std::list<CGameObject*>* objects)
{
	m_direction = EDirections::D_SOUTH;
	m_objects = objects;
	m_fieldPos = fieldPos;
	m_startPos = startPos;
	m_position = *m_startPos;
	loadTextures(id);
	m_animationState = 1;
	m_animationMultiplier = 1;
	m_sprite.setTexture(m_textures[1]);
	m_sprite.setPosition(sf::Vector2f(fieldPos->x + 16*startPos->x, fieldPos->y + 16*startPos->y - 8));
}


CPlayerObject::~CPlayerObject(void)
	{
	}
