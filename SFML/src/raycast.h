#pragma once
#include "player.h"
#include "texturesheet.h"
class raycast
{
public:
	raycast(int width, int height, player& p, texturesheet& t, sf::RenderWindow& rw);
	~raycast();

	void update();

private:
	player* m_player;
	int m_width, m_height;
	texturesheet* m_textureSheet;
	sf::RenderWindow* m_window;
};

