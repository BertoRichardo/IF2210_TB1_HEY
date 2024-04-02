#ifndef PRODUCT_HPP
#define PRODUCT_HPP
#include "GameObject.hpp"
#include <iostream>
using namespace std;

class Product : public GameObject {
    protected:
        string type;
        string origin;
        int added_weight;
    public:
        Product(string type, string origin, int added_weight, int id, string code, string name, int price);
        ~Product();
};

#endif