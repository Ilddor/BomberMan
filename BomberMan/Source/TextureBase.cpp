#include "TextureBase.h"


CTextureBase::CTextureBase(void)
{
	/*0 - bomba
	1 - block breakable
	2 - block unbreakable
	3 - player
	4 - explosion

	bomba 3
	block b 1
	block u 1
	player 16
	explosion 27*/
	m_textures = new sf::Texture * [5];
	//Bomba
	m_textures[0] = new sf::Texture[3];
	m_textures[0][0].loadFromFile("Resources/Game/Bombs/bomb_0.png");
	m_textures[0][1].loadFromFile("Resources/Game/Bombs/bomb_1.png");
	m_textures[0][2].loadFromFile("Resources/Game/Bombs/bomb_2.png");
	//Block breakable
	m_textures[1] = new sf::Texture[1];
	m_textures[1][0].loadFromFile("Resources/Game/Field/breakable0.png");
	//Block unbreakable
	m_textures[2] = new sf::Texture[1];
	m_textures[2][0].loadFromFile("Resources/Game/Field/unbreakable0.png");
	//Player
	m_textures[3] = new sf::Texture[16];
	std::string path = "Resources/Game/Players/player1";
	std::string states[4] = {"down","left","right","up"};
	int counter = 1;
	int state = 0;
	for(int i = 0; i < 12; i++){
		m_textures[3][i].loadFromFile(path + "_" + states[state] + "_" + (char)(counter + '0') + ".png");
		counter++;
		if(counter > 3){
			counter = 1;
			state++;
		}
	}
	for(int i = 0; i < 4; i++){
		m_textures[3][12 + i].loadFromFile(path + "_death_" + (char)(i+'1') + ".png");
		counter++;
		if(counter > 3){
			counter = 0;
			state++;
		}
	}
	//Explosion
	m_textures[4] = new sf::Texture[27];
	path = "Resources/Game/Explosion/explosion_";
	std::string place = "mid";
	std::string tmp;
	for(int id = 0; id < 9; id++)
	{
		if(id == 1)
			place = "up";
		else if(id == 2)
			place = "down";
		else if(id == 3)
			place = "left";
		else if(id == 4)
			place = "right";
		else if(id == 5)
			place = "top";
		else if(id == 6)
			place = "bot";
		else if(id == 7)
			place = "west";
		else if(id == 8)
			place = "east";
		for(int i = 0; i < 3; i++)
		{
			tmp = path + (char)(i+'0') + "_" + place + ".png";
			m_textures[4][i+id*3].loadFromFile(tmp);
		}
	}
}


CTextureBase::~CTextureBase(void)
	{
	}
