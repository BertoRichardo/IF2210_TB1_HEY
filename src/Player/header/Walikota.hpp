#ifndef _WALIKOTA_HPP_
#define _WALIKOTA_HPP_

#include "Player.hpp"
#include "../../GameContext/header/BuildingConfig.hpp"
#include "../../GameContext/header/Config.hpp"
#include "../../GameObject/header/Building.hpp"
#include <set>
using namespace std;

class Walikota : public Player
{
private:
public:
    /**
     * User defined constructor
     * @param username_ : string
     */
    Walikota(string username_, int invRow, int invCol);

    /**
     * @return type : string
     */
    string getType() const;

    /**
     * Menarik pajak dari pemain
     */
    void tarikPajak();

    /**
     * Membuat bangunan dan menunjukkan IO nya
     */
    void buatBangunan(const map<string, BuildingConfig> &);

    /**
     * Menthrow
     */
    void cekRecipe(const map<string, BuildingConfig> &);

    /**
     * Menjual bangunan atau product
     */
    void beli(Shop &toko);

    /**
     * Menerima IO dan melakukan pembelian atau throw error
     */
    void cekBeli(Shop &toko);

    /**
     * Menjual bangunan atau product
     */
    void jual(Shop &toko);

    /**
     * Menerima IO dan melakukan pembelian atau throw error
     */
    void cekJual(Shop &toko);

    /**
     * @param setNama : set<string>
     * @return pair<nama, jenis>
     */

    pair<string, string> tambahPemain(set<string> &setNama);
};

#endif