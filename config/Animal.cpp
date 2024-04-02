#include "Animal.hpp"
#include <iostream>
using namespace std;

Animal::Animal(string type, int w, int id, string code, string name, int price) : GameObject(id,code,name,price) {
    this->type = type;
    this->weight_to_harvest = w;
}