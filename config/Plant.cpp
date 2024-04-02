#include "Plant.hpp"
#include <iostream>
using namespace std;

Plant::Plant(string type, int d, int id, string code, string name, int price) : GameObject(id,code,name,price) {
    this->type = type;
    this->duration_to_harvest = d;
}

Plant::~Plant() {}