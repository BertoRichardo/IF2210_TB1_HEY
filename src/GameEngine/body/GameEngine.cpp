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
    throw CommandInvalidException();
}

int GameEngine::readCommand()
{
    cout << ">> ";
    string input;
    getline(cin, input);
    cout << endl;
    return checkCommand(input);
}

void GameEngine::setup()
{
    Util::displayStartingScreen();

    bool isValid = false;

    cout << "Selamat Datang di Permainan Kelola Kerajaan"
         << "\n\n";

    while (!isValid)
    {
        try
        {
            string input;
            cout << "Apakah Anda ingin memuat state? (y/n): ";
            cin >> input;
            cin.ignore();
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
        catch(const std::exception& e)
        {
            std::cerr << e.what() << "\n\n";
        }
        
    }

    cout << "Giliran saat ini adalah pemain dengan username " << playerNames[currentTurn] << " dan role " << players[playerNames[currentTurn]]->getType() << "\n\n";
}

void GameEngine::defaultSetup()
{
    // read players username
    // create walikota
    string walikota = Util::readUsername(playerNames, "walikota");
    playerNames.push_back(walikota);
    players[walikota] = new Walikota(walikota, 40, gameConfig.getInventoryRow(), gameConfig.getInventoryCol());

    // create peternak
    string peternak = Util::readUsername(playerNames, "peternak1");
    playerNames.push_back(peternak);
    players[peternak] = new Peternak(peternak, 40, gameConfig.getInventoryRow(), gameConfig.getInventoryCol(), gameConfig.getPeternakanRow(), gameConfig.getPeternakanCol());

    // create petani
    string petani = Util::readUsername(playerNames, "petani1");
    playerNames.push_back(petani);
    players[petani] = new Petani(petani, 40, gameConfig.getInventoryRow(), gameConfig.getInventoryCol(), gameConfig.getLahanRow(), gameConfig.getLahanCol());

    // sort playerNames
    sort(playerNames.begin(), playerNames.end());
    currentTurn = 0;
}
void GameEngine::stateSetup()
{
    string file;
    cout << "Masukkan lokasi berkas state : ";
    cin >> file;
    cin.ignore();

    vector<vector<string>> data = FileController::readFile(file);

    load(data);

    sort(playerNames.begin(), playerNames.end());
    currentTurn = 0;
}

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
                stillRun = check_win();
                break;
            case 1:
                cetak_penyimpanan();
                stillRun = check_win();
                break;
            case 2:
                pungut_pajak();
                stillRun = check_win();
                break;
            case 3:
                cetak_ladang();
                stillRun = check_win();
                break;
            case 4:
                cetak_peternakan();
                stillRun = check_win();
                break;
            case 5:
                tanam();
                stillRun = check_win();
                break;
            case 6:
                ternak();
                stillRun = check_win();
                break;
            case 7:
                bangun();
                stillRun = check_win();
                break;
            case 8:
                makan();
                stillRun = check_win();
                break;
            case 9:
                kasih_makan();
                stillRun = check_win();
                break;
            case 10:
                beli();
                stillRun = check_win();
                break;
            case 11:
                jual();
                stillRun = check_win();
                break;
            case 12:
                panen();
                stillRun = check_win();
                break;
            case 13:
                save();
                stillRun = check_win();
                break;
            case 14:
                tambah_pemain();
                stillRun = check_win();
                break;
            case 15:
                stillRun = false;
                cout << "Sampai Jumpa Lagi di Permainan Kelola Kerajaan (o^ ^o)/";
                break;
            }
            cout << "\n";
        }
        catch (const GameException &e)
        {
            e.displayMessage();
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}

void GameEngine::next()
{
    for (string player : playerNames)
    {
        if (players[player]->getType() == "PETANI")
        {
            dynamic_cast<Petani *>(players[player])->tambahUmurTanaman();
        }
    }

    currentTurn = (currentTurn + 1) % (int)playerNames.size();
    cout << "Giliran saat ini adalah pemain dengan username " << playerNames[currentTurn] << " dan role " << players[playerNames[currentTurn]]->getType() << "\n";
}

