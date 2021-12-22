
#include "Pole.h"

Pole::Pole(float x, float y) : NonMovableObject(x, y)
{
	m_isObstacle = false;
	m_sprite.setTexture(Resources::instance().getImage(POLE_IMG)); //all_textures[4]);
	m_sprite.setPosition(x, y);
}

void Pole::handleCollision(WorldObject& obj)
{
	if (&obj == this) return;
	//double dispatch
	obj.handleCollision(*this);
}

void Pole::handleCollision(Wall& )
{
}

void Pole::handleCollision(Enemy& obj)
{
	obj.handleCollision(*this);
}

void Pole::handleCollision(Player& obj)
{
	obj.handleCollision(*this);
}

void Pole::handleCollision(Ladder& )
{
}

void Pole::handleCollision(Coin& )
{
}

void Pole::handleCollision(Gift& )
{
}

void Pole::handleCollision(Pole& )
{
}

void Pole::handleCollision(GiftAddEnemy& )
{
}

void Pole::handleCollision(GiftAddLive& )
{
}

void Pole::handleCollision(GiftAddBonus& )
{
}

void Pole::handleCollision(GiftAddTime& )
{
}
