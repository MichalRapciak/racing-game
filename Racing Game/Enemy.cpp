/// <summary>
/// Michal Rapciak
/// </summary>

#pragma once
#include "Enemy.h"
#include <math.h>
#include <iostream>
#include <random>

Enemy::Enemy()
{
	setupPoints();
	loadImage();
	srand(time(nullptr));
	position.x = SCREEN_WIDTH / 3;
	position.y = SCREEN_HEIGHT / 3;
	direction = 0;
	heading = direction + 180;
	isColliding = false;
	alive = true;
	turning = false;
	currentPoint = level1Points[0];
	velocity = (currentPoint - position) / 500.0f;
	enemySprite.setRotation(heading);
	cooldown.restart();
	setPosition(position);  // set the position of the players sprite
}

void Enemy::setupPoints()
{
	level1Points[0] = { 3200,350 };
	level1Points[1] = { 2200,2500 };
	level1Points[2] = { 4225,1500 };
	level1Points[3] = { 3125,-300 };
	level1Points[4] = { 5550,475 };
	level1Points[5] = { 5400,1775 };
	level1Points[6] = { 6025,1125 };
	level1Points[7] = { 6375,075 };
	level1Points[8] = { 8450,650 };
	level1Points[9] = { 7500,2650 };
	level1Points[10] = { 2800,2000 };
	level1Points[11] = { 3300,2850 };
	level1Points[12] = { 275,2475 };
	level1Points[13] = { 1075,3450 };
	level1Points[14] = { 1500,4475 };
	level1Points[15] = { 3500,3875 };
	level1Points[16] = { 3750,2875 };
	level1Points[17] = { 5750,3375 };
	level1Points[18] = { 6000,4450 };
	level1Points[19] = { 7125,3850 };
	level1Points[20] = { 6475,2225 };
	level1Points[21] = { 8200,2700 };
	level1Points[22] = { 7625,5400 };
	level1CrossedPoint[0] = false;
	level1CrossedPoint[1] = false;
	level1CrossedPoint[2] = false;
	level1CrossedPoint[3] = false;
	level1CrossedPoint[4] = false;
	level1CrossedPoint[5] = false;
	level1CrossedPoint[6] = false;
	level1CrossedPoint[7] = false;
	level1CrossedPoint[8] = false;
	level1CrossedPoint[9] = false;
	level1CrossedPoint[10] = false;
	level1CrossedPoint[11] = false;
	level1CrossedPoint[12] = false;
	level1CrossedPoint[13] = false;
	level1CrossedPoint[14] = false;
	level1CrossedPoint[15] = false;
	level1CrossedPoint[16] = false;
	level1CrossedPoint[17] = false;
	level1CrossedPoint[18] = false;
	level1CrossedPoint[19] = false;
	level1CrossedPoint[20] = false;
	level1CrossedPoint[21] = false;
	level1CrossedPoint[22] = false;
}

void Enemy::loadImage()
// Loads the image for the player object
{
	if (!enemyTexture.loadFromFile("ASSETS/IMAGES/car.png"))
	{
		std::cout << "error with player image file";
	}

	enemySprite.setTexture(enemyTexture);
	enemySprite.setScale(0.075, 0.075);
	enemySprite.setOrigin(340, 170);
	enemySprite.getGlobalBounds();
}