void GameEngine::cetak_penyimpanan()
{
    players[playerNames[currentTurn]]->printInventory();
}

void GameEngine::pungut_pajak()
{
    if (players[playerNames[currentTurn]]->getType() != "WALIKOTA")
    {
        throw CommandInvalidException();
    }
    vector<Player *> vecPlayer = getPlayerVector();
    dynamic_cast<Walikota *>(players[playerNames[currentTurn]])->tarikPajak(vecPlayer);
}

void GameEngine::cetak_ladang()
{
    if (players[playerNames[currentTurn]]->getType() != "PETANI")
    {
        throw CommandInvalidException();
    }
    dynamic_cast<Petani *>(players[playerNames[currentTurn]])->printLahan();
}

void GameEngine::cetak_peternakan()
{
    if (players[playerNames[currentTurn]]->getType() != "PETERNAK")
    {
        throw CommandInvalidException();
    }
    dynamic_cast<Peternak *>(players[playerNames[currentTurn]])->printPeternakan();
}

void GameEngine::tanam()
{
    if (players[playerNames[currentTurn]]->getType() != "PETANI")
    {
        throw CommandInvalidException();
    }
    dynamic_cast<Petani *>(players[playerNames[currentTurn]])->tanam();
}

void GameEngine::ternak()
{
    if (players[playerNames[currentTurn]]->getType() != "PETERNAK")
    {
        throw CommandInvalidException();
    }
    dynamic_cast<Peternak *>(players[playerNames[currentTurn]])->letakTernak();
}

void GameEngine::bangun()
{
    if (players[playerNames[currentTurn]]->getType() != "WALIKOTA")
    {
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
        throw CommandInvalidException();
    }
}

void GameEngine::save()
{
    string file;
    cout << "Masukkan lokasi berkas state : ";
    cin >> file;
    cin.ignore();

    // simpan state saat ini
    vector<vector<string>> content;

    // simpan banyak player
    content.push_back(vector<string>{to_string((int)playerNames.size())});

    // simpan state tiap player
    for (string player : playerNames)
    {
        if (players[player]->getType() == "PETANI")
        {
            content.push_back(vector<string>{player, "Petani", to_string(players[player]->getWeight()), to_string(players[player]->getGulden())});

            // get inventory
            vector<string> invs = players[player]->getInventoryItem();
            content.push_back(vector<string>{to_string((int)invs.size())});

            for (string inv : invs)
                content.push_back(vector<string>{inv});

            // get lahan
            vector<pair<string, pair<string, string>>> lahan = dynamic_cast<Petani *>(players[player])->getLahanPlant();
            content.push_back(vector<string>{to_string((int)lahan.size())});

            for (auto plant : lahan)
            {
                content.push_back(vector<string>{plant.first, plant.second.first, plant.second.second});
            }
        }
        else if (players[player]->getType() == "PETERNAK")
        {
            content.push_back(vector<string>{player, "Peternak", to_string(players[player]->getWeight()), to_string(players[player]->getGulden())});
            // get inventory
            vector<string> invs = players[player]->getInventoryItem();
            content.push_back(vector<string>{to_string((int)invs.size())});

            for (string inv : invs)
                content.push_back(vector<string>{inv});

            // get peternakan
            vector<pair<string, pair<string, string>>> peternakan = dynamic_cast<Peternak *>(players[player])->getPeternakanAnimal();
            content.push_back(vector<string>{to_string((int)peternakan.size())});

            for (auto animal : peternakan)
            {
                content.push_back(vector<string>{animal.first, animal.second.first, animal.second.second});
            }
        }
        else
        {
            content.push_back(vector<string>{player, "Walikota", to_string(players[player]->getWeight()), to_string(players[player]->getGulden())});
            // get inventory
            vector<string> invs = players[player]->getInventoryItem();
            content.push_back(vector<string>{to_string((int)invs.size())});

            for (string inv : invs)
                content.push_back(vector<string>{inv});
        }
    }

    // simpan state toko
    vector<pair<string, string>> toko = shop.getGoodsItem();
    content.push_back(vector<string>{to_string(toko.size())});
    for (auto barang : toko)
    {
        content.push_back(vector<string>{barang.first, barang.second});
    }

    FileController::write(content, file);
}

