#pragma once
#include "constants.h"

#include "MovableObject.h"
#include "NonMovableObject.h"


#include "Wall.h"
#include "Pole.h"
#include "Ladder.h"
#include "Coin.h"
#include "Enemy.h"
#include "EnemyHorizontal.h"
#include "EnemyRandom.h"
#include "EnemyFollow.h"
#include "EnemyHorizontalGuard.h"
#include "Player.h"
#include "Gift.h"
#include "GiftAddEnemy.h"
#include "Resources.h"
#include "Controller.h"
#include "GiftAddBonus.h"
#include "GiftAddLive.h"
#include "GiftAddTime.h"

// a singleton factory to create game objects

class ObjectFactory {
public:
	~ObjectFactory();
	static ObjectFactory& instance();

	std::unique_ptr<MovableObject> createMovableObject(char type, float x, float y);
	std::unique_ptr<NonMovableObject> createUnmovableObject(char type, float x, float y);

private:
	ObjectFactory();
	ObjectFactory(const ObjectFactory&) = default;
	ObjectFactory& operator=(const ObjectFactory&) = default;

};
