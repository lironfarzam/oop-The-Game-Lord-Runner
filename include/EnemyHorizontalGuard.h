#pragma once

#include "EnemyHorizontal.h"

class EnemyHorizontalGuard : public Enemy {

public:
	EnemyHorizontalGuard(float x, float y);

	virtual void move(sf::Time deltaTime) override;
	//void handleCollision(Wall& obj);

};
