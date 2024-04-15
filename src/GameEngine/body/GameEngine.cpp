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
}

GameEngine::~GameEngine()
{
}

vector<Player *> GameEngine::getPlayerVector()
{
    vector<Player *> res;
    for (auto player : players)
    {
        res.push_back(player.second);
    }
    return res;
}

int GameEngine::checkCommand(string input)
{
    for (int i = 0; i < (int)commands.size(); i++)
    {
        if (input == commands[i])
        {
            return i;
        }
    }
    throw CommandInvalidException();;
}

int GameEngine::readCommand()
{
    cout << ">> ";
    string input;
    cin >> input;
    cout << endl;
    return checkCommand(input);
}

void GameEngine::setup()
{
    Util::displayStartingScreen();

    bool isValid = false;

    cout << "Selamat datang di permainan Kelola Kerajaan" << "\n\n";

    while (!isValid)
    {
        try
        {
            string input;
            cout << "Apakah Anda ingin memuat state? (y/n): ";
            cin >> input;
            cout << endl;

            if (input == "y" || input == "Y")
            {
                stateSetup();
            }
            else if (input == "n" || input == "N")
            {
                defaultSetup();
            }
            else
            {
                throw InputInvalidException();
            }

            isValid = true;
        }
        catch (const GameException &e)
        {
            e.displayMessage();
        }

        cout << "Giliran saat ini adalah pemain dengan username " << playerNames[currentTurn] << " dan role " << players[playerNames[currentTurn]]->getType() << "\n\n";
    }

}

void GameEngine::defaultSetup()
{
    // initialize default shop setup
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

    // read players username

    // create walikota
    string walikota = readUsername(playerNames, "walikota");
    playerNames.push_back(walikota);
    players[walikota] = new Walikota(walikota, gameConfig.getInventoryRow(), gameConfig.getInventoryCol());

    // create peternak
    string peternak = readUsername(playerNames, "peternak1");
    playerNames.push_back(peternak);
    players[peternak] = new Peternak(peternak, gameConfig.getInventoryRow(), gameConfig.getInventoryCol(), gameConfig.getPeternakanRow(), gameConfig.getPeternakanCol());

    // create petani
    string petani = readUsername(playerNames, "petani1");
    playerNames.push_back(petani);
    players[petani] = new Petani(petani, gameConfig.getInventoryRow(), gameConfig.getInventoryCol(), gameConfig.getLahanRow(), gameConfig.getLahanCol());

    // sort playerNames
    sort(playerNames.begin(), playerNames.end());
    currentTurn = 0;
}
void GameEngine::stateSetup() {}

