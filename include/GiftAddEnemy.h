#pragma once


#include "Gift.h"
#include "Player.h"

class GiftAddEnemy : public Gift {

public:
    GiftAddEnemy(float x, float y);

    virtual void handleCollision(Player& obj) override;

private:
};


