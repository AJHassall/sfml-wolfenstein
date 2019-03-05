#include "texturesheet.h"


texturesheet::texturesheet()
{
	LOG("texture sheet created\n");

}


texturesheet::~texturesheet()
{
	LOG("texture sheet destroyed\n")
}

void texturesheet::updateTexture(const std::string& path)
{

		for (uint8_t x = 0; x < 11; x++)
		{
			sf::Image img;
			//FindFirstFileA("D:\\Dev\\C++\\SFML\\res\\", s);
			img.loadFromFile(path+textureNames[x]);
			this->update(img.getPixelsPtr(), m_TEXTURE_WIDTH, m_TEXTURE_HEIGHT, m_TEXTURE_WIDTH * x, 0);
		}
	
}


