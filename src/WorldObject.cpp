
#include "WorldObject.h"



WorldObject::WorldObject(float x, float y):m_x(x), m_y(y)
{
}

bool WorldObject::checkCollision(const sf::FloatRect& floatRect) const
{
    return m_sprite.getGlobalBounds().intersects(floatRect);
}

sf::FloatRect WorldObject::getGlobalBounds() const
{
    return m_sprite.getGlobalBounds();
}

bool WorldObject::isDisposed()
{
    return m_isDisposed;
}

void WorldObject::setDisposed(bool b)
{
    m_isDisposed = b;
}

void WorldObject::draw(sf::RenderWindow & window)
{
    window.draw(m_sprite);
}

float WorldObject::getX() const
{
    return m_x;
}

float WorldObject::getY() const
{
    return m_y;
}

void WorldObject::setX(float x)
{
    m_x = x;
}

void WorldObject::setY(float y)
{
    m_y = y;
}


//virtual ~WorldObject::GameObject() = default;
