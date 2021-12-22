#include "Board.h"
#include "MovableObject.h"
#include "Player.h"
#include "EnemyRandom.h"
#include "EnemyHorizontal.h"
#include "EnemyFollow.h"
#include "EnemyHorizontalGuard.h"
#include "GiftAddEnemy.h"
#include "GiftAddBonus.h"
#include "GiftAddLive.h"
#include "GiftAddTime.h"
#include "ObjectFactory.h"
#include <string>

const char* LEVELS_FILE = "Board.txt";

/*
* param: the window game passed by the controller
*/
Board::Board(sf::RenderWindow* w)
{
    m_window = w;
    // load all maps
    m_levels.loadMapsFromFile(LEVELS_FILE);

    setCurrentLevel(0);
    loadMapObjects();
}

/*
* loop over all objects (movable and then non movable) and draw them.
* at the end print game stats at the bottom of window
*/
void Board::drawMap(sf::RenderWindow &m) // TODO REMOVE PARAM (in members)
{

    for (auto& unmovable : m_unmovables)
    {
        if (unmovable->isDisposed() == false)
            unmovable->draw(m);
    }

    for (auto& movable : m_movables)
    {
        if (movable->isDisposed() == false)
            movable->draw(m);
    }

    printStats();
}

void Board::setPlayerDirection(sf::Keyboard::Key key)
{
    m_player->setDirection(key);
}


float Board::getWindowHeight() const
{
    return m_levels.getWindowHeight();
}

float Board::getWindowWidth() const
{
    return m_levels.getWindowWidth();
}


void Board::loadMapObjects()
{
    m_movables.clear();
    m_unmovables.clear();
    Coin::resetCounter();
    m_gameIsOver = false;

    GameMap curmap = m_levels.getCurrentMap();

    for (int row = 0; row < curmap.getHeight(); row++) {
        for (int col = 0; col < curmap.getWidth(); col++) {
            createObject(curmap.getChar(row,col), (float)col * ShapeWidth, (float)row * ShapeHeight);
        }
    }
    
    resetGameClock();
}

/*
* check if currrent game clock is over
*/
bool Board::timeIsOver() const {
    if (m_levels.getCurrentMap().getTimerValue() > 0) {
        if (m_gameClock.getElapsedTime().asSeconds() > m_levels.getCurrentMap().getTimerValue())
            return true;
    }
    return false;
}

void Board::resetGameClock()
{
    m_gameClock.restart();
}

int Board::getGameClock()
{
    return (int) m_gameClock.getElapsedTime().asSeconds();
}

Player* Board::getPlayer() const
{
    return m_player;
}

int Board::getCurrentLevel() const
{
    return m_levels.getCurrentLevel();
}

void Board::setCurrentLevel(int lev)
{
    m_levels.setCurrentLevel(lev);
}

/*
* load the next map available
* returns false if no more maps, else true
*/
bool Board::loadNextMap() {
    m_player->setScore(m_player->getScore() + (getCurrentLevel() + 1) * BONUS_LEVEL);
    if (m_levels.loadNextMap()) {
        loadCurrentMap();
        resetWindowSize();
        return true;
    }
    else
        return false; // no more maps
}


/*
  maps are store in m_levels(vector of chars)
  we create the objects(movable / nonmovable) when loading a new map.
 load the current level map:
 load map: reset Coin counter and movable/unmovable
 reset window size
*/
void Board::loadCurrentMap() {

    int c = 0;
    int l = 0;
    if (m_player != NULL) {
        l = m_player->getLives();
        c = m_player->getScore();
    }

    loadMapObjects();

    if (m_player != NULL) {
        m_player->setLives(l);
        m_player->setScore(c);
        m_player->setIsDead(false);
    }
}



// the building of 2 arrays
void Board::createObject(char type, float x, float y)
{
    if (type == EMPTY)
        return;


    std::unique_ptr<MovableObject> movable = ObjectFactory::instance().createMovableObject(type, x, y);
    if (movable)
    {
        movable->setBoard(this);
        if (type == PLAYER) {
                m_player = (Player*)movable.get();
        }
        m_movables.push_back(std::move(movable));
        return;
    }

    if (type == GIFT) {
        if (m_levels.getCurrentMap().getTimerValue() > 0)
            type = GIFT4;
    }
    std::unique_ptr<NonMovableObject> unmovable = ObjectFactory::instance().createUnmovableObject(type, x, y);

    if (unmovable)
    {
        m_unmovables.push_back(std::move(unmovable));
        return;
    }

    std::cerr << "Unrecognized char in the file: '" << type << "'" << std::endl;
    exit(EXIT_FAILURE);
}

void Board::restartGame()
{
    setCurrentLevel(0);
    loadMapObjects();
}

