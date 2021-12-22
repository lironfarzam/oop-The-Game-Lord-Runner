
#include "Controller.h"
#include <experimental/vector>


/*
* The controller holds the game window, the menu and the board
*/
Controller::Controller() :m_window(sf::RenderWindow(sf::VideoMode(1500, 1500), "Lode Runner by David & Liron")), 
                        m_board(&m_window), m_menu(&m_window) {

    m_window.setView(sf::View(sf::FloatRect(0, 0, m_board.getWindowWidth(), m_board.getWindowHeight() + STATUS_HEIGHT)));
    m_window.setSize(sf::Vector2u((unsigned int) m_board.getWindowWidth(), (unsigned int) m_board.getWindowHeight() + STATUS_HEIGHT));

    m_mode = GameMode::Menu;
}

/*
* main loop: draw map, handle events, and move objects.
*/
void Controller::run() {
 
    m_menu.resetWindowSize();

    while (m_window.isOpen())
    {
        if (m_modeChanged) {

            if (m_mode == GameMode::Play) {
                m_board.restartGame();
                m_board.resetWindowSize();
            }
            else
                m_menu.resetWindowSize();

            m_modeChanged = false;
        }

        if (m_mode == GameMode::Help) {
            displayHelp();
            handleEvents();
            m_board.setGameOver(false);
        }

        if (m_board.gameIsOver()) {
            m_mode = GameMode::GameOver;
            //m_menu.setMessage(GAME_OVER_MESSAGE + std::string("   Score: ") + std::to_string(m_board.getPlayer()->getScore()));
            m_modeChanged = true;
        }


        if (m_mode == GameMode::Menu || m_mode == GameMode::GameOver)
        {
            if (m_mode == GameMode::GameOver)
                m_menu.setMessage(GAME_OVER_MESSAGE + std::string("   Score: ") + std::to_string(m_board.getPlayer()->getScore()));

            displayMenu();
            handleEvents();
        }
        else if (m_mode == GameMode::Help) {
            displayHelp();
            handleEvents();
        }
        else
        {
            // playing
            displayBoard();
            handleEvents();
            m_board.updateGameObjects();
        }
    }
}

void Controller::displayHelp()
{
    m_window.clear();
    m_menu.drawHelp();
    m_window.display();
}

void Controller::displayMenu() 
{
    m_window.clear();
    m_menu.draw();
    m_window.display();
}

void Controller::displayBoard()
{
    m_window.clear();
    m_board.drawMap(m_window);
    m_window.display();
}

/*
* handles the keys pressed by the user
*/
void Controller::handleEvents()
{
    for (auto event = sf::Event(); m_window.pollEvent(event); )
    {
        if (m_mode == GameMode::Menu || m_mode == GameMode::Help || m_mode == GameMode::GameOver)
            menuHandleEvent(event);
        else
            gameHandleEvent(event);

    }
}

void Controller::menuHandleEvent(sf::Event& event) {
    switch (event.type)
    {
    case sf::Event::Closed:
    //case sf::Keyboard::Escape:
    //    m_window.close();
    //    break;

    case sf::Event::KeyPressed:

        if (m_mode == GameMode::Help) {
            m_mode = GameMode::Menu;
            m_modeChanged = true;
            break;
        }
        

        if (event.key.code == sf::Keyboard::Escape)
            m_window.close();

        else {
            if (event.key.code == sf::Keyboard::P)
            {
                m_mode = GameMode::Play;
                m_modeChanged = true;
            }
            else
            if (event.key.code == sf::Keyboard::Q)
            {
                m_window.close();
            }
            else
            if (event.key.code == sf::Keyboard::H)
            {
                m_mode = GameMode::Help;
                m_modeChanged = true;
            }
        }
        break;

    case sf::Event::MouseButtonReleased:
    {
        if (m_mode == GameMode::Help) {
            m_mode = GameMode::Menu;
            m_modeChanged = true;
            break;
        }
        Menu::Command m = m_menu.click(event.mouseButton.x, event.mouseButton.y);

        if (m == Menu::Command::Play) {
            m_mode = GameMode::Play;
            m_modeChanged = true;
        }
        else if (m == Menu::Command::Help) {
            m_mode = GameMode::Help;
            m_modeChanged = true;
        }

        if (m == Menu::Command::Quit) {
            m_window.close();
        }
    }
        break;
    default:
        break;
    }
}


void Controller::gameHandleEvent(sf::Event& event) {
    switch (event.type)
    {
    case sf::Event::Closed:
        m_window.close();
        break;

    case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::Escape)
        {
            m_window.close();
            break;
        }
        else
            // set players direction / action in case of digging (z/x)
            m_board.setPlayerDirection(event.key.code);

        break;

    case::sf::Event::KeyReleased:
        m_board.setPlayerDirection(sf::Keyboard::Space);
        break;
    }
}