#include "../header/Animal.hpp"

/**Animal Base Class*/
///
///
Animal::Animal() : GameObject()
{
    type = "";
    harvestWeight = 0;
    weight = 0;
}

Animal::Animal(
    const string& kodeHuruf_, 
    const string& name_, 
    int price_, 
    const string& type_, 
    int harvestWeight_, 
    int weight_, 
    const vector<Product>& products_
): GameObject(kodeHuruf_, name_, price_) 
{
    type = type_;
    harvestWeight = harvestWeight_;
    weight = weight_;
    products = products_;
}

Animal::Animal(const Animal& other): GameObject(other)
{
    type = other.type;
    harvestWeight = other.harvestWeight;
    weight = other.weight;
    products = other.products;
}

Animal& Animal::operator=(const Animal& other)
{
    if (this != &other)
    {
        kodeHuruf = other.kodeHuruf;
        name = other.name;
        price = other.price;
        type = other.type;
        harvestWeight = other.harvestWeight;
        weight = other.weight;
        products = other.products;
    }
    return *this;
}

Animal::~Animal()
{
    type.clear();
}

string Animal::getType() const 
{ 
    return type; 
}
void Animal::setType(const string &type_) 
{ 
    type = type_; 
}

int Animal::getHarvestWeight() const 
{ 
    return harvestWeight; 
}
void Animal::setHarvestWeight(int harvestWeight_) 
{ 
    harvestWeight = harvestWeight_; 
}

int Animal::getWeight() const 
{ 
    return weight; 
}
void Animal::setWeight(int weight_) 
{ 
    weight = weight_; 
}

vector<Product> Animal::getProduct() const 
{ 
    return products; 
}
void Animal::setProduct(const vector<Product> &products_) 
{ 
    products = products_; 
}

bool Animal::isReadyToHarvest()
{
    return weight >= harvestWeight;
}

vector<Product> Animal::harvest()
{
    return products;
}

///
///
///
/* Carnivore */
Carnivore::Carnivore(): Animal() {}

Carnivore::Carnivore(
    const string& kodeHuruf_, 
    const string& name_, 
    int price_, 
    const string& type_, 
    int harvestWeight_, 
    int weight_, 
    const vector<Product>& products_
) : Animal(
    kodeHuruf_, 
    name_, 
    price_, 
    type_, 
    harvestWeight_, 
    weight_, 
    products_
) {}

Carnivore::Carnivore(const Carnivore& other): Animal(other) {}

Carnivore& Carnivore::operator=(const Carnivore& other)
{
    if (this != &other)
    {
        kodeHuruf = other.kodeHuruf;
        name = other.name;
        price = other.price;
        type = other.type;
        harvestWeight = other.harvestWeight;
        weight = other.weight;
        products = other.products;
    }
    return *this;
}

Carnivore::~Carnivore() {}

void Carnivore::feed(const Product &food)
{
    if (food.getType() != "PRODUCT_ANIMAL") {
        throw FeedTypeInvalidException(type, food.getType());
    } else {
        weight += food.getAddedWeight();
    }
}

void Carnivore::operator+=(const Product &food)
{
    this->feed(food);
}


///
///
///
/* Herbivore */
Herbivore::Herbivore(): Animal() {}

Herbivore::Herbivore(
    const string& kodeHuruf_, 
    const string& name_, 
    int price_, 
    const string& type_, 
    int harvestWeight_, 
    int weight_, 
    const vector<Product>& products_
) : Animal(
    kodeHuruf_, 
    name_, 
    price_, 
    type_, 
    harvestWeight_, 
    weight_, 
    products_
) {}

Herbivore::Herbivore(const Herbivore& other): Animal(other) {}

Herbivore& Herbivore::operator=(const Herbivore& other)
{
    if (this != &other)
    {
        kodeHuruf = other.kodeHuruf;
        name = other.name;
        price = other.price;
        type = other.type;
        harvestWeight = other.harvestWeight;
        weight = other.weight;
        products = other.products;
    }
    return *this;
}

Herbivore::~Herbivore() {}

void Herbivore::feed(const Product &food)
{
    if (food.getType() != "PRODUCT_FRUIT_PLANT") {
        throw FeedTypeInvalidException(type, food.getType());
    } else {
        weight += food.getAddedWeight();
    }
}

void Herbivore::operator+=(const Product &food)
{
    this->feed(food);
}


///
///
///
/* Omnivore */
Omnivore::Omnivore(): Animal() {}

Omnivore::Omnivore(
    const string& kodeHuruf_, 
    const string& name_, 
    int price_, 
    const string& type_, 
    int harvestWeight_, 
    int weight_, 
    const vector<Product>& products_
) : Animal(
    kodeHuruf_, 
    name_, 
    price_, 
    type_, 
    harvestWeight_, 
    weight_, 
    products_
) {}

Omnivore::Omnivore(const Omnivore& other): Animal(other) {}

Omnivore& Omnivore::operator=(const Omnivore& other)
{
    if (this != &other)
    {
        kodeHuruf = other.kodeHuruf;
        name = other.name;
        price = other.price;
        type = other.type;
        harvestWeight = other.harvestWeight;
        weight = other.weight;
        products = other.products;
    }
    return *this;
}

Omnivore::~Omnivore() {}

void Omnivore::feed(const Product &food)
{
    if (food.getType() != "PRODUCT_FRUIT_PLANT" && food.getType() != "PRODUCT_ANIMAL") {
        throw FeedTypeInvalidException(type, food.getType());
    } else {
        weight += food.getAddedWeight();
    }
}

void Omnivore::operator+=(const Product &food)
{
    this->feed(food);
}