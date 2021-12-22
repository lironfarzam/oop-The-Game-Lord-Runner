#include "GiftAddLive.h"

GiftAddLive::GiftAddLive(float x, float y): Gift(x, y)
{
}

void GiftAddLive::handleCollision(WorldObject& obj)
{	
	if (&obj == this) return;
	//double dispatch
	obj.handleCollision(*this);
}

//void GiftAddLive::handleCollision(Wall& obj)
//{
//}
//
//void GiftAddLive::handleCollision(Enemy& obj)
//{
//}

void GiftAddLive::handleCollision(Player& obj)
{
	m_isDisposed = true;
	//double dispatch
	obj.handleCollision(*this);
}

//void GiftAddLive::handleCollision(Ladder& obj)
//{
//}
//
//void GiftAddLive::handleCollision(Coin& obj)
//{
//}
//
//void GiftAddLive::handleCollision(Gift& obj)
//{
//}
//
//void GiftAddLive::handleCollision(Pole& obj)
//{
//}
//
//
//void GiftAddLive::handleCollision(GiftAddEnemy& obj)
//{
//}
//
//void GiftAddLive::handleCollision(GiftAddBonus& obj)
//{
//}
//
//void GiftAddLive::handleCollision(GiftAddLive& obj)
//{
//}
