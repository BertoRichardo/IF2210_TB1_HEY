#ifndef _GAME_ENGINE_HPP_
#define _GAME_ENGINE_HPP_

#include "../../Player/header/Petani.hpp"
#include "../../Player/header/Walikota.hpp"
#include "../../Player/header/Peternak.hpp"
#include "../../Shop/header/Shop.hpp"
#include "../../GameContext/header/GameContext.hpp"
#include "../header/FileController.hpp"
#include <iostream>
#include <vector>

class GameEngine
{
private:
    vector<Player *> players;
    GameContext gameConfig;
    Shop shop;

public:
    GameEngine(); 
    ~GameEngine();
    // void run();
    // void setup();
    // void getCommand();
    // void readState();
    // void saveState();
};

#endif