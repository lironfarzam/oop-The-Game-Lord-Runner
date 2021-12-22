#pragma once


#include "MovableObject.h"

#include "Wall.h"
#include "Ladder.h"
#include "Pole.h"


class Player : public MovableObject {

public:
    Player(float x, float y);
    
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


    virtual void draw(sf::RenderWindow& window) override;
    virtual void move(sf::Time deltaTime) override;
    
    int getLives() const;
    int getScore() const;

    void decreaseLives();
    void setScore(int);
    void setLives(int);

    bool getIsDead();
    void setIsDead(bool);

private:

    int m_score = 0;
    int m_lives = NUM_LIVES;
    bool m_isdead;
    sf::Sprite m_sprite_default;
    
};


