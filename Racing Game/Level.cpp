/// <summary>
/// Michal Rapciak
/// </summary>

#pragma once
#include "Level.h"
#include "Player.h"
#include <math.h>
#include <iostream>
#include <fstream>

Level::Level()
{
	initialiseArrays();
	initialiseMap();
}

void Level::initialiseMap()
{
	if (!m_bgText.loadFromFile("ASSETS/IMAGES/bg1.png"))
	{
		std::cout << "Can't load background" << std::endl;
	}
	m_bgSprite.setTexture(m_bgText);
	m_bgSprite.setPosition(0, 0);
	m_bgSprite.setScale((5.0 / 6.0) * 5, (5.0 / 6.0) * 5);
	sf::Vector2f pos = { 1600, 900 };
	m_levelView.reset(sf::FloatRect(pos.x / 2, pos.y / 2, 1600, 900));
	m_levelView.setCenter(pos);
	m_levelView.zoom(0.40);

	m_miniMap.reset(sf::FloatRect(0,0,1600,900));
	m_miniMap.zoom(1.5);
	m_miniMap.setCenter(pos);
	m_miniMap.setViewport(sf::FloatRect(0.73f, 0.035f, 0.25f, 0.25f));
}

void Level::initialiseArrays()
{
	std::ifstream level1{ "ASSETS/LEVELS/level1.txt" };
	if (!level1.is_open()) std::cout << "Error loading file" << std::endl;

	for (int i = 0; i != Y_BOXES; ++i) {
		for (int j = 0; j != X_BOXES; ++j) {
			level1 >> levelGrid1[i][j];
		}
	}
}

int Level::returnTile(sf::Vector2f t_playerPos)
{
	int xTile = t_playerPos.x / 125;
	int yTile = t_playerPos.y / 125;
	tile = levelGrid1[yTile][xTile];
	return tile;
}