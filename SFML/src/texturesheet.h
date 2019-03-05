#pragma once

#include "includes.h"
#include "SFML/Graphics.hpp"
//#include <fileapi.h>
#include <array>
#include <string>

class texturesheet: public sf::Texture
{
public:
	texturesheet();
	~texturesheet();

	void updateTexture(const std::string& path);

public:
	struct texturelocation
	{
		int X;
		int Y;
	};


private:

	const int m_TEXTURE_WIDTH = 64;
	const int m_TEXTURE_HEIGHT =64;

	std::array < std::string, 11> textureNames{"barrel.png", "bluestone.png", "colorstone.png","eagle.png",
			"greenlight.png","greystone.png","mossy.png","pillar.png","purplestone.png","redbrick.png","wood.png"};

};

