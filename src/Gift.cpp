
#include "Gift.h"

Gift::Gift(float x, float y): NonMovableObject(x,y)
{
	m_sprite.setTexture(Resources::instance().getImage(GIFT_IMG)); 
	m_sprite.setPosition(x, y);
}

void Gift::handleCollision(WorldObject& obj)
{
	if (&obj == this) return;
	//double dispatch
	obj.handleCollision(*this);
}

void Gift::handleCollision(Wall& )
{
}

void Gift::handleCollision(Enemy& )
{
}

void Gift::handleCollision(Player& obj)
{
	obj.handleCollision(*this);
}

void Gift::handleCollision(Ladder& )
{
}

void Gift::handleCollision(Coin& )
{
}

void Gift::handleCollision(Gift& )
{
}

void Gift::handleCollision(Pole& )
{
}

void Gift::handleCollision(GiftAddEnemy& )
{
}

void Gift::handleCollision(GiftAddLive& )
{
}

void Gift::handleCollision(GiftAddBonus& )
{
}

void Gift::handleCollision(GiftAddTime& )
{
}
