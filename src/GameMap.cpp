

#include "GameMap.h"

GameMap::GameMap(int w, int h, int t) : m_width(w), m_height(h), m_timer_value(t)
{
}

int GameMap::getTimerValue() const
{
	return m_timer_value;
}

int GameMap::getHeight() const
{
	return m_height;
}

int GameMap::getWidth() const
{
	return m_width;
}

void GameMap::setTimerValue(int v)
{
	m_timer_value = v;
}

void GameMap::setHeight(int h)
{
	m_height = h;
}

void GameMap::setWidth(int w)
{
	m_width = w;
}



void GameMap::resize(int size)
{
	m_chars.resize(size);
}

void GameMap::setStartLocationX(int x)
{
	m_start_location_x = x;
}

void GameMap::setStartLocationY(int y)
{
	m_start_location_y = y;
}

int GameMap::getStartLocationX() const
{
	return m_start_location_x;
}

int GameMap::getStartLocationY() const
{
	return m_start_location_y;
}

char GameMap::getChar(int row, int col) const
{
	return m_chars[row][col];
}

void GameMap::push(int row, char c)
{
	m_chars[row].push_back(c);
}
