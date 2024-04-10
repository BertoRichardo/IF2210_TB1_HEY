#include "../header/BuildingConfig.hpp"
#include "../../GameException/header/GameException.hpp"
#include <iostream>
using namespace std;

BuildingConfig::BuildingConfig() : Config() {}

BuildingConfig::BuildingConfig(int id,
                               string kode_huruf,
                               string nama,
                               int price,
                               vector<pair<string,int>> recipe) :
                               Config(id,kode_huruf,nama,price)
{
    this->recipe = recipe;
}

vector<pair<string,int>> BuildingConfig::getRecipe() {
    return this->recipe;
}

void BuildingConfig::setRecipe(const vector<pair<string,int>> recipe) {
    this->recipe = recipe;
}

pair<string,int> BuildingConfig::getRecipeComp(int idx) {
    cout << idx << " " << this->recipe.size() << endl;
    if (idx >= this->recipe.size()) {
        throw IndexInvalidException();
    }
    return this->recipe.at(idx);
}

void BuildingConfig::setRecipeComp(pair<string,int> element, int idx) {
    this->recipe.at(idx) = element;
}

string BuildingConfig::getProductName(int idx) {
    return this->recipe.at(idx).first;
}

void BuildingConfig::setProductName(string nama, int idx) {
    this->recipe.at(idx).first = nama;
}

int BuildingConfig::getQuantity(int idx) {
    return this->recipe.at(idx).second;
}

void BuildingConfig::setQuantity(int val, int idx) {
    this->recipe.at(idx).second = val;
}

void BuildingConfig::setAll(int id, 
                            string kode_huruf, 
                            string nama, 
                            int price, 
                            vector<pair<string,int>> recipe)
{
    setID(id);
    setKodeHuruf(kode_huruf);
    setNama(nama);
    setPrice(price);
    setRecipe(recipe);
}