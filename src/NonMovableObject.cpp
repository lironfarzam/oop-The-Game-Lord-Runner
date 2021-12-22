

#include "NonMovableObject.h"

/*
void NonMovableObject::handleCollision(WorldObject& gameObject)
{
    //double dispatch
    //gameObject.handleCollision(*this);
}
*/

NonMovableObject::NonMovableObject(float x, float y) :WorldObject(x, y)
{
}

bool NonMovableObject::isObstacle() const
{
    return m_isObstacle;
}

bool NonMovableObject::canClimb() const
{
    return m_canClimb;
}

//void NonMovableObject::draw(sf::RenderWindow& window) const
//{
//    draw(window);
//}
