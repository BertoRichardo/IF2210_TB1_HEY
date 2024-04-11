#ifndef _PETERNAK_HPP_
#define _PETERNAK_HPP_

#include "header/Player.hpp"
#include "../../GameObject/header/Plant.hpp"
class Peternak : public Player
{
private:
    MatrixContainer<Product *> peternakan;

public:
    Peternak(string username_);
    ~Peternak();
    void kasih_makan();
    void panen_ternak();
    void letak_ternak();
    void jual();
    void beli();
};

#endif