/// <summary>
/// Michal Rapciak
/// </summary>

#include "GamePlay.h"
#include "Game.h"
#include "Globals.h"
#include <iostream>

GamePlay::GamePlay()
{
}

GamePlay::~GamePlay()
{
}

/// <summary>
/// initilaise gameplay screen backgrounds, fonts,etc.
/// </summary>
/// <param name="t_font"></param>
void GamePlay::initialise(sf::Font& t_font)
{
	wonLevel = false;
	m_font = t_font;

	m_pauseText.setFont(t_font);
	m_pauseText.setString("GAME PAUSED");
	m_pauseText.setCharacterSize(56U);
	m_pauseText.setFillColor(sf::Color::Red);
	m_pauseText.setPosition((SCREEN_WIDTH / 2) - 220, (SCREEN_HEIGHT / 2) - 60);

	endText.setFont(t_font);
	endText.setString("");
	endText.setCharacterSize(64U);
	endText.setFillColor(sf::Color::Red);
	endText.setPosition((SCREEN_WIDTH / 2) - 340, (SCREEN_HEIGHT / 2) - 240);
}

void GamePlay::render(sf::RenderWindow& t_window)
{
	t_window.setView(level1.m_levelView);
	t_window.draw(level1.m_bgSprite);
	t_window.draw(enemy.returnSprite());
	t_window.draw(player.returnSprite());
	t_window.setView(t_window.getDefaultView());
	t_window.draw(player.scoreText);
	t_window.draw(player.speedText);
	if (m_pause == true)
	{
		t_window.draw(m_pauseText);
	}
	if (lostLevel == true || wonLevel == true)
	{
		t_window.draw(endText);
	}
	t_window.setView(level1.m_miniMap);
	t_window.draw(level1.m_bgSprite);
	t_window.draw(enemy.returnSprite());
	t_window.draw(player.returnSprite());
}

void GamePlay::update(sf::Time& t_deltatime, sf::RenderWindow& t_window)
{
	if (!m_pause)
	{
		if (enemy.getAlive() == true)
			collisions();
		if (player.getAlive() == true)
			player.movement();
		if (enemy.getAlive() == true)
		{
			enemy.updateEnemyPos();
			enemy.movement();
		}
		sf::Vector2f pos = player.getPosition();
		level1.m_levelView.setCenter(pos);
		level1.m_miniMap.setCenter(pos);
		level1.m_levelView.setRotation((player.getRotation()) - 90);
		terrain();
		player.scoreCounting();
	}
}

void GamePlay::collisions()
{
	player.returnBox();
	enemy.returnBox();
	if (player.returnBox().intersects(enemy.returnBox()))
	{
		player.isColliding = true;
		enemy.isColliding = true;
		sf::Vector2f lineOfCenters = player.returnOrigin() - enemy.returnOrigin();
		sf::Vector2f oneSwap = vectorProjection(player.getVelocity(), lineOfCenters);
		sf::Vector2f twoSwap = vectorProjection(enemy.getVelocity(), lineOfCenters);
		sf::Vector2f oneKeep = vectorRejection(player.getVelocity(), lineOfCenters);
		sf::Vector2f twoKeep = vectorRejection(enemy.getVelocity(), lineOfCenters);
		player.setVelocity((oneKeep + twoSwap) / 275.0f);
		enemy.addVelocity((twoKeep + oneSwap) / 275.0f);
	}
	else
	{
		player.isColliding = false;
		enemy.isColliding = false;
	}
	if (player.isColliding == true) player.setPosition(player.getPosition() + player.getVelocity() * 0.025f);
	if (enemy.isColliding == true) enemy.setPosition(enemy.getPosition() + enemy.getVelocity() * 0.01f);
}

void GamePlay::terrain()
{
	sf::Vector2f pos = player.getPosition();
	float avgVel = (sqrt(player.getVelocity().y * player.getVelocity().y) + sqrt(player.getVelocity().x * player.getVelocity().x)) / 2;
	int tile;
	tile = level1.returnTile(pos);
	if (tile == 1)
	{
		player.setVelocity((player.getVelocity() * 0.96f));
	}
	if (tile == 2)
	{
		player.setVelocity({ 0.0, 0.0 });
		if (avgVel > 1)
		{
			player.setAlive(false);
			lostLevel = true;
			levelLoss();
		}
	}
	sf::Vector2f enemyPos = enemy.getPosition();
	int enemyTile;
	enemyTile = level1.returnTile(enemyPos);
	if (enemyTile == 1)
	{
		enemy.setVelocity((enemy.getVelocity() * 0.94f));
	}
	if (enemyTile == 2)
	{
		wonLevel = true;
		enemy.setAlive(false);
		enemy.setVelocity({ 0.0, 0.0 });
		levelWin();
	}
}

void GamePlay::processInput(sf::Event& t_event, sf::RenderWindow& t_window)
{
	if (t_event.type == sf::Event::Resized)
	{
		// update the view to the new size of the window
		sf::FloatRect visibleArea(0.f, 0.f, t_event.size.width, t_event.size.height);
		level1.m_levelView.reset(visibleArea);
		level1.m_levelView.zoom(0.40);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		if (m_pause == true)
		{
			m_pause = false;
		}
		else if (m_pause == false)
		{
			m_pause = true;
		}
	}
	if (lostLevel == true || wonLevel == true)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			t_window.close();
			Game::currentState = GameState::MainMenu;
		}
	}
}

void GamePlay::gamePause()
{
	if (!m_pause)
	{
		m_pause = true;
	}
	else if (m_pause)
	{
		m_pause = false;
	}
}

void GamePlay::levelWin()
{
	endText.setString("YOU WON!\n YOUR SCORE:\n" + std::to_string(player.getScore()) + "\n\nPRESS ESCAPE TO RETURN\nTO DESKTOP");
}

void GamePlay::levelLoss()
{
	endText.setString("YOU LOST!\n YOUR SCORE:\n" + std::to_string(player.getScore()) + "\n\nPRESS ESCAPE TO RETURN\nTO DESKTOP");

}