void Enemy::movement()
{
	// x = Cos, Y = Sin
	heading = direction + 180;
	float dirRad = direction * 3.14159265359 / 180;
	float headingRadians = std::atan2(velocity.y, velocity.x); // used to get direction enemy is facing
	float headingDegree = 180.0f * headingRadians / static_cast<float>(3.141592);
	if (!isColliding)
	enemySprite.setRotation(headingDegree);
	turning = false;
	if (alive == true)
	{
		// if not colliding with anything, is in charge of turning the enemy to the point it is targetting
		if (!isColliding)
		{
			if (velocity.x > (currentPoint.x - position.x) / 380.0f)
			{
				velocity.x -= 0.0335;
				turning = true;
			}
			if (velocity.y < (currentPoint.y - position.y) / 380.0f)
			{
				velocity.y += 0.0335;
				turning = true;
			}
			if (velocity.x < (currentPoint.x - position.x) / 380.0f)
			{
				velocity.x += 0.0335;
				turning = true;
			}
			if (velocity.y > (currentPoint.y - position.y) / 380.0f)
			{
				velocity.y -= 0.0335;
				turning = true;
			}
		}

		//Every second it generates a random number that is used as a multiplier to drive in a random direction
		if (cooldown.getElapsedTime().asSeconds() > 1)
		{
			cooldown.restart();
		}
		if (cooldown.getElapsedTime().asSeconds() > 0.9 && cooldown.getElapsedTime().asSeconds() < 1)
		{
			randomNo = (rand() % 3) + 1;
		}
		switch (randomNo)
		{
		case 1:
			multiplier = -1;
			break;
		case 2:
			multiplier = 0;
			break;
		case 3:
			multiplier = 1;
			break;
		default:
			multiplier = 0;
			break;
		}
		float avgVel = (sqrt(velocity.y * velocity.y) + sqrt(velocity.x * velocity.x)) / 2;
		if (turning == true && avgVel > 0.8)
		{
			velocity.x += (0.0275 * multiplier);
			velocity.y += (0.0275 * multiplier);
		}
		position += velocity;
		enemySprite.setPosition(position);
	}
	if (!isColliding)
	enemySprite.setRotation(headingDegree);
}

void Enemy::updateEnemyPos()
{
	//This just changes the enemy's target to the next point once it crosses a point
	if (position.x > 1800 && level1CrossedPoint[0] == false)
	{
		if (level1CrossedPoint[0] == false)
		{
			currentPoint = level1Points[1];
			level1CrossedPoint[0] = true;
		}
	}
	if (position.x > 1975 && position.y > 1325 && level1CrossedPoint[0] == true)
	{
		if (!level1CrossedPoint[1])
		{
			currentPoint = level1Points[2];
			level1CrossedPoint[1] = true;
		}
	}
	if (position.x > 2875 && level1CrossedPoint[1] == true)
	{
		if (!level1CrossedPoint[2])
		{
			currentPoint = level1Points[3];
			level1CrossedPoint[2] = true;
		}
	}
	if (position.y < 660 && level1CrossedPoint[2] == true)
	{
		if (!level1CrossedPoint[3])
		{
			currentPoint = level1Points[4];
			level1CrossedPoint[3] = true;
		}
	}
	if (position.x > 4050 && level1CrossedPoint[3] == true)
	{
		if (!level1CrossedPoint[4])
		{
			currentPoint = level1Points[5];
			level1CrossedPoint[4] = true;
		}
	}
	if (position.x > 4600 && level1CrossedPoint[4] == true)
	{
		if (!level1CrossedPoint[5])
		{
			currentPoint = level1Points[6];
			level1CrossedPoint[5] = true;
		}
	}
	if (position.x > 4875 && level1CrossedPoint[5] == true)
	{
		if (!level1CrossedPoint[6])
		{
			currentPoint = level1Points[7];
			level1CrossedPoint[6] = true;
		}
	}
	if (position.y < 700 && level1CrossedPoint[6] == true)
	{
		if (!level1CrossedPoint[7])
		{
			currentPoint = level1Points[8];
			level1CrossedPoint[7] = true;
		}
	}
	if (position.x > 7250 && level1CrossedPoint[7] == true)
	{
		if (!level1CrossedPoint[8])
		{
			currentPoint = level1Points[9];
			level1CrossedPoint[8] = true;
		}
	}
	if (position.y > 1750 && level1CrossedPoint[8] == true)
	{
		if (!level1CrossedPoint[9])
		{
			currentPoint = level1Points[10];
			level1CrossedPoint[9] = true;
		}
	}
	if (position.x < 4075 && level1CrossedPoint[9] == true)
	{
		if (!level1CrossedPoint[10])
		{
			currentPoint = level1Points[11];
			level1CrossedPoint[10] = true;
		}
	}
	if (position.y > 2000 && level1CrossedPoint[10] == true)
	{
		if (!level1CrossedPoint[11])
		{
			currentPoint = level1Points[12];
			level1CrossedPoint[11] = true;
		}
	}
	if (position.x < 1700 && level1CrossedPoint[11] == true)
	{
		if (!level1CrossedPoint[12])
		{
			currentPoint = level1Points[13];
			level1CrossedPoint[12] = true;
		}
	}
	if (position.y > 2700 && level1CrossedPoint[12] == true)
	{
		if (!level1CrossedPoint[13])
		{
			currentPoint = level1Points[14];
			level1CrossedPoint[13] = true;
		}
	}
	if (position.y > 3500 && level1CrossedPoint[13] == true)
	{
		if (!level1CrossedPoint[14])
		{
			currentPoint = level1Points[15];
			level1CrossedPoint[14] = true;
		}
	}
	if (position.x > 2625 && level1CrossedPoint[14] == true)
	{
		if (!level1CrossedPoint[15])
		{
			currentPoint = level1Points[16];
			level1CrossedPoint[15] = true;
		}
	}
	if (position.y > 3625 && level1CrossedPoint[15] == true)
	{
		if (!level1CrossedPoint[16])
		{
			currentPoint = level1Points[17];
			level1CrossedPoint[16] = true;
		}
	}
	if (position.x > 4900 && level1CrossedPoint[16] == true)
	{
		if (!level1CrossedPoint[17])
		{
			currentPoint = level1Points[18];
			level1CrossedPoint[17] = true;
		}
	}
	if (position.y > 3325 && level1CrossedPoint[17] == true)
	{
		if (!level1CrossedPoint[18])
		{
			currentPoint = level1Points[19];
			level1CrossedPoint[18] = true;
		}
	}
	if (position.x > 6325 && level1CrossedPoint[18] == true)
	{
		if (!level1CrossedPoint[19])
		{
			currentPoint = level1Points[20];
			level1CrossedPoint[19] = true;
		}
	}
	if (position.y < 2400 && level1CrossedPoint[19] == true)
	{
		if (!level1CrossedPoint[20])
		{
			currentPoint = level1Points[21];
			level1CrossedPoint[20] = true;
		}
	}
	if (position.x > 7500 && level1CrossedPoint[20] == true)
	{
		if (!level1CrossedPoint[21])
		{
			currentPoint = level1Points[22];
			level1CrossedPoint[21] = true;
		}
	}
	if (position.y > 3750 && level1CrossedPoint[21] == true)
	{
		std::cout << "YOU LOST" << std::endl;
	}
}

