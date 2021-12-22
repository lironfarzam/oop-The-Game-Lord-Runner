#pragma once


#include "WorldObject.h"

class NonMovableObject : public WorldObject {
public:
	NonMovableObject(float x, float y);

	bool isObstacle() const;
	bool canClimb() const;

protected:
	bool m_isObstacle = false;
	bool m_canClimb = false;
};


