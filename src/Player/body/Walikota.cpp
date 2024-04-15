#include "../header/Walikota.hpp"

Walikota::Walikota(string username_, int weight_,
                   int invRow,
                   int invCol)
    : Player(username_, weight_, invRow, invCol)
{
}

string Walikota::getType() const
{
    return "WALIKOTA";
}

void Walikota::buatBangunan(const map<string, BuildingConfig> &buildings)
{
    map<string, int> groupedItem = inventory.getGroupedItem();

    vector<pair<vector<pair<string, int>>, int>> listOfRecipes;
    for (auto building : buildings)
    {
        listOfRecipes.push_back(make_pair(building.second.getRecipe(), building.second.getPrice()));
    }

    int num = 1;
    cout << "Resep bangunan yang ada adalah sebagai berikut: " << endl;
    for (auto building : buildings)
    {
        cout << "   " << num++ << ". " << building.first << " (" << building.second.getPrice() << " gulden, ";

        // print recipe
        for (int i = 0; i < (int)building.second.getRecipe().size(); i++)
        {
            cout << building.second.getRecipe()[i].first << " " << building.second.getRecipe()[i].second;
            if (i != (int)building.second.getRecipe().size() - 1)
            {
                cout << ", ";
            }
        }
        cout << ")\n";
    }

    if (!isBuildAvailable(groupedItem, listOfRecipes))
    {
        throw CustomException("Anda tidak bisa membangun bangunan.");
    }

    bool isDone = false;
    while (!isDone)
    {
        try
        {
            cekRecipe(buildings, groupedItem);
            isDone = true;
        }
        catch (const GameException &e)
        {
            e.displayMessage();
        }
    }
}

void Walikota::cekRecipe(const map<string, BuildingConfig> &buildings, map<string, int> &materials)
{

    string input;
    cout << endl
         << "Bangunan yang ingin dibangun: ";
    cin >> input;
    cin.ignore();

    if (buildings.find(input) == buildings.end())
    {
        throw CustomException("Bangunan yang ingin Anda bangun tidak tersedia.");
    }

    vector<pair<string, int>> recipe = buildings.at(input).getRecipe();

    vector<pair<string, int>> insufficientMaterial = getInsufficientMaterial(materials, make_pair(recipe, buildings.at(input).getPrice()));

    // cek gulden and material
    int harga = buildings.at(input).getPrice();

    if (getGulden() < harga || insufficientMaterial.size() != 0)
    {
        // cout << "throw insufficient" << endl;
        if (getGulden() < harga)
        {
            throw ResourceInsufficientException(harga - getGulden(), insufficientMaterial);
        }
        else
        {
            throw ResourceInsufficientException(0, insufficientMaterial);
        }
    }

    // Set GUlden
    int newGulden = getGulden() - harga;
    setGulden(newGulden);

    // hilangkan material yang dipakai
    // int cnt = 0;

    for (auto &ingredient : recipe)
    {
        int materialNeeded = ingredient.second;
        for (int row = 0; row < inventory.getRow(); row++)
        {
            for (int col = 0; col < inventory.getCol(); col++)
            {
                if (!inventory.isCellEmpty(row, col) && inventory.getItem(row, col)->getKodeHuruf() == ingredient.first)
                {
                    delete inventory.getItem(row, col);
                    inventory.removeItem(row, col);
                    materialNeeded--;
                    if (materialNeeded == 0)
                    {
                        break;
                    }
                }
            }
            if (materialNeeded == 0)
            {
                break;
            }
        }
    }

    BuildingConfig config = buildings.at(input);
    Building *bangunan = new Building(config.getKodeHuruf(), config.getNama(), config.getPrice(), config.getRecipe());

    inventory.addItem(bangunan);
    cout << input << " berhasil dibangun dan telah menjadi hak milik walikota!" << endl;
}

void Walikota::beli(Shop &toko)
{
    toko.printToko();

    cout << endl
         << "Uang Anda : " << gulden << endl
         << "Slot penyimpanan tersedia : " << inventory.emptySpace() << endl;

    cout << "Barang yang ingin dibeli: ";

    try
    {
        cekBeli(toko);
    }
    catch (const GameException &e)
    {
        e.displayMessage();
    }
}

