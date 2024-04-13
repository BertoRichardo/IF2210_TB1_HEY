#include "../header/Walikota.hpp"

Walikota::Walikota(string username_) : Player(username_)
{
}

string Walikota::getType() const
{
    return "WALIKOTA";
}

void Walikota::tarikPajak()
{
    /**
     * TODO: traverse through all the player -> at the game context vector
     */
}

void Walikota::buatBangunan(const map<string, BuildingConfig> &buildings)
{
    /**
     * TODO: tampilkan resep
     */

    if (inventory.isMatrixFull())
    {
        // throw MatrixPenuhException;
    }

    bool isDone = false;
    while (!isDone)
    {
        try
        {
            cekRecipe(buildings);
        }
        catch (const GameException &e)
        {
            e.displayMessage();
        }
    }
}

void Walikota::cekRecipe(const map<string, BuildingConfig> &buildings)
{
    string input;
    cout << "Bangunan yang ingin dibangun" << endl;
    cin >> input;

    if (buildings.find(input) == buildings.end())
    {
        // throw
        /**
         * TODO: RecipeNotFoundException
         */
    }

    vector<pair<string, int>> recipe = buildings.at(input).getRecipe();

    map<string, int> inventoryCount = getInventoryCount();
    vector<pair<string, int>> InsufficentMaterial;

    // cek material
    for (auto i = recipe.begin(); i != recipe.end(); i++)
    {
        if (i->second > inventoryCount[i->first])
        {
            InsufficentMaterial.push_back(pair(i->first, i->second - inventoryCount[i->first]));
        }
    }
    // cek gulden
    int harga = buildings.at(input).getPrice();
    int newGulden = getGulden() < harga;
    if (newGulden || InsufficentMaterial.size() != 0)
    {
        cout << "throw insufficient" << endl;
        /**
         * TODO: throw MaterialInsufficientException
         */
    }

    // Set GUlden
    setGulden(newGulden);

    // hilangkan material yang dipakai
    for (auto i = recipe.begin(); i != recipe.end(); i++)
    {
        int x = 0;
        int y = 0;
        int j = i->second;

        while (j != 0)
        {
            if (!inventory.isCellEmpty(y, x))
            {
                if (inventory.getItem(y, x)->getName() == i->first)
                {
                    j--;
                }
                x++;
                if (x > inventory.getCol())
                {
                    x = 0;
                    y++;
                }
            }
        }
    }

    BuildingConfig config = buildings.at(input);
    Building *bangunan = new Building(config.getKodeHuruf(), config.getNama(), config.getPrice(), config.getRecipe());

    bool stored = false;
    while (!stored)
    {
        for (int i = 0; i < inventory.getRow(); i++)
        {
            for (int j = 0; j < inventory.getCol(); j++)
            {
                if (inventory.isCellEmpty(i, j))
                {
                    inventory.addItem(i, j, bangunan);
                }
            }
        }
    }
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
    cout << "Barang yang ingin dibeli :";
    cin >> masukan;
    cout << endl;

    // validasi masukan
    if (masukan <= 0 || masukan > toko.getSize())
    {
        // throw InputInvalidException
    }

    if (dynamic_cast<Building *>(toko.getGameObject(masukan)) != NULL)
    {
        // throw CantBuyBuilding
    }

    // validasi inventory
    int quantity;
    cout << "Kuantitas: ";
    cin >> quantity;
    cout << endl;

    if (quantity == 0 || quantity > inventory.emptySpace())
    {
        // throw inputInvalidException
    }

    // validasi gulden
    if (quantity * toko.getGameObject(masukan)->getPrice() > getGulden())
    {

        /**
         * throw Gulden kurang (?)
         */
    }

    // Validasi stock
    if (toko.getStock(masukan - 1) != -1 && quantity > toko.getStock(masukan - 1))
    {
        /**
         * TODO: throw StockKurang Exception
         */
    }

    // Berikan IO dan kurangi uang
    setGulden(getGulden() - quantity * toko.getGameObject(masukan)->getPrice());
    cout << "Selamat Anda berhasil membeli " << quantity << " " << toko.getGameObject(masukan)->getName() << ".";
    cout << "Uang Anda tersisa " << getGulden();

    // IO pemilihan slot
    cout << "Pilih slot untuk menyimpan barang yang Anda beli!" << endl;
    cout << "[Penyimpanan]:" << endl;
    inventory.printMatrix();

    // Pilih slot
    bool isDone = false;
    while (!isDone)
    {
        GameObject *item = Util::callCCtor(toko.getGameObject(masukan - 1));
        string inSlot;
        cout << "Petak slot: ";
        cin >> inSlot;
        vector<string> slotS = Util::parserSlots(inSlot);
        int cnt = 0;
        try
        {
            // eksekusi
            for (int i = 0; i < (int)slotS.size(); i++)
            {
                inventory.addItem(slotS[i], item);
            }
            isDone = true;
            if (dynamic_cast<Plant *>(item) == NULL && dynamic_cast<Animal *>(item) == NULL)
            {
                toko.setStock(item->getName(), toko.getStock(masukan - 1) - quantity);
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
    cout << "[Penyimpanan]:";
    inventory.printMatrix();
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
        cin >> inSlot;
        vector<string> slotS = Util::parserSlots(inSlot);
        vector<pair<GameObject *, string>> vectorTemp;

        try
        {
            for (int i = 0; i < (int)inSlot.size(); i++)
            {
                vectorTemp.push_back(pair(inventory.getItem(slotS[i]), slotS[i]));

                // Kurangi stock jika barang yang dibeli finite
                if (dynamic_cast<Plant *>(inventory.getItem(slotS[i])) == NULL && dynamic_cast<Animal *>(inventory.getItem(slotS[i])) == NULL)
                {
                    toko.setStock(inventory.getItem(slotS[i])->getName(), toko.getStock(inventory.getItem(slotS[i])->getName()) - 1);
                }

                inventory.removeItem(slotS[i]);
                setGulden(getGulden() + inventory.getItem(slotS[i])->getPrice());
            }
        }
        catch (const GameException &e)
        {
            // Pop vector (saat throw pertama kali ditemukan)
            vectorTemp.pop_back();

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

pair<string, string> Walikota::tambahPemain(set<string> &names)
{
    // Input Jenis pemain
    string name, jenis;
    cout << "Masukkan jenis pemain:";
    cin >> jenis;
    if (jenis != "peternak" && jenis != "petani")
    {
        /**
         * TODO: throw InvalidJenisPlayer
         */
    }

    // nama pemain
    cout << "Masukkan nama pemain:";
    cin >> name;
    cout << endl;
    if (names.find(name) != names.end())
    {
        /**
         * TODO: throw NameIsNotUnique
         */
    }
    cout << "Pemain baru ditambahkan!" << endl;
    cout << "Selamat datang \"" << name << "\" di kota ini!" << endl;
    return {name, jenis};
}
