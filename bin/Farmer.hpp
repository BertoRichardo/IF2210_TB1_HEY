#include <iostream>
#include "Player.hpp"
#include "Inventory.hpp"
#include "../config/Plant.hpp"
using namespace std;

class Farmer : public Player
{
private:
    Inventory<Plant> lahan;

public:
    Farmer(/* args */);
    ~Farmer();
};
