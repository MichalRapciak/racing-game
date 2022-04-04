#include "MainMenu.h"
#include "Game.h"
#include "GamePlay.h"
#include <iostream>

MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::initialise(sf::Font& t_font)
{
	m_yOffset = 200;
	m_xOffset = (SCREEN_WIDTH / 2) - m_buttonWidth - 150;
	m_buttonSpacing = 120;
	m_buttonWidth = 300;
	m_buttonHeight = 100;
	int textDropOffset = 15;
	sf::String m_Texts[] = { "Start Race", "Controls", "Exit Game" };

	m_font = t_font;

	if (!m_buttonTxt.loadFromFile("ASSETS/IMAGES/buttontxt.png"))
	{
		std::cout << "Can't load button texture";
	}
	for (int i = 0; i < m_buttonCount; i++)
	{
		m_buttonSprite[i].setTexture(m_buttonTxt);
		m_buttonSprite[i].setPosition(m_xOffset, m_buttonSpacing * (i + m_yOffset));
		sf::Vector2u txtSize = m_buttonTxt.getSize();
		m_buttonSprite[i].setScale(m_buttonWidth / txtSize.x, m_buttonHeight / txtSize.y);
		
		m_text[i].setFont(m_font);
		m_text[i].setString(m_Texts[i]);
		m_text[i].setFillColor(sf::Color::White);
		m_text[i].setCharacterSize(40);
		sf::FloatRect textSize = m_text[i].getGlobalBounds();
		float textOffset = (m_buttonWidth - textSize.width) / (2);
		m_text[i].setPosition(m_xOffset + textOffset, m_buttonSpacing * i + m_yOffset + textDropOffset);
	}
}

void MainMenu::update(sf::Time& t_deltaTime, sf::Window& t_window)
{
	sf::Vector2i mouseLocation;
	mouseLocation = sf::Mouse::getPosition(t_window);
	for (int i = 0; i < m_buttonCount; i++)
	{
		m_text[i].setFillColor(sf::Color::White);
	}
	if (mouseLocation.x > m_xOffset && mouseLocation.x < m_xOffset + m_buttonWidth)
	{
		if (mouseLocation.y > m_yOffset && mouseLocation.y < m_yOffset + m_buttonHeight)
		{
			m_buttonSprite[0].setColor(sf::Color{ 100,100,100,255 });
			m_text[0].setFillColor(sf::Color{ 75,75,75,255 });
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				Game::currentState = GameState::GamePlay;
			}
		}
		if (mouseLocation.y > m_yOffset + m_buttonSpacing && mouseLocation.y < m_yOffset + m_buttonHeight + m_buttonSpacing)
		{
			m_buttonSprite[1].setColor(sf::Color{ 100,100,100,255 });
			m_text[1].setFillColor(sf::Color{ 75,75,75,255 });
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				Game::currentState = GameState::Help;
			}
		}
		if (mouseLocation.y > m_yOffset + (m_buttonSpacing * 2) && mouseLocation.y < m_yOffset + m_buttonHeight + (m_buttonSpacing * 2))
		{
			m_buttonSprite[2].setColor(sf::Color{ 100,100,100,255 });
			m_text[2].setFillColor(sf::Color{ 75,75,75,255 });
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				t_window.close();
			}
		}
	}
}

void MainMenu::render(sf::RenderWindow& t_window)
{
	t_window.setView(t_window.getDefaultView());
	for (int i = 0; i < m_buttonCount; i++)
	{
		t_window.draw(m_buttonSprite[i]);
		t_window.draw(m_text[i]);
	}
}
