#include "../header/Plant.hpp"

Plant::Plant()
{
    GameObject();
    type = "";
    harvestDuration = 0;
    duration = 0;
}

Plant::Plant(const string& kodeHuruf_, const string& name_, int price_, const string& type_, int harvestDuration_, int duration_, const Product& product_)
{
    GameObject(kodeHuruf_, name_, price_);
    type = type_;
    harvestDuration = harvestDuration_;
    duration = duration_;
    product = product_;
}

Plant::Plant(const Plant& other)
{
    GameObject(other);
    type = other.type;
    harvestDuration = other.harvestDuration;
    duration = other.duration;
    product = other.product;
}

Plant& Plant::operator=(const Plant& other)
{
    if (this != &other) 
    {
        kodeHuruf = other.kodeHuruf;
        name = other.name;
        price = other.price;
        type = other.type;
        harvestDuration = other.harvestDuration;
        duration = other.duration;
        product = other.product;
    }
    return *this;
}

Plant::~Plant()
{
    type.clear();
}

string Plant::getType()
{
    return type;
}

void Plant::setType(const string &type_)
{
    type = type_;
}

int Plant::getHarvestDuration() const
{
    return harvestDuration;
}

void Plant::setHarvestDuration(int harvestDuration_)
{
    harvestDuration = harvestDuration_;
}

int Plant::getDuration() const
{
    return duration;
}

void Plant::setDuration(int duration_)
{
    duration = duration_;
}

Product Plant::getProduct() const
{
    return product;
}

void Plant::setProduct(const Product &product_)
{
    product = product_;
}

Product Plant::harvest()
{
    return product;
}

void Plant::grow()
{
    duration++;
}

void Plant::operator++(int)
{
    duration++;
}