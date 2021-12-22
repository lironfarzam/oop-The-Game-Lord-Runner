
#include "Wall.h"
#include <iostream>


Wall::Wall(float x, float y) : NonMovableObject(x, y)
{
    m_isObstacle = true;
    m_sprite.setTexture(Resources::instance().getImage(WALL_IMG)); //all_textures[0]);
    m_sprite.setPosition(x, y);

}

void Wall::digHole()
{
    m_clock.restart();
    m_isHole = true;
    setDisposed(true);

}


bool  Wall::isDisposed()  {
    if (m_clock.getElapsedTime().asSeconds() >= 5) {
        m_isHole = false;
    }

    return m_isHole;
}


/*
 **************** COLLISION ******************
*/

void Wall::handleCollision(WorldObject& obj)
{
    if (&obj == this) return;
    //double dispatch
    obj.handleCollision(*this);
}

void Wall::handleCollision(Wall& )
{
}

void Wall::handleCollision(Enemy& obj)
{
    obj.handleCollision(*this);
}

void Wall::handleCollision(Player& obj)
{
    obj.handleCollision(*this);

}

void Wall::handleCollision(Ladder& )
{
}

void Wall::handleCollision(Coin& )
{
}

void Wall::handleCollision(Gift& )
{
}

void Wall::handleCollision(Pole& )
{
}

void Wall::handleCollision(GiftAddEnemy& )
{

}

void Wall::handleCollision(GiftAddLive& )
{
}

void Wall::handleCollision(GiftAddBonus& )
{
}

void Wall::handleCollision(GiftAddTime& )
{
}
    