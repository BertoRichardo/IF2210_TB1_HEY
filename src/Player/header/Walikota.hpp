#ifndef _WALIKOTA_HPP_
#define _WALIKOTA_HPP_

#include "Player.hpp"

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
    void buatBangunan(const map<string, bangunanConfig>);

    /**
     * Membangun bangunan atau men-throw eror
     */
    void cekRecipe(map<GameObject *, int> recipe);
    void jual();
    void beli();
};

#endif