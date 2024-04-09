#include "../header/Building.hpp"

Building::Building()
{
    GameObject();
}

Building::Building(const string& kodeHuruf_, const string& name_, int price_, const vector<pair<string, int>> &recipe_)
{
    GameObject(kodeHuruf_, name_, price_);
    recipe = recipe_;
}

Building::Building(const Building& other)
{
    GameObject(other);
    recipe = other.recipe;
}

Building& Building::operator=(const Building& other)
{
    if (this != &other)
    {
        kodeHuruf = other.kodeHuruf;
        name = other.name;
        price = other.price;
        recipe = other.recipe;
    }
    return *this;
}

Building::~Building()
{
    recipe.clear();
}

vector<pair<string,int>> Building::getRecipe() const
{
    vector<pair<string,int>> out = recipe;
    return out;
}

void Building::setRecipe(const vector<pair<string,int>> &recipe_)
{
    recipe = recipe_;
}

