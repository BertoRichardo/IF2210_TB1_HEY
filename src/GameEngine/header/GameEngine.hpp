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
    map<string, Player *> players;
    vector<string> playerNames;
    GameContext gameConfig;
    Shop shop;
    int currentTurn;
    static const vector<string> commands;

public:
    /**
     * Constructor
     */
    GameEngine();
    /**
     * Destructor
     */
    ~GameEngine();

    /* GETTER */
    vector <Player*> getPlayerVector(); 

    /* ACTION */
    /**
     * Run GameEngine
     */
    void run();

    /**
     * Setup GameEngine
     */
    void setup();

    /**
     * Default Setup for GameEngine
     */
    void defaultSetup();

    /**
     * Read State for GameEngine
     */
    void stateSetup();

    /**
     * check if command is valid
     * @return command index in vector of commands: int
     * @throw invalidCommand
     */
    int checkCommand(string input);

    /**
     * read username from user's input
     * @return command index in vector of commands: int
     */
    int readCommand();

    /**
     * read username from user's input
     * @return username: string
     */
    string readUsername(vector<string> prev, string placeholder);

    // void readState();
    // void saveState();
};

#endif