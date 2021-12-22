#include "GiftAddTime.h"

GiftAddTime::GiftAddTime(float x, float y): Gift(x,y)
{
}

void GiftAddTime::handleCollision(Player& obj)
{
	m_isDisposed = true;
	//double dispatch
	obj.handleCollision(*this);
}
