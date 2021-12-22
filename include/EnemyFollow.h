#pragma once

#include "Enemy.h"


class EnemyFollow : public Enemy {


public:
	EnemyFollow(float x, float y);
	virtual void move(sf::Time deltaTime) override;

	void handleCollision(Wall& obj);
	void handleCollision(Ladder& obj);
	void handleCollision(Pole& obj);

private:
	int fail_direction_left = 0;
	int fail_direction_right = 0;

};