void Walikota::cekBeli(Shop &toko)
{
    // Minta masukan dari user
    int masukan;
    while (cout << "Barang yang ingin dibeli : " && !(cin >> masukan))
    {
        cin.clear();                                         // clear bad input flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard input
        cout << "Input invalid (bukan integer), mohon masukkan input kembali.\n";
    }
    cin.ignore();
    cout << endl;

    // validasi masukan
    if (masukan <= 0 || masukan > toko.getSize())
    {
        throw InputInvalidException();
    }

    if (dynamic_cast<Building *>(toko.getGameObject(masukan)) != NULL)
    {
        throw CustomException("Walikota tidak bisa beli bangunan");
    }

    // validasi inventory
    int quantity;
    while (cout << "Kuantitas : " && !(cin >> quantity))
    {
        cin.clear();                                         // clear bad input flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard input
        cout << "Input invalid (bukan integer), mohon masukkan input kembali.\n";
    }
    cin.ignore();
    cout << endl;

    if (quantity == 0 || quantity > inventory.emptySpace())
    {
        throw InputInvalidException();
    }

    // validasi gulden
    if (quantity * toko.getGameObject(masukan)->getPrice() > getGulden())
    {
        throw CustomException("Gulden Anda kurang!");
    }

    // Validasi stock
    if (toko.getStock(masukan - 1) != -1 && quantity > toko.getStock(masukan - 1))
    {
        throw CustomException("Stock tidak mencukup");
    }

    // Berikan IO dan kurangi uang
    setGulden(getGulden() - quantity * toko.getGameObject(masukan - 1)->getPrice());
    cout << "Selamat Anda berhasil membeli " << quantity << " " << toko.getGameObject(masukan - 1)->getName() << ".";
    cout << "Uang Anda tersisa " << getGulden();

    // IO pemilihan slot
    cout << "Pilih slot untuk menyimpan barang yang Anda beli!" << endl;
    cout << "[Penyimpanan]:" << endl;
    inventory.printMatrix();

    // Pilih slot
    bool isDone = false;
    while (!isDone)
    {
        string inSlot;
        cout << "Petak slot: ";
        getline(cin, inSlot);
        vector<string> slotS = Util::parserSlots(inSlot);
        int cnt = 0;
        try
        {
            // eksekusi
            for (int i = 0; i < (int)slotS.size(); i++)
            {
                GameObject *item = Util::callCCtor(toko.getGameObject(masukan - 1));
                inventory.addItem(slotS[i], item);
            }
            isDone = true;
            if (dynamic_cast<Plant *>(toko.getGameObject(masukan - 1)) == NULL && dynamic_cast<Animal *>(toko.getGameObject(masukan - 1)) == NULL)
            {
                toko.setStock(toko.getGameObject(masukan - 1)->getName(), toko.getStock(masukan - 1) - quantity);
            }
        }
        catch (const GameException &e)
        {
            for (int i = 0; i < cnt; i++)
            {
                inventory.removeItem(slotS[i]);
            }
            e.displayMessage();
        }
    }
}

void Walikota::jual(Shop &toko)
{
    cout << "Berikut merupakan penyimnpanan Anda" << endl;
    printInventory();
    try
    {
        cekJual(toko);
    }
    catch (const GameException &e)
    {
        e.displayMessage();
    }
}

void Walikota::cekJual(Shop &toko)
{
    bool isDone = false;
    while (!isDone)
    {
        cout << "Silahkan pilih petak yang ingin Anda jual!" << endl;
        cout << "Petak: ";
        string inSlot;
        getline(cin, inSlot);
        vector<string> slotS = Util::parserSlots(inSlot);
        vector<pair<GameObject *, string>> vectorTemp;

        try
        {
            for (int i = 0; i < (int)slotS.size(); i++)
            {
                // Kurangi stock jika barang yang dibeli finite
                if (dynamic_cast<Plant *>(inventory.getItem(slotS[i])) == NULL && dynamic_cast<Animal *>(inventory.getItem(slotS[i])) == NULL)
                {
                    toko.setStock(inventory.getItem(slotS[i])->getName(), toko.getStock(inventory.getItem(slotS[i])->getName()) + 1);
                }
                
                // setGulden
                setGulden(getGulden() + inventory.getItem(slotS[i])->getPrice());

                vectorTemp.push_back(make_pair(inventory.getItem(slotS[i]), slotS[i]));

                // remove dari inventory
                inventory.removeItem(slotS[i]);
            }
            // delete vectorTemp
            for (auto &obj : vectorTemp)
            {
                delete obj.first;
            }
            isDone = true;
        }
        catch (const GameException &e)
        {
            // Pop vector (saat throw pertama kali ditemukan)

            // Masukkan kembali barang dan uangnya ke inventory
            // dan keluarkan dari vector temp serta shop
            while (!vectorTemp.empty())
            {
                inventory.addItem(vectorTemp[vectorTemp.size() - 1].second, (vectorTemp[vectorTemp.size() - 1].first));
                if (dynamic_cast<Plant *>(vectorTemp[vectorTemp.size() - 1].first) == NULL && dynamic_cast<Animal *>(vectorTemp[vectorTemp.size() - 1].first) == NULL)
                {
                    toko.setStock(vectorTemp[vectorTemp.size() - 1].first->getName(), toko.getStock(vectorTemp[vectorTemp.size() - 1].first->getName()) + 1);
                }
                setGulden(getGulden() - vectorTemp[vectorTemp.size() - 1].first->getPrice());
                vectorTemp.pop_back();
            }
        }
    }
}

