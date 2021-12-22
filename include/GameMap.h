#pragma once


#include <vector>

class GameMap {

public:

    GameMap(int h, int w, int t) ;

    int getTimerValue() const;
    int getHeight() const;
    int getWidth() const;

    void setTimerValue(int);
    void setHeight(int);
    void setWidth(int);
    
    void resize(int size);

    void setStartLocationX(int x);
    void setStartLocationY(int y);
    int getStartLocationX() const;
    int getStartLocationY() const;

    char getChar(int row, int col) const;
    void push(int row, char c);

private:
    // a single map
    std::vector<std::vector<char>> m_chars; 

    // player start location
    int m_start_location_x = 0;
    int m_start_location_y = 0;

    int m_timer_value;
    int m_height;
    int m_width;

};


