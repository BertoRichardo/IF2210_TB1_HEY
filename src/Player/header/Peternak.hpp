#ifndef _PETERNAK_HPP_
#define _PETERNAK_HPP_

#include "Player.hpp"
#include "../../GameObject/header/Animal.hpp"
class Peternak : public Player
{
private:
    MatrixContainer<Animal *> peternakan;

public:
    /**
     * User Defined Constructor
     */
    Peternak(string username_);

    /**
     * Destructor
     */
    ~Peternak();

    /**
     * Memilih ternak yang ingin diberi makan,
     * lalu memilih item dari inventory
     * lakukan validasi
     */
    void kasihMakan();

    /**
     * Memanen ternak
     */
    void panenTernak();

    /**
     * Memanen ternak
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
     * @return hasil convert dari angka huruf : 1 -> a
     * handle hingga 26 * 26 + 26
     */
    friend string angkaToHuruf();
};

#endif