sf::Sprite Enemy::returnSprite()
{
	return enemySprite;
}

void Enemy::setPosition()
{
	enemySprite.setPosition(200, 40);
}


void Enemy::setPosition(sf::Vector2f position)
{
	enemySprite.setPosition(position);
}

sf::Vector2f Enemy::getPosition()
{
	sf::Vector2f pos = enemySprite.getPosition();
	return pos;
}

float Enemy::getRotation()
{
	float dirRad = direction * 3.14159265359 / 180;
	return direction;
}

sf::FloatRect Enemy::returnBox()
{
	return enemySprite.getGlobalBounds();
}

sf::Vector2f Enemy::getVelocity()
{
	return velocity;
}

void Enemy::setVelocity(sf::Vector2f t_velocity)
{
	velocity = t_velocity;
	float headingRadians = std::atan2(velocity.y, velocity.x);
	float headingDegree = 180.0f * headingRadians / static_cast<float>(3.141592);
	if (!isColliding)
	enemySprite.setRotation(headingDegree + 180);
}

void Enemy::addVelocity(sf::Vector2f t_velocity)
{
	velocity += t_velocity * 2.0f;
	float headingRadians = std::atan2(velocity.y, velocity.x);
	float headingDegree = 180.0f * headingRadians / static_cast<float>(3.141592);
	if (!isColliding)
		enemySprite.setRotation(headingDegree + 180);
}

sf::Vector2f Enemy::returnOrigin()
{
	return enemySprite.getOrigin();
}

void Enemy::setAlive(bool t_alive)
{
	alive = t_alive;
}

bool Enemy::getAlive()
{
	return alive;
}