#include "../header/GameEngine.hpp"

GameEngine::GameEngine(): gameConfig()
{
    // read game config from file
    gameConfig.readConfig();
    cout << gameConfig.getGuldenWin() << '\n';
}

GameEngine::~GameEngine(){}