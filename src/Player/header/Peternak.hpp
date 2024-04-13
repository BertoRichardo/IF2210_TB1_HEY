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
    Peternak(string username_, int row, int col);

    /**
     * Destructor
     */
    ~Peternak();

    /**
     * @return type : string
     */
    string getType() const;

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
     * @return hasil convert dari angka huruf : 1 -> a
     * handle hingga 26 * 26 + 26
     */
    friend string angkaToHuruf();
};

#endif