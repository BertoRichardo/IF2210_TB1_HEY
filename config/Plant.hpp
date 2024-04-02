#ifndef PLANT_HPP
#define PLANT_HPP
#include "GameObject.hpp"
#include <iostream>
using namespace std;

class Plant : public GameObject {
    protected:
        string type;
        int duration_to_harvest;
    public:
        Plant(string type, int d, int id, string code, string name, int price);
        ~Plant();
};

#endif