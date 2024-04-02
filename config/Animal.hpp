#ifndef ANIMAL_HPP
#define ANIMAL_HPP
#include "GameObject.hpp"
#include <iostream>
using namespace std;

class Animal : public GameObject {
    protected:
        string type;
        int weight_to_harvest;
    public:
        Animal(string type, int w, int id, string code, string name, int price);
        ~Animal();
};


#endif