pair<string, string> Walikota::tambahPemain(vector<string> &names)
{
    if (getGulden() < 50)
    {
        throw CustomException("Gulden Anda tidak cukup");
    }

    // Input Jenis pemain
    string name, jenis;
    cout << "Masukkan jenis pemain:";
    cin >> jenis;
    cin.ignore();
    if (jenis != "peternak" && jenis != "petani")
    {
        throw CustomException("Jenis player salah");
    }

    // nama pemain
    cout << "Masukkan nama pemain:";
    cin >> name;
    cin.ignore();
    cout << endl;
    if (binary_search(names.begin(), names.end(), name))
    {
        throw InputInvalidException();
    }

    // set Gulden walikota
    setGulden(getGulden() - 50);

    cout << "Pemain baru ditambahkan!" << endl;
    cout << "Selamat datang \"" << name << "\" di kota ini!" << endl;
    return {name, jenis};
}

void Walikota::tarikPajak(vector<Player *> &listOfPlayers)
{
    vector<pair<int, pair<string, string>>> wajibPajak;

    int sumPajak = 0;
    for (auto &player : listOfPlayers)
    {
        if (player->getType() != "WALIKOTA")
        {
            int pajak = player->getPajak();
            int currGulden = player->getGulden();
            int pajakActual;
            // Player dapat membayar full
            if (pajak < currGulden)
            {
                pajakActual = pajak;
            }

            // Player tidak dapat membayar full
            else
            {
                pajakActual = currGulden;
            }
            player->setGulden(currGulden - pajakActual);
            wajibPajak.push_back(make_pair(pajakActual, make_pair(player->getUsername(), player->getType())));
        }
    }
    // sort data wajibPajak
    sort(wajibPajak.begin(), wajibPajak.end(), Util::customComparator);

    // Tampilkan data
    int i = 0;
    for (auto &data : wajibPajak)
    {
        cout << i + 1 << ". " << data.second.first << " - " << data.second.second << ": " << data.first << " gulden" << endl;
        i++;
    }
    cout << endl;

    // setGulden Walikota
    setGulden(getGulden() + sumPajak);

    cout << "Negara mendapatkan pemasukan sebesar " << sumPajak << " gulden." << endl;
    cout << "Gunakan dengan baik dan jangan dikorupsi ya!"
         << "\n\n";
}

int Walikota::getPajak() const
{
    return 0;
}

vector<pair<string, int>> Walikota::getInsufficientMaterial(
    map<string, int> &materials,
    const pair<vector<pair<string, int>>, int> &recipe)
{
    vector<pair<string, int>> insufficentMaterial;
    for (auto const &i : recipe.first)
    {
        if (i.second > materials[i.first])
        {
            insufficentMaterial.push_back(make_pair(i.first, i.second - materials[i.first]));
        }
    }

    return insufficentMaterial;
}

bool Walikota::isBuildAvailable(
    map<string, int> &materials,
    const vector<pair<vector<pair<string, int>>, int>> &listOfRecipes)
{
    for (auto const &recipe : listOfRecipes)
    {
        if ((int)getInsufficientMaterial(materials, recipe).size() == 0 &&
            gulden >= recipe.second)
        {
            return true;
        }
    }
    return false;
}