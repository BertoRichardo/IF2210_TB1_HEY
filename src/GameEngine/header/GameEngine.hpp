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

    /* COMMANDS */
    void next();
    void cetak_penyimpanan();
    void pungut_pajak();
    void cetak_ladang();
    void cetak_peternakan();
    void tanam();
    void ternak();
    void bangun();
    void makan();
    void kasih_makan();
    void beli();
    void jual();
    void panen();
    void save();
    void tambah_pemain();
    void load(vector<vector<string>>);
    void info();
    bool check_win();

public:
    /**
     * Constructor
     */
    GameEngine();
    /**
     * Destructor
     */
    ~GameEngine();

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
};

#endif