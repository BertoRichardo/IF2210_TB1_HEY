#include "Bangunan.hpp"
#include <iostream>
using namespace std;

Bangunan::Bangunan(string type, string origin, int pro_size, int id, string code, string name, int price) : GameObject(id,code,name,price) {
    this->type = type;
    this->origin = origin;
}

Bangunan::~Bangunan() {}