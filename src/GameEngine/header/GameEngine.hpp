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
    int currentTurn;
    static const vector<string> commands;

public:
    GameEngine();
    ~GameEngine();
    void run();
    void setup();
    int checkCommand(string input);
    int getCommand();
    // void readState();
    // void saveState();
};

#endif