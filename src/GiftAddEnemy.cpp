#include "GiftAddEnemy.h"

GiftAddEnemy::GiftAddEnemy(float x, float y) : Gift(x,y)
{
}


void GiftAddEnemy::handleCollision(Player& obj)
{
	m_isDisposed = true;
	obj.handleCollision(*this);
}
