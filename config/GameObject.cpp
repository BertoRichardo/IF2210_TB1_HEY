#include "GameObject.hpp"
#include <iostream>
using namespace std;

int GameObject::GAME_OBJECT_COUNT = 0;

GameObject::GameObject(int id, string code, string name, int price) {
    this->id = id;
    this->code = code;
    this->name = name;
    this->price = price;
}

GameObject::~GameObject() {}