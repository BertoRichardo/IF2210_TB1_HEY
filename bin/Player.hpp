#include <iostream>
#include <string>
#include "Inventory.hpp"
#include "../config/GameObject.hpp"
using namespace std;

class Player
{
protected:
    string username;
    int weigth;
    int money;
    const int inventory_amount_x;
    const int inventory_amount_y;
    Inventory<GameObject> storage;

public:
    Player(/* args */);
    ~Player();
};
