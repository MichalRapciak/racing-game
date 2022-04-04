/// <summary>
/// Michal Rapciak
/// </summary>

#pragma once
#include "Player.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

Player::Player()
{
	loadImage();
	isColliding = false;
	position.x = SCREEN_WIDTH / 2;
	position.y = SCREEN_HEIGHT / 2;
	direction = 180;
	score = 0;
	speed = 0;
	alive = true;
	heading = direction + 270;
	playerSprite.setRotation(heading);
	setPosition(position);  // set the position of the players sprite
}

void Player::loadImage()
// Loads the image for the player object
{
	if (!playerTexture.loadFromFile("ASSETS/IMAGES/Trueno.png"))
	{
		std::cout << "error with player image file";
	}

	playerSprite.setTexture(playerTexture);
	playerSprite.setScale(0.20f, 0.20f);
	playerSprite.setOrigin(64, 128);
	playerSprite.getGlobalBounds();

	m_font.loadFromFile("ASSETS/FONTS/ariblk.ttf");
	scoreText.setFont(m_font);
	scoreText.setCharacterSize(32U);
	scoreText.setString("SCORE: " + std::to_string(score));
	scoreText.setPosition((SCREEN_WIDTH / 2) - 75, 30.0f);

	speedText.setFont(m_font);
	speedText.setCharacterSize(42U);
	speedText.setString(std::to_string(speed) + " KM/H");
	speedText.setPosition((SCREEN_WIDTH / 2) - 75, 840.0f);
}

void Player::movement()
{
	// x = Cos, Y = Sin
	heading = direction + 270;
	float dirRad = direction * 3.14159265359 / 180;
	forwardMovement(dirRad);
	dirRad = direction * 3.14159265359 / 180;
	position += velocity;
	if (!isColliding)
		playerSprite.setPosition(position);
	slowingDownMovement();
}

void Player::forwardMovement(float t_dir)
{
	float avgVel = (sqrt(velocity.y * velocity.y) + sqrt(velocity.x * velocity.x)) / 2;
	avgVel /= 3;
	if (!isColliding)
		playerSprite.setPosition(position);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) // Going forward
	{
		if (velocity.y < 0 && velocity.y > -4)
		{
			velocity.y -= 0.075 * (std::sin(t_dir));
		}
		if (velocity.y > 0 && velocity.y < 4)
		{
			velocity.y -= 0.075 * (std::sin(t_dir));
		}
		if (velocity.x < 0 && velocity.x > -4)
		{
			velocity.x -= 0.075 * (std::cos(t_dir));
		}
		if (velocity.x > 0 && velocity.x < 4)
		{
			velocity.x -= 0.075 * (std::cos(t_dir));
		}
		playerSprite.setRotation(heading);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) // Backing up
	{
		if ((velocity.y < 2.0 && velocity.y > -2.0))
		{
			velocity.y += 0.035 * (std::sin(t_dir));
			velocity.x += 0.035 * (std::cos(t_dir));
		}
		else if (velocity.y > 2.0)
		{
			velocity.y -= 0.075 * (std::sin(t_dir));
			velocity.x += 0.075 * (std::cos(t_dir));
		}
		else if (velocity.y < -2.0)
		{
			velocity.y += 0.075 * (std::sin(t_dir));
			velocity.x += 0.075 * (std::cos(t_dir));
		}
		playerSprite.setRotation(heading);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		direction -= (3 - avgVel);
		velocity.y += 0.025 * (std::sin(t_dir));
		velocity.x += 0.025 * (std::cos(t_dir));
		playerSprite.setRotation(heading);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		direction += (3 - avgVel);
		velocity.y += 0.025 * (std::sin(t_dir));
		velocity.x += 0.025 * (std::cos(t_dir));
		playerSprite.setRotation(heading);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && (sf::Keyboard::isKeyPressed(sf::Keyboard::S)))
	{
		direction += (3 - avgVel);
		velocity.y -= 0.010 * (std::sin(t_dir));
		velocity.x -= 0.010 * (std::cos(t_dir));
		playerSprite.setRotation(heading);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && (sf::Keyboard::isKeyPressed(sf::Keyboard::S)))
	{
		direction -= (3 - avgVel);
		velocity.y -= 0.010 * (std::sin(t_dir));
		velocity.x -= 0.010 * (std::cos(t_dir));
		playerSprite.setRotation(heading);
	}
}