void GameEngine::tambah_pemain()
{
    if (players[playerNames[currentTurn]]->getType() != "WALIKOTA")
    {
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
        players[res.first] = new Petani(res.first, 0, gameConfig.getInventoryRow(), gameConfig.getInventoryCol(), gameConfig.getLahanRow(), gameConfig.getLahanCol());
    }
    else
    {
        players[res.first] = new Peternak(res.first, 0, gameConfig.getInventoryRow(), gameConfig.getInventoryCol(), gameConfig.getPeternakanRow(), gameConfig.getPeternakanCol());
    }
}

void GameEngine::load(vector<vector<string>> data)
{
    int index = 0;
    int numPlayer = stoi(data.at(index).at(index));
    index++;

    // input player data
    while (numPlayer--)
    {
        // assign username, tipe, weight, and gulden
        string username = data.at(index).at(0);
        string tipe = data.at(index).at(1);
        int weight = stoi(data.at(index).at(2));
        int gulden = stoi(data.at(index).at(3));

        index++;

        playerNames.push_back(username);

        if (tipe == "Petani")
        {
            players[username] = new Petani(username, weight, gameConfig.getInventoryRow(), gameConfig.getInventoryCol(), gameConfig.getLahanRow(), gameConfig.getLahanCol());
        }
        else if (tipe == "Peternak")
        {
            players[username] = new Peternak(username, weight, gameConfig.getInventoryRow(), gameConfig.getInventoryCol(), gameConfig.getPeternakanRow(), gameConfig.getPeternakanCol());
        }
        else
        {
            players[username] = new Walikota(username, weight, gameConfig.getInventoryRow(), gameConfig.getInventoryCol());
        }
        
        players[username]->setGulden(gulden);
        // get inventory data
        int numOfInventoryItem = stoi(data.at(index).at(0));
        index++;

        map<string, ProductConfig> products = gameConfig.getProducts();
        map<string, PlantConfig> plants = gameConfig.getPlants();
        map<string, AnimalConfig> animals = gameConfig.getAnimals();
        map<string, BuildingConfig> buildings = gameConfig.getBuildings();
        map<string, vector<Product>> productMap;

        for (auto product : products)
        {
            Product temp(product.second.getKodeHuruf(), product.second.getNama(), product.second.getPrice(), product.second.getType(), product.second.getOrigin(), product.second.getAddedWeight());
            productMap[product.second.getOrigin()].push_back(temp);
        }

        for (int i = 0; i < numOfInventoryItem; i++)
        {
            string itemName = data.at(index).at(0);
            index++;

            if (plants.find(itemName) != plants.end())
            {
                players[username]->addItemToInventory(new Plant(plants[itemName].getKodeHuruf(), plants[itemName].getNama(), plants[itemName].getPrice(), plants[itemName].getType(), plants[itemName].getDurationToHarvest(), 0, productMap[itemName].front()));
                continue;
            }
            if (animals.find(itemName) != animals.end())
            {
                if (animals[itemName].getType() == "HERBIVORE")
                    players[username]->addItemToInventory(new Herbivore(animals[itemName].getKodeHuruf(), animals[itemName].getNama(), animals[itemName].getPrice(), animals[itemName].getType(), animals[itemName].getWeightToHarvest(), 0, productMap[itemName]));
                else if (animals[itemName].getType() == "CARNIVORE")
                    players[username]->addItemToInventory(new Carnivore(animals[itemName].getKodeHuruf(), animals[itemName].getNama(), animals[itemName].getPrice(), animals[itemName].getType(), animals[itemName].getWeightToHarvest(), 0, productMap[itemName]));
                else
                    players[username]->addItemToInventory(new Omnivore(animals[itemName].getKodeHuruf(), animals[itemName].getNama(), animals[itemName].getPrice(), animals[itemName].getType(), animals[itemName].getWeightToHarvest(), 0, productMap[itemName]));
                continue;
            }
            if (products.find(itemName) != products.end())
            {
                players[username]->addItemToInventory(new Product(products[itemName].getKodeHuruf(), products[itemName].getNama(), products[itemName].getPrice(), products[itemName].getType(), products[itemName].getOrigin(), products[itemName].getAddedWeight()));
                continue;
            }
            if (buildings.find(itemName) != buildings.end())
            {
                players[username]->addItemToInventory(new Building(buildings[itemName].getKodeHuruf(), buildings[itemName].getNama(), buildings[itemName].getPrice(), buildings[itemName].getRecipe()));
                continue;
            }
        }

        // if player is petani, check ladang
        if (tipe == "Petani")
        {
            int numOfPlants = stoi(data.at(index).at(0));
            index++;

            for (int i = 0; i < numOfPlants; i++)
            {
                string coordinate = data.at(index).at(0);
                string plantName = data.at(index).at(1);
                int umur = stoi(data.at(index).at(2));
                index++;

                dynamic_cast<Petani *>(players[username])->addPlantToLahan(new Plant(plants[plantName].getKodeHuruf(), plantName, plants[plantName].getPrice(), plants[plantName].getType(), plants[plantName].getDurationToHarvest(), umur, productMap[plantName].front()), coordinate);
            }
        }

        // if player is peternak, check peternakan
        if (tipe == "Peternak")
        {
            int numOfAnimals = stoi(data.at(index).at(0));
            index++;

            for (int i = 0; i < numOfAnimals; i++)
            {
                string coordinate = data.at(index).at(0);
                string animalName = data.at(index).at(1);
                int w = stoi(data.at(index).at(2));
                index++;

                if (animals[animalName].getType() == "HERBIVORE")
                {
                    dynamic_cast<Peternak *>(players[username])->addAnimalToPeternakan(new Herbivore(animals[animalName].getKodeHuruf(), animalName, animals[animalName].getPrice(), animals[animalName].getType(), animals[animalName].getWeightToHarvest(), w, productMap[animalName]), coordinate);
                }
                else if (animals[animalName].getType() == "CARNIVORE")
                {
                    dynamic_cast<Peternak *>(players[username])->addAnimalToPeternakan(new Carnivore(animals[animalName].getKodeHuruf(), animalName, animals[animalName].getPrice(), animals[animalName].getType(), animals[animalName].getWeightToHarvest(), w, productMap[animalName]), coordinate);
                }
                else
                {
                    dynamic_cast<Peternak *>(players[username])->addAnimalToPeternakan(new Omnivore(animals[animalName].getKodeHuruf(), animalName, animals[animalName].getPrice(), animals[animalName].getType(), animals[animalName].getWeightToHarvest(), w, productMap[animalName]), coordinate);
                }
            }
        }
    }

    // input shop data
    int numOfShopItem = stoi(data.at(index).at(0));
    index++;

    for (int i = 0; i < numOfShopItem; i++)
    {
        string name = data.at(index).at(0);
        int quantity = stoi(data.at(index).at(1));
        index++;

        shop.setStock(name, quantity);
    }
}

bool GameEngine::check_win()
{
    if (players[playerNames[currentTurn]]->isPlayerWin(gameConfig.getGuldenWin(), gameConfig.getWeightWin()))
    {
        cout << "Selamat kepada pemain dengan username " << playerNames[currentTurn] << " dan role " << players[playerNames[currentTurn]]->getType() << "\n";
        return false;
    }
    return true;
}