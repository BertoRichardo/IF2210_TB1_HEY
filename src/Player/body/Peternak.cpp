#include "../header/Peternak.hpp"

Peternak::Peternak(string username_) : Player::Player(username_)
{
    MatrixContainer<Plant *> peternakan(10, 10);
    // peternakan = peternakan_;
}

Peternak::~Peternak()
{
    peternakan.~MatrixContainer();
}

void Peternak::kasih_makan(){
    
}
