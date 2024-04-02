#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP
using namespace std;
#include <string>

class GameObject
{
protected:
    int id;
    string kode;
    string name;
    int price;

public:
    GameObject(int id, string kode, string name, int price)
    {
        // GAME_OBJECT_COUNT++;
        this->id = id;
        this->kode = kode;
        this->name = name;
        this->price = price;
    }
    ~GameObject() {}
    virtual int getType() = 0;
    static const int PLANT_OBJECT = 0;    // 0
    static const int ANIMAL_OBJECT = 1;   // 1
    static const int PRODUCT_OBJECT = 2;  // 2
    static const int BUILDING_OBJECT = 3; // 3
    static int GAME_OBJECT_COUNT;         // mungkin ada, mungkin gak
};

class Animal : public GameObject
{
private:
    string type;
    int weight_to_harvest;

public:
    Animal(string type, int w) : GameObject(id, kode, name, price)
    {
        this->type = type;
        weight_to_harvest = w;
    }
};

#endif