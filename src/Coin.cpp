
#include "Coin.h"


int Coin::m_count = 0;

void Coin::resetCounter() { 
	m_count = 0; 
}

int Coin::getCount()
{
	return m_count;
}

Coin::Coin(float x, float y) :NonMovableObject(x, y)
{
	m_sprite.setTexture(Resources::instance().getImage(COIN_IMG));//all_textures[5]);
	m_sprite.setPosition(x, y);
	m_count++;
}

void Coin::handleCollision(WorldObject& obj)
{
	if (&obj == this) return;
	//double dispatch
	//std::cout << " Coin::handleCollision(WorldObject& obj)" << std::endl;
	obj.handleCollision(*this);
}

void Coin::handleCollision(Wall& )
{
}

void Coin::handleCollision(Enemy& )
{
}

void Coin::handleCollision(Player& obj)
{
	obj.handleCollision(*this);
	m_isDisposed = true;
	Coin::m_count--;
}

void Coin::handleCollision(Ladder& )
{
}

void Coin::handleCollision(Coin& )
{
}

void Coin::handleCollision(Gift& )
{
}

void Coin::handleCollision(Pole& )
{
}



void Coin::handleCollision(GiftAddEnemy& )
{
}

void Coin::handleCollision(GiftAddLive& )
{
}

void Coin::handleCollision(GiftAddBonus& )
{
}

void Coin::handleCollision(GiftAddTime& )
{
}
