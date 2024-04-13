#ifndef _PETERNAK_HPP_
#define _PETERNAK_HPP_

#include "Player.hpp"
#include "../../GameObject/header/Animal.hpp"
class Peternak : public Player
{
private:

public:
    MatrixContainer<Animal *> peternakan;
    /**
     * User Defined Constructor
     */
    Peternak(string username_,
             int invRow, int invCol,
             int peternakanRow, int peternakanCol);

    /**
     * Destructor
     */
    ~Peternak();

    /**
     * @return type : string
     */
    string getType() const;

    /**
     * @return peternakan
     */
    MatrixContainer<Animal *> getPeternakan() const;

    /**
     * @return pajak : int
     */
    int getPajak() const;

    /**
     * Memilih ternak yang ingin diberi makan,
     * lalu memilih item dari inventory
     * lakukan validasi
     */
    void kasihMakan();

    /**
     * Memanen ternak dan mengeluarkan pesan
     */
    void panenTernak();

    /**
     * Memanen ternak atau men-throw error
     */
    void cekPanen(string cell);

    /**
     * @return true jika ada kotak peternakan yang siap dipanen
     */
    bool isPanenableMatrix();

    /**
     * Memilih ternak dari inventory dan meletakkan di peternakan
     */
    void letakTernak();

    /**
     * Mencetak peternakan
     */
    void printPeternakan();
};

#endif