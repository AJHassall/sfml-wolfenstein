#include "raycast.h"

#include <cmath>
#include "SFML/Graphics.hpp"

raycast::raycast(int width, player & p, texturesheet& t, sf::RenderWindow& rw):
	m_width(width), m_player(&p), m_textureSheet(&t),m_window(&rw)
{

}

raycast::~raycast()
{
}
using namespace std;
void raycast::update()
{

	int WorldMap[10][10] = {
		{1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1} };



	auto _player= m_player->getPositionAndDirection();
	for (int x = 0; x < m_width; x++)
	{

		double planeX = _player.yDir, planeY = -_player.xDir;
		double cameraX = 2 * x / double(m_width) - 1; //x-coordinate in camera space

		double rayDirX = _player.xDir + planeX * cameraX;
		double rayDirY = _player.yDir + planeY * cameraX;

		int mapX = int(_player.x);
		int mapY = int(_player.y);

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = std::abs(1 / rayDirX);
		double deltaDistY = std::abs(1 / rayDirY);
		double perpWallDist;
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (_player.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - _player.x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (_player.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - _player.y) * deltaDistY;
		}

		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (WorldMap[mapX][mapY] > 0) hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if (side == 0) perpWallDist = (mapX - _player.x + (1 - stepX) / 2) / rayDirX;
		else           perpWallDist = (mapY - _player.y + (1 - stepY) / 2) / rayDirY;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(300 / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + 300 / 2;
		if (drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + 300 / 2;
		if (drawEnd >= 300)drawEnd = 300- 1;



		sf::Sprite s = sf::Sprite(*m_textureSheet, sf::IntRect(200, 0, 1, 64));
		s.setPosition(x, drawStart);

		double yscale = double(drawEnd - drawStart) / 64;
		s.setScale(1, yscale);
		m_window->draw(s);
		
	}
}
