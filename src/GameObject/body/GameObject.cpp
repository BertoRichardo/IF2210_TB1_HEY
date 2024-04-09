#include "../header/GameObject.hpp"

GameObject::GameObject()
{
    kodeHuruf = "";
    name = "";
    price = 0;
}

GameObject::GameObject(const string &kodeHuruf_, const string &name_, int price_)
{
    kodeHuruf = kodeHuruf_;
    name = name_;
    price = price_;
}

GameObject::~GameObject()
{

}

string GameObject::getKodeHuruf() const 
{
    return kodeHuruf;
}

void GameObject::setKodeHuruf(const string &kodeHuruf_)
{
    kodeHuruf = kodeHuruf_;
}

string GameObject::getName() const \
{
    return name;
}

void GameObject::setName(const string &name_) 
{
    name = name_;
}

int GameObject::getPrice() const 
{
    return price;
}

void GameObject::setPrice(int price_)
{
    price = price_;
}

bool GameObject::isEmpty() const 
{
    return kodeHuruf == "";
}

void GameObject::clearData()
{
    kodeHuruf = "";
    name = "";
    price = 0;
}