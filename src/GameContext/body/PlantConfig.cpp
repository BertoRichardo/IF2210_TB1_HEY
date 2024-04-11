#include "../header/PlantConfig.hpp"
#include <iostream>
using namespace std;

PlantConfig::PlantConfig() : Config() {
    this->type = "";
    this->duration_to_harvest = 0;
}

PlantConfig::PlantConfig(int id,
                         string kode_huruf,
                         string nama,
                         int price,
                         string type,
                         int duration_to_harvest) :
                         Config(id,kode_huruf,nama,price)
{
    this->type = type;
    this->duration_to_harvest = duration_to_harvest;
}

string PlantConfig::getType() const {
    return this->type;
}

void PlantConfig::setType(string type) {
    this->type = type;
}

int PlantConfig::getDurationToHarvest() const {
    return this->duration_to_harvest;
}

void PlantConfig::setDurationToHarvest(int duration_to_harvest) {
    this->duration_to_harvest = duration_to_harvest;
}

void PlantConfig::setAll(int id, 
                         string kode_huruf, 
                         string nama, 
                         int price, 
                         string type, 
                         int duration_to_harvest)
{
    setID(id);
    setKodeHuruf(kode_huruf);
    setNama(nama);
    setPrice(price);
    setType(type);
    setDurationToHarvest(duration_to_harvest);
}