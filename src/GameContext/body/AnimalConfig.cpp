#include "../header/AnimalConfig.hpp"
#include <iostream>
using namespace std;

AnimalConfig::AnimalConfig() : Config() {
    this->type = "";
    this->weight_to_harvest = 0;
}

AnimalConfig::AnimalConfig(int id, 
                           string kode_huruf, 
                           string nama, 
                           int price, 
                           string type, 
                           int weight_to_harvest) :
                           Config(id,kode_huruf,nama,price)
{
    this->type = type;
    this->weight_to_harvest = weight_to_harvest;
}

string AnimalConfig::getType() {
    return this->type;
}

void AnimalConfig::setType(string type) {
    this->type = type;
}

int AnimalConfig::getWeightToHarvest() {
    return this->weight_to_harvest;
}

void AnimalConfig::setWeightToHarvest(int weight_to_harvest) {
    this->weight_to_harvest = weight_to_harvest;
}

void AnimalConfig::setAll(int id, 
                          string kode_huruf, 
                          string nama, 
                          int price, 
                          string type, 
                          int weight_to_harvest)
{
    setID(id);
    setKodeHuruf(kode_huruf);
    setNama(nama);
    setPrice(price);
    setType(type);
    setWeightToHarvest(weight_to_harvest);
}