#include "../header/GameContext.hpp"
#include "../../GameEngine/header/FileController.hpp"
#include <iostream>
using namespace std;

GameContext::GameContext() {}

GameContext::GameContext(map<string,AnimalConfig> animals,
                         map<string,BuildingConfig> buildings,
                         map<string,PlantConfig> plants,
                         map<string,ProductConfig> products)
{
    this->animals = animals;
    this->buildings = buildings;
    this->plants = plants;
    this->products = products;
}

map<string,AnimalConfig> GameContext::getAnimals() const {
    return this->animals;
}

void GameContext::setAnimals(map<string,AnimalConfig> animals) {
    this->animals = animals;
}

map<string,BuildingConfig> GameContext::getBuildings() const {
    return this->buildings;
}

void GameContext::setBuildings(map<string,BuildingConfig> buildings) {
    this->buildings = buildings;
}

map<string,PlantConfig> GameContext::getPlants() const {
    return this->plants;
}

void GameContext::setPlants(map<string,PlantConfig> plants) {
    this->plants = plants;
}

map<string,ProductConfig> GameContext::getProducts() const {
    return this->products;
}

void GameContext::setProducts(map<string,ProductConfig> products) {
    this->products = products;
}

void GameContext::readConfig() {
    vector<vector<string>> animal_list;
    vector<vector<string>> plant_list;
    vector<vector<string>> building_list;
    vector<vector<string>> product_list;

    animal_list = FileController::readFile("../../../config/animal.txt");
    plant_list = FileController::readFile("../../../config/plant.txt");
    building_list = FileController::readFile("../../../config/recipe.txt");
    product_list = FileController::readFile("../../../product.txt");

    int temp_id;
    string temp_kode_huruf;
    string temp_nama;
    string temp_type;
    string temp_origin;
    int temp_price;
    int temp_weight_to_harvest;
    int temp_duration_to_harvest;
    int temp_added_weight;
    pair<string,int> temp_comp;
    vector<pair<string,int>> temp_recipe;

    AnimalConfig temp_animal;
    PlantConfig temp_plant;
    BuildingConfig temp_building;
    ProductConfig temp_product;

    // Assign animal to game context
    for (int i = 0; i < animal_list.size(); i++) {
        temp_id = stoi(animal_list.at(i).at(0));
        temp_kode_huruf = animal_list.at(i).at(1);
        temp_nama = animal_list.at(i).at(2);
        temp_type = animal_list.at(i).at(3);
        temp_weight_to_harvest = stoi(animal_list.at(i).at(4));
        temp_price = stoi(animal_list.at(i).at(5));
        temp_animal.setAll(temp_id,temp_kode_huruf,temp_nama,temp_price,temp_type,temp_weight_to_harvest);
        this->animals.insert({temp_nama,temp_animal});
    }

    // Assign plant to game context
    for (int i = 0; i < plant_list.size(); i++) {
        temp_id = stoi(plant_list.at(i).at(0));
        temp_kode_huruf = plant_list.at(i).at(1);
        temp_nama = plant_list.at(i).at(2);
        temp_type = plant_list.at(i).at(3);
        temp_duration_to_harvest = stoi(plant_list.at(i).at(4));
        temp_price = stoi(plant_list.at(i).at(5));
        temp_plant.setAll(temp_id,temp_kode_huruf,temp_nama,temp_price,temp_type,temp_duration_to_harvest);
        this->plants.insert({temp_nama,temp_plant});
    }

    // Assign building to game context
    for (int i = 0; i < building_list.size(); i++) {
        temp_id = stoi(building_list.at(i).at(0));
        temp_kode_huruf = building_list.at(i).at(1);
        temp_nama = building_list.at(i).at(2);
        temp_price = stoi(building_list.at(i).at(3));
        for (int j = 4; j < building_list.at(i).size(); j += 2) {
            temp_comp.first = building_list.at(i).at(j);
            temp_comp.second = stoi(building_list.at(i).at(j+1));
            temp_recipe.push_back(temp_comp);
        }
        temp_building.setAll(temp_id,temp_kode_huruf,temp_nama,temp_price,temp_recipe);
        this->buildings.insert({temp_nama,temp_building});
        temp_recipe.clear();
    }

    // Assign product to game context
    for (int i = 0; i < product_list.size(); i++) {
        temp_id = stoi(product_list.at(i).at(0));
        temp_kode_huruf = product_list.at(i).at(1);
        temp_nama = product_list.at(i).at(2);
        temp_type = product_list.at(i).at(3);
        temp_origin = product_list.at(i).at(4);
        temp_added_weight = stoi(product_list.at(i).at(5));
        temp_price = stoi(product_list.at(i).at(6));
        temp_product.setAll(temp_id,temp_kode_huruf,temp_nama,temp_price,temp_type,temp_origin,temp_added_weight);
        this->products.insert({temp_nama,temp_product});
    }
}