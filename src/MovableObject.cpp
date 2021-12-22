

#include "MovableObject.h"
#include "Board.h"

//void MovableObject::handleCollision(WorldObject & obj) {
    //obj.handleCollision(*this); // double dispatch
//}

namespace
{
    sf::Vector2f dirToVector(MovableObject::Direction dir)
    {
        switch (dir)
        {
        case MovableObject::Direction::Right: return { 1, 0 };
        case MovableObject::Direction::Left:  return { -1, 0 };
        case MovableObject::Direction::Up:    return { 0, -1 };
        case MovableObject::Direction::Down:  return { 0, 1 };
        case MovableObject::Direction::Stay:  return { 0, 0 };
        case MovableObject::Direction::DigLeft:  return { 0, 0 };
        case MovableObject::Direction::DigRight:  return { 0, 0 };
        }
        return { 0, 0 }; // just to silence the warning about no return
        // would be better to throw an exception but we haven't learned about it yet
    }
}

MovableObject::MovableObject(float x, float y) :WorldObject(x, y), m_rectSourceSprite(0, 0, (int) ShapeWidth, (int) ShapeHeight)
{
    m_window_height = 500;
    m_window_width = 500;
    m_boardGame = NULL;

    m_state = State::onGround;
    m_dir = Direction::Stay;

    m_clock.restart();
}


void MovableObject::setBoard(Board* board) {
    if (board == NULL)
        return;
    m_boardGame = board;
    m_window_height = board->getWindowHeight();;
    m_window_width = board->getWindowWidth();
}

Board* MovableObject::getBoard() const
{
    return m_boardGame;
}

float MovableObject::getSpeed() const {
    return m_speed;
}

void MovableObject::setSpeed(float s) {
    m_speed = s;
}

void MovableObject::move(sf::Time deltaTime)
{
    sf::Vector2f v = dirToVector(m_dir) * getSpeed() * deltaTime.asSeconds();
    m_x = m_x + v.x;
    m_y = m_y + v.y;

    // check bounds of boards
    limitBounds();

    m_sprite.setPosition(m_x, m_y);

    m_boardGame->handleCollisions(*this);
}

void MovableObject::setDirection(sf::Keyboard::Key key)
{
    switch (key)
    {
    case sf::Keyboard::Right: m_dir = Direction::Right;    break;
    case sf::Keyboard::Left:  m_dir = Direction::Left;     break;
    case sf::Keyboard::Up:    m_dir = Direction::Up;       break;
    case sf::Keyboard::Down:  m_dir = Direction::Down;     break;
    case sf::Keyboard::Space: m_dir = Direction::Stay;     break;
    case sf::Keyboard::Z:     m_dir = Direction::DigLeft;  break;
    case sf::Keyboard::X:     m_dir = Direction::DigRight; break;

    }
}

void MovableObject::setDirection(MovableObject::Direction dir)
{
    m_dir = dir;
}

MovableObject::Direction MovableObject::getDirection()
{
    return m_dir;
}

void MovableObject::setWindowHeight(float h)
{
    m_window_height = h;
}

void MovableObject::setWindowWidth(float w)
{
    m_window_width = w;
}

bool MovableObject::limitBounds()
{
    if (m_x < 0) {
        m_x = 0;
        return false;
    }

    if (m_y < 0) {
        m_y = 0;
        return false;
    }

    if (m_x > (m_window_width - ShapeWidth)){
        m_x = (m_window_width - ShapeWidth);
    return false;
}
    if (m_y > (m_window_height - ShapeHeight)){
        m_y = (m_window_height - ShapeHeight);
    return false;
    }
    
    return true;
}

void MovableObject::mirorDir()
{
    if (m_dir == Direction::Down)
    {
        m_dir = Direction::Up;
    }
    if (m_dir == Direction::Up)
    {
        m_dir = Direction::Down;
    }
    if (m_dir == Direction::Left)
    {
        m_dir = Direction::Right;
    }
    if (m_dir == Direction::Right)
    {
        m_dir = Direction::Left;
    }
}

void MovableObject::setState(State s)
{
    m_state = s;
}

MovableObject::State MovableObject::getState()
{
    return m_state;
}


