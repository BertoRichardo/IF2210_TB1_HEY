#include "../header/Player.hpp"

Player::Player(string username_, int invRow, int invCol)
    : inventory(invRow, invCol)
{
    username = username_;
    gulden = 50;
    weigth = 40;
}

Player::~Player() {}

string Player::getUsername() const
{
    return username;
}

void Player::setUsername(string username_)
{
    username = username_;
}

int Player::getWealthFromInv() const
{
    // inisialisasi
    int pajak = 0;

    // kekayaan dari gulden
    pajak += getGulden();

    // cari kekayaan dari inventory
    for (int i = 0; i < inventory.getRow(); i++)
    {
        for (int j = 0; j < inventory.getCol(); j++)
        {
            if (!inventory.isCellEmpty(i, j))
            {
                pajak += inventory.getItem(i, j)->getPrice();
            }
        }
    }
    return pajak;
}

string Player::getType() const
{
    return "PLAYER";
}

int Player::getWeight() const
{
    return weigth;
}

void Player::setWeight(int weight_)
{
    weigth = weight_;
}

int Player::getGulden() const
{
    return gulden;
}

void Player::setGulden(int gulden_)
{
    gulden = gulden_;
}

void Player::eat()
{
    // Menampilkan Inventory
    cout << "Pilih makanan dari penyimpanan" << endl;
    cout << "[Penyimpanan]: " << endl;
    inventory.printMatrix();

    if (inventory.isFoodEmpty())
    {
        // throw FoodEmptyException
    }

    // Memilih dari inventory
    bool isDone = false;

    string koordinat;
    while (!isDone)
    {
        try
        {
            cout << "Slot: ";
            cin >> koordinat;
            cout << endl;

            Product *makanan = dynamic_cast<Product *>(inventory.getMakanan(koordinat));
            weigth += makanan->getAddedWeight();

            cout << "Dengan lahapnya, kamu memakan hidangan itu" << endl;
            cout << "Alhasil, berat badan kamu naik menjadi " << weigth << endl;

            inventory.removeItem(koordinat);
            makanan->~Product();

            // Makanan sudah dimakan
            isDone = true;
        }

        /**
         * TODO: implement Exception
         */
        catch (const GameException &e)
        {
            e.displayMessage();
        }
    }
}

void Player::beli(Shop &toko)
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

void Player::cekBeli(Shop &toko)
{
    // Minta masukan dari user
    int masukan;
    cout << "Barang yang ingin dibeli :";
    cin >> masukan;
    cout << endl;

    // validasi masukan
    if (masukan < 1 || masukan > toko.getSize())
    {
        // throw inputInvalidException
    }

    // validasi penyimpanan
    int quantity;
    cout << "Kuantitas: ";
    cin >> quantity;
    cout << endl;
    if (quantity == 0 || quantity > inventory.emptySpace())
    {
        // throw inputInvalidException
    }

    // validasi gulden
    if (quantity * toko.getGameObject(masukan - 1)->getPrice() > getGulden())
    {
        /**
         * throw Gulden kurang (?)
         */
    }

    // validasi stock di toko
    if (toko.getStock(masukan - 1) != -1 && quantity > toko.getStock(masukan - 1))
    {
        /**
         * TODO: throw StockInsufficient
         */
    }

    // Berikan IO dan kurangi uang
    setGulden(getGulden() - quantity * toko.getGameObject(masukan - 1)->getPrice());
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
            // batal beli
            for (int i = 0; i < cnt; i++)
            {
                inventory.removeItem(slotS[i]);
            }
            e.displayMessage();
        }
    }
}

void Player::jual(Shop &toko)
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

void Player::cekJual(Shop &toko)
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

                // cek bangunan
                if (dynamic_cast<Building *>(inventory.getItem(slotS[i])) != NULL)
                {
                    // throw Invalid
                }

                // Kurangi stock jika barang yang dibeli finite
                if (dynamic_cast<Plant *>(inventory.getItem(slotS[i])) == NULL && dynamic_cast<Animal *>(inventory.getItem(slotS[i])) == NULL)
                {
                    toko.setStock(inventory.getItem(slotS[i])->getName(), toko.getStock(inventory.getItem(slotS[i])->getName()) - 1);
                }

                // setGulden
                setGulden(getGulden() + inventory.getItem(slotS[i])->getPrice());

                // remove dari inventory
                inventory.removeItem(slotS[i]);
            }

            // delete vectorTemp
            for (auto &obj : vectorTemp)
            {
                delete obj.first;
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

void Player::printInventory()
{
    printHeader("Penyimpanan");
    inventory.printMatrix();
    cout << "Total slot kosong: " << inventory.emptySpace() << endl;
}

void Player::printHeader(string judul)
{
    cout << "   ";
    if (inventory.getCol() * 6 + 1 > 13)
    {
        for (int i = 0; i < (inventory.getCol() * 6 - 12) / 2; i++)
        {
            cout << "=";
        }
        cout << judul;
        for (int i = 0; i < (inventory.getCol() * 6 - 12) / 2; i++)
        {
            cout << "=";
        }
    }
    else
    {
        cout << judul;
    }
    cout << endl;
}