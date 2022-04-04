/// <summary>
/// Michal Rapciak
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
#include "GamePlay.h"
#include "Player.h"
#include "Enemy.h"
#include "Level.h"
#include "Globals.h"
#include "LicenseScreen.h"
#include "SplashScreen.h"
#include "MainMenu.h"
#include "Help.h"

enum class
	GameState
{
	None,
	License,
	Splash,
	MainMenu,
	Help,
	GamePlay
};

class Game
{

public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();
	static GameState currentState;

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();

	void initialiseStates();

	sf::Font m_font;
	sf::RenderWindow m_window; // main SFML window

	LicenseScreen m_licenseScreen;
	SplashScreen m_splashScreen;
	MainMenu m_mainMenuScreen;
	Help m_helpScreen;
	GamePlay m_gamingScreen;

	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP

