#include "EnemyFollow.h"
#include "Board.h"

EnemyFollow::EnemyFollow(float x, float y) : Enemy(x, y)
{
}

void EnemyFollow::move(sf::Time deltaTime)
{
	if (getBoard() == NULL)
		return;

	Player* player = m_boardGame->getPlayer();

	float player_x = player->getX();
	float player_y = player->getY();

	if (!m_boardGame->isCollision(*this) && !m_boardGame->isObstacleBelow(this)) {
		m_dir = Direction::Down;
	} 
	else

	if (m_y == player_y) { // player on same row

		if (m_x < player_x)
			m_dir = Direction::Right;
		else
			m_dir = Direction::Left;
	}
	else {	// Player is not on same row
		
		if (m_y <= player_y) {				// player down

			if (m_boardGame->canGoDown(this)) { 
					m_dir = Direction::Down;
					fail_direction_left = 0;
					fail_direction_right = 0;
			}
			else {

				if (m_x <= player_x) {
					if (fail_direction_right > 0) {
						m_dir = Direction::Left;
						fail_direction_right = 0;
					}
					else {
						m_dir = Direction::Right;
					}
				} 
				else {
					if (fail_direction_left > 0) {
						m_dir = Direction::Right;
						fail_direction_left = 0;
					}
					else {
						m_dir = Direction::Left;
					}
				}
			}
		}
		else						// player up
		{
			if (m_boardGame->canGoUp(this)) {
					m_dir = Direction::Up;
					fail_direction_left = 0;
					fail_direction_right = 0;
			}
			else {
				
				if (m_x < player_x)
					m_dir = Direction::Right;
				else
					m_dir = Direction::Left;
			}
		}
	}

	MovableObject::move(deltaTime);
}

void EnemyFollow::handleCollision(Wall& obj)
{
	if (m_dir == Direction::Up)
	{
		m_y = obj.getY() + ShapeHeight;
		m_dir = Direction::Left;
	}
	else if (m_dir == Direction::Down)
	{
		m_y = obj.getY() - ShapeHeight;
		setState(MovableObject::State::onGround);
	}
	else if (m_dir == Direction::Left)
	{
		m_x = obj.getX() + ShapeWidth;
		m_dir = Direction::Right;
		fail_direction_left++;
	}
	else if (m_dir == Direction::Right)
	{
		m_x = obj.getX() - ShapeWidth;
		m_dir = Direction::Left;
		fail_direction_right++;
	}

	m_sprite.setPosition(m_x, m_y);

}

void EnemyFollow::handleCollision(Ladder& obj)
{

	//float dx = m_x - obj.getX();

	m_state = State::onLadder;

	// ON LADDER ONLY WHEN UP/DOWN
	if (m_dir == Direction::Down || m_dir == Direction::Up) {
		m_x = obj.getX(); // align when climbing
	}

	float dy = obj.getY() - m_y;

	// standing on top of ladder
	if ((m_dir == Direction::Up && !m_boardGame->canGoUp(this))) {

		if (dy >= (ShapeHeight - 3.0f) && dy <= (ShapeHeight + 3.0f)) {
			m_y = obj.getY() - ShapeHeight;
			m_state = State::onGround;
			m_dir = m_dir = Direction::Stay;
		}
	}

	m_sprite.setPosition(m_x, m_y);

}

void EnemyFollow::handleCollision(Pole& obj)
{
	//float dx = m_x - obj.getX();
	float dy = m_y - obj.getY();

	if (m_dir == Direction::Left || m_dir == Direction::Right) {
		m_y = obj.getY();

		m_sprite.setPosition(m_x, m_y);
		m_state = State::onPole; // TEST
		return;
	}

	if (dy <= 0 && dy > -1.f) {  // landing on a pole
		m_y = obj.getY(); // align
		m_dir = Direction::Stay;
		setState(MovableObject::State::onPole);

	}
	else if (dy >= 0) {
		if (m_dir == Direction::Down) { // jump off -> down
			m_y = obj.getY() + ShapeHeight;
			setState(MovableObject::State::onPole);
			m_isFalling = true;
			Resources::instance().playSound(FALL_SOUND);
		}
	}

	m_sprite.setPosition(m_x, m_y);
}

