#include <string>
#include <iostream>
#include <filesystem>
#include "texturesheet.h"






namespace fs = std::experimental::filesystem;

texturesheet::texturesheet(const std::wstring& path,uint8_t numberOfFiles) {

	this->create(m_TEXTURE_WIDTH * numberOfFiles, m_TEXTURE_HEIGHT);
	
	int8_t x = 0;
	for (const auto & entry : fs::directory_iterator(path))
	{
		std::cout << entry.path() << std::endl;

		sf::Image img;
		if(!img.loadFromFile(entry.path().string()))
			std::cout<<"load failed\n";
		this->update(img.getPixelsPtr(), m_TEXTURE_WIDTH, m_TEXTURE_HEIGHT, m_TEXTURE_WIDTH * x, 0);
		x++; 

	}
}