void GameEngine::run()
{
    bool stillRun = true;
    while (stillRun)
    {
        try
        {
            int command = readCommand();

            switch (command)
            {
            case 0:
                next();
                break;
            case 1:
                cetak_penyimpanan();
                break;
            case 2:
                pungut_pajak();
                break;
            case 3:
                cetak_ladang();
                break;
            case 4:
                cetak_peternakan();
                break;
            case 5:
                tanam();
                break;
            case 6:
                ternak();
                break;
            case 7:
                bangun();
                break;
            case 8:
                makan();
                break;
            case 9:
                kasih_makan();
                break;
            case 10:
                beli();
                break;
            case 11:
                jual();
                break;
            case 12:
                panen();
                break;
            case 13:
                save();
                break;
            case 14:
                tambah_pemain();
                break;
            case 15:
                stillRun = false;
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

string GameEngine::readUsername(vector<string> prev, string placeholder)
{
    bool isDone = false;
    string input;
    while (!isDone)
    {
        try
        {
            cout << "Masukkan username " << placeholder << ": ";
            cin >> input;
            cout << endl;
            if (input == "")
            {
                throw InputInvalidException();
            }
            if (Util::containSpace(input))
            {
                throw InputInvalidException();
            }
            for (auto username : prev)
            {
                if (input == username)
                {
                    throw InputInvalidException();
                }
            }
            isDone = true;
        }
        catch (const GameException &e)
        {
            e.displayMessage();
        }
    }
    return input;
}

void GameEngine::next()
{
    if (players[playerNames[currentTurn]]->getType() == "PETANI")
    {
        dynamic_cast<Petani *>(players[playerNames[currentTurn]])->tambahUmurTanaman();
    }
    /**
     * @todo: handle if player win
     */
    currentTurn = (currentTurn + 1) % (int)playerNames.size();
    cout << "Giliran saat ini adalah pemain dengan username " << playerNames[currentTurn] << " dan role " << players[playerNames[currentTurn]]->getType() << "\n\n";
}

void GameEngine::cetak_penyimpanan()
{
    players[playerNames[currentTurn]]->printInventory();
}

void GameEngine::pungut_pajak()
{
    if (players[playerNames[currentTurn]]->getType() != "WALIKOTA")
    {
        /**
         * @todo: throw inaccessible command
         */
        throw CommandInvalidException();
    }
    vector<Player *> vecPlayer = getPlayerVector();
    dynamic_cast<Walikota *>(players[playerNames[currentTurn]])->tarikPajak(vecPlayer);
}

void GameEngine::cetak_ladang()
{
    if (players[playerNames[currentTurn]]->getType() != "PETANI")
    {
        /**
         * @todo: throw inaccessible command
         */
        throw CommandInvalidException();
    }
    dynamic_cast<Petani *>(players[playerNames[currentTurn]])->printLahan();
}

void GameEngine::cetak_peternakan()
{
    if (players[playerNames[currentTurn]]->getType() != "PETERNAK")
    {
        /**
         * @todo: throw inaccessible command
         */
        throw CommandInvalidException();
    }
    dynamic_cast<Peternak *>(players[playerNames[currentTurn]])->printPeternakan();
}

void GameEngine::tanam()
{
    if (players[playerNames[currentTurn]]->getType() != "PETANI")
    {
        /**
         * @todo: throw inaccessible command
         */
        throw CommandInvalidException();
    }
    dynamic_cast<Petani *>(players[playerNames[currentTurn]])->tanam();
}

void GameEngine::ternak()
{
    if (players[playerNames[currentTurn]]->getType() != "PETERNAK")
    {
        /**
         * @todo: throw inaccessible command
         */
        throw CommandInvalidException();
    }
    dynamic_cast<Peternak *>(players[playerNames[currentTurn]])->letakTernak();
}

void GameEngine::bangun()
{
    if (players[playerNames[currentTurn]]->getType() != "WALIKOTA")
    {
        /**
         * @todo: throw inaccessible command
         */
        throw CommandInvalidException();
    }
    dynamic_cast<Walikota *>(players[playerNames[currentTurn]])->buatBangunan(gameConfig.getBuildings());
}

void GameEngine::makan()
{
    players[playerNames[currentTurn]]->eat();
}

void GameEngine::kasih_makan()
{
    if (players[playerNames[currentTurn]]->getType() != "PETERNAK")
    {
        /**
         * @todo: throw inaccessible command
         */
        throw CommandInvalidException();
    }
    dynamic_cast<Peternak *>(players[playerNames[currentTurn]])->kasihMakan();
}

void GameEngine::beli()
{
    players[playerNames[currentTurn]]->beli(shop);
}

void GameEngine::jual()
{
    players[playerNames[currentTurn]]->jual(shop);
}

void GameEngine::panen()
{
    if (players[playerNames[currentTurn]]->getType() == "PETERNAK")
    {
        dynamic_cast<Peternak *>(players[playerNames[currentTurn]])->panenTernak();
    }
    else if (players[playerNames[currentTurn]]->getType() == "PETANI")
    {
        dynamic_cast<Petani *>(players[playerNames[currentTurn]])->panenTanaman();
    }
    else
    {
        /**
         * @todo: throw inaccessible command
         */
        throw CommandInvalidException();
    }
}

void GameEngine::save()
{
    /**
     * @todo: lengkapin save
     */
}

void GameEngine::tambah_pemain()
{
    if (players[playerNames[currentTurn]]->getType() != "WALIKOTA")
    {
        /**
         * @todo: throw inaccessible command
         */
        throw CommandInvalidException();
    }
    pair<string, string> res = dynamic_cast<Walikota *>(players[playerNames[currentTurn]])->tambahPemain(playerNames);

    // add new player
    playerNames.push_back(res.first);
    if (res.first < playerNames[currentTurn])
    {
        currentTurn = (currentTurn + 1) % (int)playerNames.size();
    }
    sort(playerNames.begin(), playerNames.end());

    if (res.second == "petani")
    {
        players[res.first] = new Petani(res.first, gameConfig.getInventoryRow(), gameConfig.getInventoryCol(), gameConfig.getLahanRow(), gameConfig.getLahanCol());
    }
    else
    {
        players[res.first] = new Peternak(res.first, gameConfig.getInventoryRow(), gameConfig.getInventoryCol(), gameConfig.getPeternakanRow(), gameConfig.getPeternakanCol());
    }
}

void GameEngine::load()
{
    /**
     * @todo: lengkapin load
     */
}