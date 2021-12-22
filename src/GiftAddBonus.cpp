#include "GiftAddBonus.h"

GiftAddBonus::GiftAddBonus(float x, float y): Gift(x, y)
{
}

void GiftAddBonus::handleCollision(WorldObject& obj)
{
	if (&obj == this) return;
	//double dispatch
	obj.handleCollision(*this);

}

//void GiftAddBonus::handleCollision(Wall& obj)
//{
//}
//
//void GiftAddBonus::handleCollision(Enemy& obj)
//{
//}

void GiftAddBonus::handleCollision(Player& obj)
{
	m_isDisposed = true;
	//double dispatch
	obj.handleCollision(*this);

}

//void GiftAddBonus::handleCollision(Ladder& obj)
//{
//}
//
//void GiftAddBonus::handleCollision(Coin& obj)
//{
//}
//
//void GiftAddBonus::handleCollision(Gift& obj)
//{
//}
//
//void GiftAddBonus::handleCollision(Pole& obj)
//{
//}
//
//void GiftAddBonus::handleCollision(GiftAddEnemy& obj)
//{
//}
//
//void GiftAddBonus::handleCollision(GiftAddLive& obj)
//{
//}
//
//void GiftAddBonus::handleCollision(GiftAddBonus& obj)
//{
//}
