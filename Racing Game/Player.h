/// <summary>
/// Michal Rapciak
/// </summary>

#pragma once
#include <SFML/Graphics.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Globals.h"

class Player
{
	sf::Texture playerTexture;
	sf::Sprite playerSprite;
	float direction;
	float heading;
	int speed;
	int score;
	bool alive;
	sf::Font m_font;
	sf::Vector2f velocity;
	sf::Vector2f position;

public:

	Player();
	void loadImage();
	void forwardMovement(float t_dir);
	void slowingDownMovement();
	void movement();
	void scoreCounting();

	sf::Text scoreText;
	sf::Text speedText;

	void setPosition();
	void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition();
	void setVelocity(sf::Vector2f t_velocity);
	sf::Vector2f getVelocity();
	float getRotation();

	sf::Text returnScoreText();
	sf::FloatRect returnBox();
	sf::Sprite returnSprite();
	sf::Vector2f returnOrigin();
	int getScore();

	void setAlive(bool t_alive);
	bool getAlive();

	bool isColliding;

};