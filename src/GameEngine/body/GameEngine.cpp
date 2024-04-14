#include "../header/GameEngine.hpp"

const vector<string> GameEngine::commands({"NEXT",
                                           "CETAK_PENYIMPANAN",
                                           "PUNGUT_PAJAK",
                                           "CETAK_LADANG",
                                           "CETAK_PETERNAKAN",
                                           "TANAM",
                                           "TERNAK",
                                           "BANGUN",
                                           "MAKAN",
                                           "KASIH_MAKAN",
                                           "BELI",
                                           "JUAL",
                                           "PANEN",
                                           "SIMPAN",
                                           "TAMBAH_PEMAIN", "EXIT"});

GameEngine::GameEngine() : gameConfig(), shop()
{
    // read game config from file
    gameConfig.readConfig();

    map<string, BuildingConfig> buildings = gameConfig.getBuildings();
    map<string, ProductConfig> products = gameConfig.getProducts();
    map<string, AnimalConfig> animals = gameConfig.getAnimals();
    map<string, PlantConfig> plants = gameConfig.getPlants();

    map<string, vector<Product>> productMap;

    // iterate over buildings
    for (auto building : buildings)
    {
        shop.addGoods({new Building(building.second.getKodeHuruf(), building.second.getNama(), building.second.getPrice(), building.second.getRecipe()), 0});
    }

    // iterate over products
    for (auto product : products)
    {
        Product temp(product.second.getKodeHuruf(), product.second.getNama(), product.second.getPrice(), product.second.getType(), product.second.getOrigin(), product.second.getAddedWeight());
        productMap[product.second.getOrigin()].push_back(temp);
        shop.addGoods({new Product(temp), 0});
    }

    // iterate over animals
    for (auto animal : animals)
    {
        if (animal.second.getType() == "HERBIVORE")
        {
            shop.addGoods({new Herbivore(animal.second.getKodeHuruf(), animal.second.getNama(), animal.second.getPrice(), animal.second.getType(), animal.second.getWeightToHarvest(), 0, productMap[animal.second.getNama()]), -1});
        }
        else if (animal.second.getType() == "OMNIVORE")
        {
            shop.addGoods({new Omnivore(animal.second.getKodeHuruf(), animal.second.getNama(), animal.second.getPrice(), animal.second.getType(), animal.second.getWeightToHarvest(), 0, productMap[animal.second.getNama()]), -1});
        }
        else
        {
            shop.addGoods({new Carnivore(animal.second.getKodeHuruf(), animal.second.getNama(), animal.second.getPrice(), animal.second.getType(), animal.second.getWeightToHarvest(), 0, productMap[animal.second.getNama()]), -1});
        }
    }

    // iterate over plants
    for (auto plant : plants)
    {
        shop.addGoods({new Plant(plant.second.getKodeHuruf(), plant.second.getNama(), plant.second.getPrice(), plant.second.getType(), plant.second.getDurationToHarvest(), 0, productMap[plant.second.getNama()].front()), -1});
    }
}

GameEngine::~GameEngine() {}

int GameEngine::checkCommand(string input)
{
    for (int i = 0; i < (int)commands.size(); i++)
    {
        if (input == commands[i])
        {
            return i;
        }
    }
    throw IndexInvalidException();
}

int GameEngine::getCommand()
{
    cout << "> ";
    string input;
    cin >> input;
    return checkCommand(input);
}

void GameEngine::setup()
{
}

void GameEngine::run()
{
    bool stillRun = true;
    while (stillRun)
    {
        try
        {
            int command = getCommand();

            switch (command)
            {
            case 0:
                break;
            case 15:
                stillRun = false;
                break;
            default:
                break;
            }
        }
        catch (const GameException &e)
        {
            e.displayMessage();
            cout << '\n';
        }
    }
}