/* 
* The Main board logic
* 1. check the game state (game over, go to next level..)
* 2. loop over movables (player and enemy) and apply gravity then move
* the move function triggers the double dispatch and collision detection
*/
void Board::updateGameObjects()
{
    sf::FloatRect rect;
    sf::FloatRect rect_below;

    checkBoardState();

    if (m_gameIsOver)
        return;

    const auto deltaTime = m_animClock.restart();

    // move player and enemies
    std::vector<MovableObject>::size_type size = m_movables.size();

    for (std::vector<MovableObject>::size_type i = 0; i < size; ++i) {

        if (m_movables[i]->isDisposed())
            continue;

        applyGravity(m_movables[i].get(),deltaTime);
        m_movables[i]->move(deltaTime);
    }
}


/* 
    correct the wanted direction in case object is about to fall or fly in the air
*/
void Board::applyGravity(MovableObject * mov, sf::Time deltaTime) const {
    bool fall = false;
    // check if falling
    if (!isCollision(*mov) && !isObstacleBelow(mov))
    {
        mov->m_isFalling = true;
        mov->setX(floor((mov->getX() + ShapeWidth / 2) / ShapeWidth) * ShapeWidth);
        mov->setDirection(MovableObject::Direction::Down); // FALLING!
        mov->move(deltaTime);
        fall = true;
    }
    // check gravity up (don't fly..)
    if (!fall) {
        // going up and no collision detection so we handle it here
        if (mov->getDirection() == MovableObject::Direction::Up) {
            if (mov->getState() != MovableObject::State::onLadder) {
                mov->setDirection(MovableObject::Direction::Stay);
            }
        }
    }
}

/*
* check the game states and update the player/game/map
*/
void Board::checkBoardState() {
    if (timeIsOver()) {
        m_player->decreaseLives();
        m_player->setIsDead(true);
    }

    if (m_player->getLives() == 0) { // Game OVER
        m_gameIsOver = true;
    }

    if (m_player->getIsDead() == true) {
        // reload map
        loadCurrentMap();
        resetWindowSize();
    }

    else
        if (Coin::getCount() == 0) {
            if (!loadNextMap())
                m_gameIsOver = true;
        }
}

bool Board::isCollision(MovableObject& movable) const
{
    sf::FloatRect rect;
    rect = movable.getGlobalBounds(); // copy current 

    for (auto& unmovable : m_unmovables)
    {
        if (!unmovable->isDisposed() && movable.checkCollision(unmovable->getGlobalBounds()))
        {
            return true;
        }
    }
    return false;
}

bool Board::isObstacleBelow(MovableObject * movable) const
{
    bool obstacle_below = false;

    sf::FloatRect rect = movable->getGlobalBounds(); 
    rect.top = rect.top + ShapeHeight;
    // build a 0.1 x 0.2 rectangle under the movable
    rect.left = (rect.left + (ShapeWidth / 2)) - 0.1f;
    rect.width = 0.2f;
    rect.height = 0.1f;

    for (auto& unmovable : m_unmovables)
    {
        if (!unmovable->isDisposed() && unmovable->isObstacle()  && unmovable->checkCollision(rect))
        {
            obstacle_below = true;
            break;
        }
    }
    return obstacle_below;
}

bool Board::nothingBelow(MovableObject* movable) const
{
    sf::FloatRect rect_below = movable->getGlobalBounds();
    rect_below.top = rect_below.top + ShapeHeight; // 1;
    bool isfalling = true;

    rect_below.left = rect_below.left + 10.f;
    rect_below.width = rect_below.width - 20.f;
    rect_below.height = 1.f;


    for (auto& unmovable : m_unmovables)
    {
        if (!unmovable->isDisposed() && unmovable->checkCollision(rect_below)) {
            isfalling = false;
        }
    }
    return isfalling;
}

/*
* nothing below movable to the right
* or nothing below movable to the left
*/
bool Board::nothingBelow(MovableObject* movable, MovableObject::Direction dir) const {
    bool isfalling = true;
    sf::FloatRect rect_below = movable->getGlobalBounds();
    rect_below.top = rect_below.top + 1; 

    if (dir == MovableObject::Direction::Left)
        rect_below.left = (floor(rect_below.left / ShapeWidth)) * ShapeWidth;
    else
        rect_below.left = (ceil(rect_below.left / ShapeWidth)/* +1*/ ) * ShapeWidth;

    for (auto& unmovable : m_unmovables)
    {
        if (!unmovable->isDisposed() && unmovable->checkCollision(rect_below)) {
            isfalling = false;
        }
    }
    return isfalling;
}

