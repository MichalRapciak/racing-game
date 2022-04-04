#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"
class LicenseScreen
{
public:
	LicenseScreen();
	~LicenseScreen();
	void initialise(sf::Font& t_font);
	void render(sf::RenderWindow & t_window);
	void update(sf::Time& t_deltaTime);

protected:
	sf::Font m_font;
	sf::Text m_text;
	sf::Time m_licenseTime;
};

