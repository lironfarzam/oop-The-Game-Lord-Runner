#pragma once


#include "GameMap.h"
#include "constants.h"
#include "Player.h"

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cstdio>

#include <io.h>

class Levels {
public:
    void loadMapsFromFile(const char* file_name);
    bool loadNextMap();

    int getCurrentLevel() const;
    void setCurrentLevel(int lev);

    GameMap getCurrentMap() const;
    float getWindowHeight() const;
    float getWindowWidth() const;

private:

    std::vector<GameMap> m_maps;
    int m_current_level = 0;
};


