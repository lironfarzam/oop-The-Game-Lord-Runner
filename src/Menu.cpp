#include "Menu.h"
#include <iostream>

Menu::Menu(sf::RenderWindow* w): m_playButton(90, 500, BUTTON_WIDTH, BUTTON_HEIGHT), 
                                m_quitButton(800, 500, BUTTON_WIDTH, BUTTON_HEIGHT),
                                m_helpButton(445, 500, BUTTON_WIDTH, BUTTON_HEIGHT)
{
    m_window = w;
    m_message = "";
}

// display the opening image with play and quit buttons
void Menu::draw() {

    sf::Sprite sp = sf::Sprite(Resources::instance().getImage(COVER_IMG));
    sp.setPosition(sf::Vector2f(0, 0));
    m_window->draw(sp);

    if (m_message.length() > 0) {
        sf::Text text;
        text.setFont(Resources::instance().getFont());
        text.setStyle(sf::Text::Bold);
        text.setString(m_message);
        text.setFillColor(sf::Color::Red);
        text.setCharacterSize(48);
        //text.setPosition(sf::Vector2f(350, 400));

        sf::Rect bounds = text.getGlobalBounds();
        bounds.top = 350;
        bounds.left = (MENU_WIDTH - bounds.width) / 2;
        text.setPosition(bounds.left, bounds.top);

        m_window->draw(text);
    }

}

void Menu::drawHelp() {

    sf::Sprite sp = sf::Sprite(Resources::instance().getImage(COVER_HELP_IMG));
    sp.setPosition(sf::Vector2f(0, 0));
    m_window->draw(sp);
}

void Menu::resetWindowSize() {
    m_window->setSize(sf::Vector2u(MENU_WIDTH, MENU_HEIGHT));
    m_window->setView(sf::View(sf::FloatRect(0, 0, MENU_WIDTH  , MENU_HEIGHT)));
    m_window->clear();

}

void Menu::setMessage(std::string mess)
{
    m_message = mess;
}

// returns the clicked button, or None
Menu::Command Menu::click(int x, int y)
{
    if (m_playButton.contains(x, y)) 
        return Menu::Command::Play;

    if (m_quitButton.contains(x, y))
        return Menu::Command::Quit;

    if (m_helpButton.contains(x, y))
        return Menu::Command::Help;

    return Menu::Command::None;
}


