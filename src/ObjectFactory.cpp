#include "ObjectFactory.h"
#include <iostream>

/*
*  A SINGLETON factory to create game objects
*/

ObjectFactory::~ObjectFactory()
{
}

ObjectFactory& ObjectFactory::instance()
{
    static ObjectFactory inst;
    return inst;
}


ObjectFactory::ObjectFactory()
{

}

std::unique_ptr<MovableObject> ObjectFactory::createMovableObject(char type, float x, float y)
{
    switch (type)
    {
    case PLAYER:
        return std::make_unique<Player>(x, y);
        break;
    case ENEMY:
        int enemyType = Resources::randomNumber(4);
        switch (enemyType) {
        case 0:
            return std::make_unique <EnemyFollow>(x, y);

            break;
        case 1:
            return std::make_unique < EnemyHorizontal >(x, y);

            break;
        case 2:
            return std::make_unique <EnemyRandom>(x, y);

            break;
        case 3:
            return std::make_unique <EnemyHorizontalGuard>(x, y);

            break;
        }
        //return std::make_unique <EnemyFollow> (x, y); 
        break;
    }
    return nullptr;
}

// our FACTORY for NonMovable
std::unique_ptr<NonMovableObject> ObjectFactory::createUnmovableObject(char type, float x, float y)
{
    int giftType = 0;
    switch (type)
    {
    case WALL:
        return std::make_unique<Wall>(x, y);
        break;

    case LADDER:
        return std::make_unique<Ladder>(x, y);
        break;

    case COIN:
        return std::make_unique<Coin>(x, y);
        break;

    case POLE:
        return std::make_unique<Pole>(x, y);
        break;

    case GIFT:
        giftType = Resources::randomNumber(3);
        // same as GIFT4
    case GIFT4: // with timer we can choose also GiftAddTime
        if (type != GIFT)
            giftType = Resources::randomNumber(4);

        switch (giftType) {
        case 0:
            return std::make_unique <GiftAddBonus>(x, y);
            break;
        case 1:
            return std::make_unique <GiftAddEnemy>(x, y);
            break;
        case 2:
            return std::make_unique <GiftAddLive>(x, y);
            break;
        case 3:
            return std::make_unique <GiftAddTime>(x, y);
            break;
        }

    default:
        break;
    }

    return nullptr;
}

