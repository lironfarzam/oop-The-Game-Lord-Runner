#pragma once


#include "NonMovableObject.h"
#include "Player.h"

class Coin : public NonMovableObject{

public:
	Coin(float x, float y);

    virtual void handleCollision(WorldObject& obj) override;
    virtual void handleCollision(Wall& obj) override;
    virtual void handleCollision(Enemy& obj) override;
    virtual void handleCollision(Player& obj) override;
    virtual void handleCollision(Ladder& obj) override;
    virtual void handleCollision(Coin& obj) override;
    virtual void handleCollision(Gift& obj) override;
    virtual void handleCollision(Pole& obj) override;
    virtual void handleCollision(GiftAddEnemy& obj) override;
    virtual void handleCollision(GiftAddLive& obj) override;
    virtual void handleCollision(GiftAddBonus& obj) override;
    virtual void handleCollision(GiftAddTime& obj) override;

    static int getCount();
    static void resetCounter();

private:
    static int m_count;
};


