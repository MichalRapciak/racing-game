#pragma once
/// <summary>
/// Michal Rapciak
/// </summary>

#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include "Globals.h"
enum class Tile {
	Road,
	Grass,
	Wall
};
class Level
{
	static const int X_BOXES = 64;
	static const int Y_BOXES = 36;
	sf::Texture m_bgText;
	int levelGrid1[Y_BOXES][X_BOXES];
	int tile;

public:
	Level();
	void initialiseArrays();
	void initialiseMap();
	int returnTile(sf::Vector2f t_playerPos);
	sf::View m_levelView;
	sf::View m_miniMap;
	sf::Sprite m_bgSprite;
};