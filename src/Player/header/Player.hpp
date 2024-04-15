#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

using namespace std;
#include <iostream>
#include <string>
#include <map>
#include <cmath>
#include "../../Container/header/MatrixContainer.hpp"
#include "../../Shop/header/Shop.hpp"
#include "../../GameObject/header/GameObject.hpp"
#include "../../GameObject/header/Animal.hpp"
#include "../../GameObject/header/Plant.hpp"
#include "../../GameObject/header/Product.hpp"
#include "../../GameObject/header/Building.hpp"
#include "../../GameException/header/GameException.hpp"
#include "../../Util/header/Util.hpp"

class Player
{
protected:
    string username;
    int weigth;
    int gulden;

public:
    MatrixContainer<GameObject *> inventory;
    /**
     * User defined Constructor
     * @param username_ nama player
     * -TODO: handle username tidak unik
     */
    Player(string username_, int invRow, int invCol);

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
     * @return kekayaan from inventory : int
     */
    int getWealthFromInv() const;

    /**
     * @return type : string
     */
    virtual string getType() const;

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

    /*COMMAND*/

    /**
     * Melakukan command makan
     */
    void eat();

    /**
     * jual : virtual function
     * @param toko : Shop
     */
    virtual void jual(Shop &toko);

    /**
     * beli : sama untuk petani dan peternak, override untuk walikota
     * @param toko: reference dari Shop
     */
    virtual void beli(Shop &toko );

    /**
     * Melakukan proses pembelian atau throw erro
     */
    virtual void cekBeli(Shop &toko);

    /**
     * Melakukan proses penjualan atau throw erro
     * @param toko : Shop
     */
    virtual void cekJual(Shop &toko);
    /**
     * parser slot
     */

    /**
     * Mencetak Header untuk matrix
     * @param judul : string judul header
     */
    void printHeader(string judul);

    /**
     * Mencetak header inventory, isinya, dan total slot kosong
     */
    void printInventory();

    /**
     * Mendapatkan nominal pajak yang perlu dibayar oleh player
     */
    virtual int getPajak() const;

    /**
     * @param guldenToWin : int
     * @param weigthToWin : int
     * @return apakah pemain menang atau tidak
     */
    bool isPlayerWin(int guldenToWin, int weigthToWin);
};

#endif