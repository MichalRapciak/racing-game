#include "Help.h"
#include "Game.h"

Help::Help()
{
}

Help::~Help()
{
}

void Help::initialise(sf::Font& t_font)
{
	m_font = t_font;

	m_helpText.setFont(m_font);
	m_helpText.setString("Use WASD to drive around \nPress Spacebar to brake your car\nPress Esc pause during the game\n or to to return to Main Menu now");
	m_helpText.setCharacterSize(60);
	m_helpText.setFillColor(sf::Color::White);

	sf::FloatRect textSize = m_helpText.getGlobalBounds();
	float xpos = SCREEN_WIDTH / 2 - textSize.width / 2;
	m_helpText.setPosition(xpos, SCREEN_HEIGHT * 0.20f);
	m_pressedExit = false;
}

void Help::processInput(sf::Event& t_event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		m_pressedExit = true;
	}
}

void Help::update(sf::Time& t_deltatime)
{
	if (m_pressedExit == true)
	{
		Game::currentState = GameState::MainMenu;
	}
	m_pressedExit = false;
}

void Help::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_helpText);
}
