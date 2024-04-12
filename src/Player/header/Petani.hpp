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
    Petani(string username_, int row, int col);

    /**
     * Destructor
     */
    ~Petani();

    /**
     * Memanen tanaman atau men-throw error
     */
    void cekPanen(string cell);

    /**
     * @return true jika ada kotak lahan yang siap dipanen
     */
    bool isPanenableMatrix();

    /**
     * Memanen tanaman dan memberikan pesan
     */
    void panenTanaman();

    /**
     * Memilih tanaman dari inventory dan meletakkan di lahan
     */
    void tanam();

    /**
     * @return hasil convert dari angka huruf : 1 -> a
     * handle hingga 26 * 26 + 26
     */
    friend string angkaToHuruf();
};

#endif