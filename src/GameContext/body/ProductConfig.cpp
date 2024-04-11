#include "../header/ProductConfig.hpp"
#include <iostream>
using namespace std;

ProductConfig::ProductConfig() : Config() {
    this->type = "";
    this->origin = "";
    this->added_weight = 0;
}

ProductConfig::ProductConfig(int id,
                             string kode_huruf,
                             string nama,
                             int price,
                             string type,
                             string origin,
                             int added_weight) :
                             Config(id,kode_huruf,nama,price)
{
    this->type = type;
    this->origin = origin;
    this->added_weight = added_weight;
}

string ProductConfig::getType() const {
    return this->type;
}

void ProductConfig::setType(string type) {
    this->type = type;
}

string ProductConfig::getOrigin() const {
    return this->origin;
}

void ProductConfig::setOrigin(string origin) {
    this->origin = origin;
}

int ProductConfig::getAddedWeight() const {
    return this->added_weight;
}

void ProductConfig::setAddedWeight(int added_weight) {
    this->added_weight = added_weight;
}

void ProductConfig::setAll(int id, 
                           string kode_huruf, 
                           string nama, 
                           int price, 
                           string type,
                           string origin,
                           int added_weight)
{
    setID(id);
    setKodeHuruf(kode_huruf);
    setNama(nama);
    setPrice(price);
    setType(type);
    setOrigin(origin);
    setAddedWeight(added_weight);
}