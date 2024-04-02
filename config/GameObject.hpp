#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP
using namespace std;
#include <string>

class GameObject
{
protected:
    int id;
    string code;
    string name;
    int price;

public:
    GameObject(int id, string code, string name, int price);
    ~GameObject();
    virtual int getType() = 0;
    static const int PLANT_OBJECT = 0;    // 0
    static const int ANIMAL_OBJECT = 1;   // 1
    static const int PRODUCT_OBJECT = 2;  // 2
    static const int BUILDING_OBJECT = 3; // 3
    static int GAME_OBJECT_COUNT;         // mungkin ada, mungkin gak
};

#endif