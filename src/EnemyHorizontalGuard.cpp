#include "EnemyHorizontalGuard.h"
#include "Board.h"

EnemyHorizontalGuard::EnemyHorizontalGuard(float x, float y): Enemy(x, y)
{
}

void EnemyHorizontalGuard::move(sf::Time deltaTime)
{
	if (getBoard() == NULL)
		return;

	Player* player = m_boardGame->getPlayer();
	float player_x = player->getX();
	float player_y = player->getY();


	if ((m_y - player_y) >= -1.0f && (m_y - player_y) <= 1.0f)  // player on same row
	{
		if (m_x < player_x) //player to the right
		{
			if (!getBoard()->nothingBelow(this, Direction::Right)) //can go to right
			{
				m_dir = Direction::Right;
			}
			else // can't go to there
			{
				m_dir = Direction::Stay;
			}
		}
		else //player to the left
		{
			if (!getBoard()->nothingBelow(this, Direction::Left))//can go to left
			{
				m_dir = Direction::Left;
			}
			else//cant go to there
			{
				m_dir = Direction::Stay;
			}
		}
		if (m_dir != Direction::Stay)//if we need to move ->save litel time
		{
			MovableObject::move(deltaTime);// *2 to run very fast
			MovableObject::move(deltaTime);
		}
		else//we on stay mode and nead to chaing it for next time
		{
			if (m_x < player_x)
				m_dir = Direction::Right;
			else
				m_dir = Direction::Left;
		}
	}

	else//not in same row of player play allong whit func from bequeath
	{
		//EnemyHorizontal::move(deltaTime); 
		// we removed inheritance from EnnemyHorizontal
		// after Michal told us
		// so this code is identical in EnemyHorizontal
		// check if we have floor
		switch (m_dir) {
		case Direction::Left:
			if (getBoard()->nothingBelow(this, Direction::Left))
				m_dir = Direction::Right;
			break;
		case Direction::Right:
			if (getBoard()->nothingBelow(this, Direction::Right))
				m_dir = Direction::Left;
			break;
		case Direction::Down:
		case Direction::Up:
		default:
			return;
		}

		MovableObject::move(deltaTime);
	}
}

//void EnemyHorizontalGuard::handleCollision(Wall& obj)
//{
//	switch (m_dir) {
//	case Direction::Left:
//		m_x = obj.getX() + ShapeWidth;
//		m_dir = Direction::Right;
//		break;
//	case Direction::Right:
//		m_x = obj.getX() - ShapeWidth;
//		m_dir = Direction::Left;
//		break;
//	case Direction::Down:
//	case Direction::Up:
//	default:
//		return;
//	}
//}