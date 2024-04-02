#include "Product.hpp"
#include <iostream>
using namespace std;

Product::Product(string type, string origin, int added_weight, int id, string code, string name, int price) : GameObject(id,code,name,price) {
    this->type = type;
    this->origin = origin;
    this->added_weight = added_weight;
}

Product::~Product() {}