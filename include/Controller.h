#pragma once

#include <vector>
#include <memory>
#include <memory>

//#include "Menu.h"
//#include "Board.h"

#include "Levels.h"
#include "MovableObject.h"
#include "NonMovableObject.h"

#include "Wall.h"
#include "Ladder.h"
#include "Coin.h"
#include "Pole.h"
#include "Enemy.h"
#include "Player.h"
#include "Gift.h"
#include "Board.h"
#include "Menu.h"


#include <SFML/Graphics.hpp>

class Controller {

public:
    Controller();

    void displayBoard();
    void displayMenu();
    void displayHelp();

    void handleEvents();
    void run();

    void menuHandleEvent(sf::Event& event);
    void gameHandleEvent(sf::Event& event);

    enum class GameMode
    {
        Menu,
        Play,
        GameOver,
        Help
    };

private:
    Board m_board;
    sf::RenderWindow m_window;

    GameMode m_mode;
    bool m_modeChanged = false;
    Menu m_menu;
};


