#pragma once


#include "Gift.h"
#include "Player.h"

class GiftAddLive : public Gift {

public:
    GiftAddLive(float x, float y);

    //virtual void handleCollision(Player& obj) override;

    virtual void handleCollision(WorldObject& obj) override;
    //virtual void handleCollision(Wall& obj) override;
    //virtual void handleCollision(Enemy& obj) override;
    virtual void handleCollision(Player& obj) override;
    //virtual void handleCollision(Ladder& obj) override;
    //virtual void handleCollision(Coin& obj) override;
    //virtual void handleCollision(Gift& obj) override;
    //virtual void handleCollision(Pole& obj) override;
    //virtual void handleCollision(GiftAddEnemy& obj) override;
    //virtual void handleCollision(GiftAddBonus& obj) override;
    //virtual void handleCollision(GiftAddLive& obj) override;

private:
};