void Player::slowingDownMovement()
{
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && velocity.y < 0)
	{
		velocity.y += 0.05;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && velocity.x < 0)
	{
		velocity.x += 0.05;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && velocity.y > 0)
	{
		velocity.y -= 0.05;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && velocity.x > 0)
	{
		velocity.x -= 0.05;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && (velocity.y < 0.1 && velocity.y > -0.1) && velocity.x < 0)
	{
		velocity.x += 0.05;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && (velocity.y < 0.1 && velocity.y > -0.1) && velocity.x > 0)
	{
		velocity.x -= 0.05;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && (velocity.x < 0.1 && velocity.x > -0.1) && velocity.y < 0)
	{
		velocity.y += 0.05;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && (velocity.x < 0.1 && velocity.x > -0.1) && velocity.y > 0)
	{
		velocity.y -= 0.05;
	}
	if (!isColliding)
		playerSprite.setPosition(position);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (velocity.y < 0)
		{
			velocity.y += 0.10;
		}
		if (velocity.x < 0)
		{
			velocity.x += 0.10;
		}
		if (velocity.y > 0)
		{
			velocity.y -= 0.10;
		}
		if (velocity.x > 0)
		{
			velocity.x -= 0.10;
		}
		if ((velocity.y < 0.1 && velocity.y > -0.1) && velocity.x < 0)
		{
			velocity.x += 0.05;
		}
		if ((velocity.y < 0.1 && velocity.y > -0.1) && velocity.x > 0)
		{
			velocity.x -= 0.05;
		}
		if ((velocity.x < 0.1 && velocity.x > -0.1) && velocity.y < 0)
		{
			velocity.y += 0.05;
		}
		if ((velocity.x < 0.1 && velocity.x > -0.1) && velocity.y > 0)
		{
			velocity.y -= 0.05;
		}
	}
}

void Player::scoreCounting()
{
	float avgVel = (sqrt(velocity.y * velocity.y) + sqrt(velocity.x * velocity.x)) / 2;
	if (avgVel > 1 && avgVel < 2)
	{
		score++;
	}
	if (avgVel > 2 && avgVel < 2.5)
	{
		score += 2;
	}
	if (avgVel > 2.5)
	{
		score += 4;
	}
	scoreText.setString("SCORE: " + std::to_string(score));
	speed = static_cast<int>(avgVel * 30);
	speedText.setString(std::to_string(speed) + " KM/H");
}

sf::Sprite Player::returnSprite()
{
	return playerSprite;
}

void Player::setPosition()
{
	playerSprite.setPosition(200, 40);
}


void Player::setPosition(sf::Vector2f position)
{
	playerSprite.setPosition(position);
}

sf::Vector2f Player::getPosition()
{
	sf::Vector2f pos = playerSprite.getPosition();
	return pos;
}

float Player::getRotation()
{
	float dirRad = direction * 3.14159265359 / 180;
	return direction;
}

sf::FloatRect Player::returnBox()
{
	return playerSprite.getGlobalBounds();
}

sf::Vector2f Player::getVelocity()
{
	return velocity;
}

void Player::setVelocity(sf::Vector2f t_velocity)
{
	velocity = t_velocity;
}

sf::Vector2f Player::returnOrigin()
{
	return playerSprite.getOrigin();
}

sf::Text Player::returnScoreText()
{
	return scoreText;
}


void Player::setAlive(bool t_alive)
{
	alive = t_alive;
}

bool Player::getAlive()
{
	return alive;
}

int Player::getScore()
{
	return score;
}