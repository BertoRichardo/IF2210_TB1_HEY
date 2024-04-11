#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

using namespace std;
#include <iostream>
#include <string>
#include <map>
#include "MatrixContainer.hpp"
#include "../../GameObject/header/GameObject.hpp"
#include "../../GameObject/header/Product.hpp"
#include "../../GameException/header/GameException.hpp"

class Player
{
protected:
    string username;
    int weigth;
    int gulden;
    MatrixContainer<GameObject *> inventory;

public:
    /**
     * User defined Constructor
     * @param username_ nama player
     * -TODO: handle username tidak unik
     */
    Player(string username_);

    /**
     * Destructor
     */
    ~Player();

    /*SELECTOR*/
    /**
     * @return username : String
     */
    string getUsername() const;

    /**
     * Mengubah nama pemain
     * @param username_ nama pemain : string
     */
    void setUsername(string username_);

    /**
     * @return weight : int
     */
    int getWeight() const;

    /**
     * Mengubah berat pemain
     * @param weight_ berat pemain : int
     */
    void setWeight(int weight_);

    /**
     * @return gulden : int
     */
    int getGulden() const;

    /**
     * Mengubah gulden pemain
     * @param gulden_ gulden pemain : int
     */
    void setGulden(int gulden_);

    /*UTIL*/
    /**
     * Mendapatkan Inventory dan jumlahnya
     * @return map<string, pair<GameObject* , int>>
     */
    map<string, int> getInventoryCount();

    /*COMMAND*/

    /**
     * Melakukan command makan
     */
    void eat();

    /**
     * virtual function
     */
    virtual void jual() = 0;
    virtual void beli() = 0;
};

#endif