
#include "Ladder.h"

Ladder::Ladder(float x, float y):NonMovableObject(x,y)
{
	m_isObstacle = true;
	m_canClimb = true;
	m_sprite = sf::Sprite(Resources::instance().getImage(LADDER_IMG));//all_textures[3]);
	m_sprite.setPosition(x, y);
}

void Ladder::handleCollision(WorldObject& obj)
{
	if (&obj == this) return;
	//double dispatch
	obj.handleCollision(*this);
}

void Ladder::handleCollision(Wall& )
{
}

void Ladder::handleCollision(Enemy& obj)
{
	obj.handleCollision(*this);
}

void Ladder::handleCollision(Player& obj)
{
	obj.handleCollision(*this);
}

void Ladder::handleCollision(Ladder& )
{
}

void Ladder::handleCollision(Coin& )
{
}

void Ladder::handleCollision(Gift& )
{
}

void Ladder::handleCollision(Pole& )
{
}

void Ladder::handleCollision(GiftAddEnemy& )
{
}

void Ladder::handleCollision(GiftAddLive& )
{
}

void Ladder::handleCollision(GiftAddBonus& )
{
}

void Ladder::handleCollision(GiftAddTime& )
{
}
