#pragma once


#include "Gift.h"
#include "Player.h"

class GiftAddTime : public Gift {

public:
    GiftAddTime(float x, float y);

    virtual void handleCollision(Player& obj) override;

private:
};


