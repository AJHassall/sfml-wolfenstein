#pragma once

#include <string>
#include "SFML/Graphics.hpp"

class texturesheet :public sf::Texture {


public:
	texturesheet(const std::wstring& path, uint8_t numberOfFiles);

private:

	const int8_t m_TEXTURE_WIDTH=64, m_TEXTURE_HEIGHT=64;
};