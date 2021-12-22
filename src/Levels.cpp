
#include "Levels.h"
using namespace std;


// load the maps from file - called only once
void Levels::loadMapsFromFile(const char* file_name) {

    ifstream if1;
    if1.open(file_name);
    if (!if1) {
        cerr << "Unable to open file " << file_name << endl;
        exit(EXIT_FAILURE);
    }
    char c;
    int width, height, timer;
    int mapindex = 0;

    while (if1 >> skipws >> height) {

        if1 >> skipws >> width;
        if1 >> skipws >> timer;
        // read the EOL
        if1.ignore(1, '\n');

        // add the map and set its size
        m_maps.push_back(GameMap(width, height, timer ));

        //m_maps[mapindex].m_chars.resize(height);
        // allocate the matrix
        //m_maps[mapindex].m_chars.resize(height);
        m_maps[mapindex].resize(height);

        // read the map
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                if1 >> noskipws >> c;
                //m_maps[mapindex].m_chars[row].push_back( c);
                m_maps[mapindex].push(row, c);

                if (c == PLAYER) {
                    m_maps[mapindex].setStartLocationX(col); // col == x
                    m_maps[mapindex].setStartLocationY(row); // row == y
                }
            }
            if1.ignore(1, '\n'); // end of each line in a map
        }
        // empty line beween maps
        if1.ignore(1, '\n');

        mapindex++;
    }

    if1.close();
}

int Levels::getCurrentLevel() const
{
    return m_current_level;
}

void Levels::setCurrentLevel(int lev)
{
    if (lev <0 || lev > m_maps.size())
        lev = 0;
    m_current_level = lev;
}

bool Levels::loadNextMap()
{
    Resources::instance().playSound(PASS_SOUND);

    if (m_current_level < m_maps.size()-1) {
        m_current_level++;
        return true;
    }
    return false;
}

GameMap Levels::getCurrentMap() const
{
    return m_maps[m_current_level];
}

float Levels::getWindowHeight() const
{
    return m_maps[m_current_level].getHeight()* ShapeHeight;
}

float Levels::getWindowWidth() const
{
    return m_maps[m_current_level].getWidth() * ShapeWidth;
}
