/// <summary>
/// Michal Rapciak
/// </summary>

#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include "Globals.h"

class Enemy
{
	sf::Texture enemyTexture;
	sf::Sprite enemySprite;
	float direction;
	float heading;
	int speed;
	int multiplier;
	int randomNo;
	bool alive;
	bool turning;
	sf::Clock cooldown;
	sf::Vector2f level1Points[24];
	bool level1CrossedPoint[24];
	sf::Vector2f currentPoint;
	sf::Vector2f velocity;
	sf::Vector2f position;

public:

	Enemy();
	void setupPoints();
	void loadImage();
	void movement();
	sf::Sprite returnSprite();
	void setPosition();
	bool isColliding;
	void updateEnemyPos();
	void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition();
	float getRotation();
	sf::FloatRect returnBox();
	sf::Vector2f getVelocity();
	void setVelocity(sf::Vector2f t_velocity);
	void addVelocity(sf::Vector2f t_velocity);
	sf::Vector2f returnOrigin();
	void setAlive(bool t_alive);
	bool getAlive();
};