#pragma once
#include "player.h"
#include "texturesheet.h"
class raycast
{
public:
	raycast(int width, player& p, texturesheet& t, sf::RenderWindow& rw);
	~raycast();

	void update();

private:
	player* m_player;
	int m_width;
	texturesheet* m_textureSheet;
	sf::RenderWindow* m_window;
};