// used by the player to try to dig left or right
void Board::digHole(MovableObject* movable, MovableObject::Direction dir) {
    Wall* w;

    sf::FloatRect rect_below = movable->getGlobalBounds();
    rect_below.top = rect_below.top + ShapeHeight;
    rect_below.height = 1;
    if (dir == MovableObject::Direction::Left)
        rect_below.left = (floor(rect_below.left / ShapeWidth) -1) * ShapeWidth;
    else
        rect_below.left = (ceil(rect_below.left / ShapeWidth) + 1) * ShapeWidth;

    for (auto& unmovable : m_unmovables)
    {
        if (!unmovable->isDisposed() && unmovable->checkCollision(rect_below)) {
            w = dynamic_cast<Wall*>(unmovable.get());
            if (w != NULL){
                w->digHole();
                return;
            }
        }
    }
}

bool  Board::canGoDown(MovableObject* movable) const {

    return canGoDirection(movable, MovableObject::Direction::Down);
}

bool Board::canGoUp(MovableObject* movable) const {

    return canGoDirection(movable, MovableObject::Direction::Up);
}

// private  function
bool Board::canGoDirection(MovableObject* movable, MovableObject::Direction dir) const {
    sf::FloatRect rect = movable->getGlobalBounds();
    if (dir == MovableObject::Direction::Up) {
        rect.top = rect.top - 1;
    }
    else
        rect.top = rect.top + ShapeHeight;

    rect.left = (rect.left + (ShapeWidth / 2)) - 1.0f; 
    rect.width = 2.f; 

    for (auto& unmovable : m_unmovables)
    {
        if (unmovable->checkCollision(rect)) {
            if (unmovable->canClimb()) {
                return true;
            }
        }
    }
    return false;
}

/*
*  used in double dispatch: gameObject is a movable (PLAYER OR ENEMY)
* 1. check if player or ennemy is collision with unmovable
* 2. check if player/enemy collision with other player/enemy
*/
void Board::handleCollisions(WorldObject& gameObject)
{
    // check if player or ennemy is collision with unmovable

    std::vector<NonMovableObject>::size_type size = m_unmovables.size();
    for (std::vector<NonMovableObject>::size_type i = 0; i < size; ++i)
    {
        if (!m_unmovables[i]->isDisposed() && gameObject.checkCollision(m_unmovables[i]->getGlobalBounds()))
        {
            gameObject.handleCollision(*m_unmovables[i]);
        }
    }

 
    // check if player/enemy collision with other player/enemy
    // m_movables can be modified in the loop when creating new enemy (GiftEnemy)
    size = m_movables.size();
    for (std::vector<MovableObject>::size_type i = 0; i < size; ++i) 
    {
        if (!m_movables[i]->isDisposed() && gameObject.checkCollision(m_movables[i]->getGlobalBounds()))
            gameObject.handleCollision(*m_movables[i]);
    }
}

/*
* duplicate an enemy - we use the same position of the first found enemy
*/
void Board::addEnemy()
{
    std::vector<MovableObject>::size_type size = m_movables.size();
    int target = Resources::randomNumber((int)size);
    // avoid the player
    if (m_movables[target].get() == m_player) {
        target = target + 1;
        if (target == size)
            target = 0;
    }

    for (std::vector<MovableObject>::size_type i = 0; i < size; ++i) {

        if (target == i && m_movables[i].get() != m_player) {
            //we got an enemy
            createObject(ENEMY,m_movables[i]->getX(), m_movables[i]->getY());
            break;
        }

    }

}
bool Board::gameIsOver() const
{
    return m_gameIsOver;
}
void Board::setGameOver(bool b)
{
    m_gameIsOver = b;
}
/*
* prints the stats below the game board using sf::
*/
void Board::printStats()  {

    if (m_player == NULL)
        return;
    std::string score = 
          "Score: "    + std::to_string(m_player->getScore()) 
        + "   |   Lives: "    + std::to_string(m_player->getLives())
        + "   |   Level: "    + std::to_string(getCurrentLevel()+1);

    if (m_levels.getCurrentMap().getTimerValue() > 0) {
        score += "   |   Clock: " 
            + std::to_string(int (m_levels.getCurrentMap().getTimerValue() - m_gameClock.getElapsedTime().asSeconds()));
    }

    sf::Text text;
    text.setFont (Resources::instance().getFont()); 
    text.setStyle(sf::Text::Bold);
    text.setString(score);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(24);

    sf::Rect bounds = text.getGlobalBounds();
    bounds.top = getWindowHeight() + STATUS_HEIGHT / 4;
    bounds.left = (getWindowWidth() - bounds.width) / 2;
    text.setPosition(bounds.left, bounds.top);

    m_window->draw(text);
}

void Board::resetWindowSize() {
    m_window->setView(sf::View(sf::FloatRect(0, 0, getWindowWidth(), getWindowHeight() + STATUS_HEIGHT)));
    m_window->setSize(sf::Vector2u((unsigned int) getWindowWidth(), (unsigned int) getWindowHeight() + STATUS_HEIGHT));
}