#pragma once


#include <SFML/Graphics.hpp>
#include "constants.h"
#include <iostream>
#include "Resources.h"

//#include <Controller.h>

class Wall;
class Enemy;
class Player;
class Ladder;
class Coin;
class Gift;
class GiftAddEnemy;
class GiftAddBonus;
class GiftAddLive;
class Pole;
class GiftAddTime;

class WorldObject {

public:
    WorldObject(float, float);
    

    virtual void handleCollision(WorldObject& obj) = 0;
    virtual void handleCollision(Wall& obj) = 0;
    virtual void handleCollision(Enemy & obj) = 0;
    virtual void handleCollision(Player & obj) = 0;
    virtual void handleCollision(Ladder & obj) = 0;
    virtual void handleCollision(Coin & obj) = 0;
    virtual void handleCollision(Gift & obj) = 0;
    virtual void handleCollision(Pole & obj) = 0;
    virtual void handleCollision(GiftAddEnemy & obj) = 0;
    virtual void handleCollision(GiftAddLive& obj) = 0;
    virtual void handleCollision(GiftAddBonus& obj) = 0;
    virtual void handleCollision(GiftAddTime& obj) = 0;

    virtual bool checkCollision(const sf::FloatRect&) const;
    virtual sf::FloatRect getGlobalBounds() const;
   
    // virtual dtor
    virtual ~WorldObject() = default;
    
    virtual bool isDisposed();
    virtual void setDisposed(bool b);

    virtual void draw(sf::RenderWindow& window);

    float getX() const;
    float getY() const;
    void setX(float);
    void setY(float);
    

protected:
    bool m_isDisposed = false;
    float m_x = 0;
    float m_y = 0;
    sf::Sprite m_sprite;

};

