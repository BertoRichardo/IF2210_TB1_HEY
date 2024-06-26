#ifndef _PETANI_HPP_
#define _PETANI_HPP_

#include "Player.hpp"
#include "../../GameObject/header/Plant.hpp"
class Petani : public Player
{
private:
    MatrixContainer<Plant *> lahan;

public:
    /**
     * User Defined Constructor
     */
    Petani(string username_,
           int weight_,
           int invRow,
           int invCol,
           int lahanRow,
           int lahanCol);

    /**
     * Destructor
     */
    ~Petani();

    MatrixContainer<Plant *> getLahan() const;

    /**
     * @return type : string
     */
    string getType() const;

    /**
     * @return pajak : int
     */
    int getPajak() const override;

    /**
     * @return plants in lahan : vector<pair<string, pair<string, string>>>
     */
    vector<pair<string, pair<string, string>>> getLahanPlant();

    /**
     * add plant to lahan
    */
    void addPlantToLahan(Plant *plant, string coordinate);

    /**
     * @return true jika ada kotak lahan yang siap dipanen
     */
    bool isPanenableMatrix();

    /**
     * Memanen tanaman atau men-throw error
     */
    void cekPanen(string cell);

    /**
     * Memanen tanaman dan memberikan pesan
     */
    void panenTanaman();

    /**
     * Memilih tanaman dari inventory dan meletakkan di lahan
     */
    void tanam();

    /**
     * Menambahkan umur setiap tanaman sebesar 1
     */
    void tambahUmurTanaman();

    /**
     * @return kekayaan dari lahan : int
     */
    int getWealthFromLahan() const;

    /**
     * Mencetak Lahan
     */
    void printLahan();
};

#endif