#include "../header/Product.hpp"

Product::Product(): GameObject()
{
    type = "";
    origin = "";
    addedWeight = 0;
}

Product::Product(const string& kodeHuruf_, const string& name_, int price_, const string& type_, const string& origin_, int addedWeight_)
{
    GameObject(kodeHuruf_, name_, price_);
    type = type_;
    origin = origin_;
    addedWeight = addedWeight_;
}

Product::Product(const Product& other)
{
    GameObject(other);
    type = other.type;
    origin = other.origin;
    addedWeight = other.addedWeight;
}

Product& Product::operator=(const Product& other)
{
    if (this != &other)
    {
        kodeHuruf = other.kodeHuruf;
        name = other.name;
        price = other.price;
        type = other.type;
        origin = other.origin;
        addedWeight = other.addedWeight;
    }
    return *this;
}

Product::~Product()
{}

string Product::getType() const
{
    return type;
}
void Product::setType(const string &type_)
{
    type = type_;
}
string Product::getOrigin() const
{
    return origin;
}
void Product::setOrigin(const string &origin_)
{
    origin = origin_;
}
int Product::getAddedWeight() const
{
    return addedWeight;
}
void Product::setAddedWeight(int addedWeight_)
{
    addedWeight = addedWeight_;
}