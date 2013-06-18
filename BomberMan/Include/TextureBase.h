#pragma once
#include <SFML\Graphics.hpp>
#include <map>
#include <string>
class CTextureBase
	{
	public:
		sf::Texture** m_textures;
		CTextureBase(void);
		~CTextureBase(void);
	};

