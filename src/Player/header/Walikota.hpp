#ifndef _WALIKOTA_HPP_
#define _WALIKOTA_HPP_

#include "Player.hpp"
#include "../../GameContext/header/BuildingConfig.hpp"
#include "../../GameContext/header/Config.hpp"
using namespace std;

class Walikota : public Player
{
private:
public:
    /**
     * User defined constructor
     * @param username_ : string
     */
    Walikota(string username_);

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
     * Membangun bangunan atau men-throw eror
     */
    void jual();
    void beli();
};

#endif