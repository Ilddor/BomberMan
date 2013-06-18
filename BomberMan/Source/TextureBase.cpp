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
}


CTextureBase::~CTextureBase(void)
	{
	}
