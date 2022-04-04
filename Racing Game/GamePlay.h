/// <summary>
/// Michal Rapciak
/// </summary>

#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Level.h"
#include "Globals.h"
#include "MyVector2.h"

class GamePlay
{
public:

	GamePlay();
	~GamePlay();
	void initialise(sf::Font& t_font);
	void render(sf::RenderWindow& t_window);
	void update(sf::Time& t_deltatime, sf::RenderWindow& t_window);
	void processInput(sf::Event& t_event, sf::RenderWindow& t_window);

	void collisions();
	void terrain();
	void gamePause();
	void levelWin();
	void levelLoss();

	Player player;
	Enemy enemy;
	Level level1;

protected:

	bool m_pause = false;

	bool wonLevel = false;
	bool lostLevel = false;

	sf::Text endText;

	sf::Text m_pauseText;

	sf::Font m_font;
};

