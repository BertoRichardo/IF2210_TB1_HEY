#ifndef BANGUNAN_HPP
#define BANGUNAN_HPP
#include "GameObject.hpp"
#include "Product.hpp"
#include <iostream>
using namespace std;

class Bangunan : public GameObject {
    protected:
        string type;
        string origin;
        Product *buffer;
    public:
        Bangunan(string type, string origin, int pro_size, int id, string code, string name, int price);
        ~Bangunan();
};

#endif