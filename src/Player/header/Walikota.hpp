#ifndef _WALIKOTA_HPP_
#define _WALIKOTA_HPP_

#include "Player.hpp"
#include "../../GameContext/header/BuildingConfig.hpp"
#include "../../GameContext/header/Config.hpp"
#include "../../GameObject/header/Building.hpp"
#include <algorithm>
#include <set>
#include <algorithm>
#include <queue>
using namespace std;

class Walikota : public Player
{
private:
public:
    /**
     * User defined constructor
     * @param username_ : string
     */
    Walikota(string username_, int weight_, int invRow, int invCol);

    /**
     * @return type : string
     */
    string getType() const;

    /**
     * Membuat bangunan dan menunjukkan IO nya
     */
    void buatBangunan(const map<string, BuildingConfig> &);

    /**
     * Menthrow
     */
    void cekRecipe(const map<string, BuildingConfig> &building, map<string, int> &materials);

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
    pair<string, string> tambahPemain(vector<string> &setNama);

    /**
     * @param listOfPlayers
     * Mengurangi gulden player lain sesuai pajaknya dan menambahkan ke walikota
     */
    void tarikPajak(vector<Player *> &listOfPlayers);

    /**
     * tidak diimplementasikan untuk walikota
     */
    int getPajak() const override;

    /**
     * @param material:
     * @param recipe :
     * @return InsufficientMaterial
     */
    vector<pair<string, int>> getInsufficientMaterial(
        map<string, int> &materials,
        const vector<pair<string, int>> &recipe);

    /**
     * @return true jika walikota dapat membangun berdasarkan minimal salah satu recipe
     */
    bool isBuildAvailable(
        map<string, int> &materials,
        const vector<vector<pair<string, int>>> &listOfRecipes);
};

#endif