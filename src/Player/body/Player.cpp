#include "../header/Player.hpp"

Player::Player(string username_, int weight_, int invRow, int invCol)
    : inventory(invRow, invCol)
{
    username = username_;
    gulden = 50;
    weigth = weight_;
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
    int wealth = 0;

    // cari kekayaan dari inventory
    for (int i = 0; i < inventory.getRow(); i++)
    {
        for (int j = 0; j < inventory.getCol(); j++)
        {
            if (!inventory.isCellEmpty(i, j))
            {
                wealth += inventory.getItem(i, j)->getPrice();
            }
        }
    }
    return wealth;
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
    printInventory();

    if (inventory.isFoodEmpty())
    {
        throw CustomException("Tidak ada makanan di inventory.");
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
            cin.ignore();
            cout << endl;

            Product *makanan = dynamic_cast<Product *>(inventory.getMakanan(koordinat));
            weigth += makanan->getAddedWeight();

            cout << "Dengan lahapnya, kamu memakan hidangan itu" << endl;
            cout << "Alhasil, berat badan kamu naik menjadi " << weigth << endl;

            inventory.removeItem(koordinat);
            delete makanan;

            // Makanan sudah dimakan
            isDone = true;
        }

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
    cekBeli(toko);
}

void Player::cekBeli(Shop &toko)
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
    if (masukan < 1 || masukan > toko.getSize())
    {
        throw CustomException("Input tidak valid.");
    }

    // validasi penyimpanan
    int quantity;

    while (cout << "Kuantitas : " && !(cin >> quantity))
    {
        cin.clear();                                         // clear bad input flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard input
        cout << "Input invalid (bukan integer), mohon masukkan input kembali.\n";
    }
    cin.ignore();

    cout << endl;

    if (quantity <= 0 || quantity > inventory.emptySpace())
    {
        throw CustomException("Kuantitas tidak valid atau melebihi kapasitas.");
    }

    // validasi stock di toko
    if (toko.getStock(masukan - 1) != -1 && quantity > toko.getStock(masukan - 1))
    {
        throw CustomException("Stok barang yang Anda pilih tidak cukup.");
    }

    // validasi gulden
    if (quantity * toko.getGameObject(masukan - 1)->getPrice() > getGulden())
    {
        throw CustomException("Gulden Anda tidak cukup.");
    }

    // Berikan IO dan kurangi uang
    setGulden(getGulden() - quantity * toko.getGameObject(masukan - 1)->getPrice());
    cout << "Selamat Anda berhasil membeli " << quantity << " " << toko.getGameObject(masukan - 1)->getName() << ".\n";
    cout << "Uang Anda tersisa " << getGulden() << endl;

    // IO pemilihan slot
    cout << "Pilih slot untuk menyimpan barang yang Anda beli!" << endl;
    printInventory();

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
            // validasi jumlah slot
            if ((int)slotS.size() != quantity)
            {
                throw CustomException("Jumlah Slot tidak valid");
            }

            // eksekusi
            for (int i = 0; i < (int)slotS.size(); i++)
            {
                GameObject *item = Util::callCCtor(toko.getGameObject(masukan - 1));
                inventory.addItem(slotS[i], item);
                cnt++;
            }

            // kurangi stock jika barang finite
            if (dynamic_cast<Plant *>(toko.getGameObject(masukan - 1)) == NULL && dynamic_cast<Animal *>(toko.getGameObject(masukan - 1)) == NULL)
            {
                toko.setStock(toko.getGameObject(masukan - 1)->getName(), toko.getStock(masukan - 1) - quantity);
            }
            isDone = true;
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
    if (inventory.isMatrixEmpty())
    {
        throw CustomException("Penyimpanan kosong");
    }
    cout << "Berikut merupakan penyimpanan Anda" << endl
         << endl;
    printInventory();
    cekJual(toko);
}

void Player::cekJual(Shop &toko)
{
    bool isDone = false;
    while (!isDone)
    {
        cout << "Silahkan pilih petak yang ingin Anda jual!\n";
        cout << "Petak: ";

        string inSlot;
        getline(cin, inSlot);
        vector<string> slotS = Util::parserSlots(inSlot);
        vector<pair<GameObject *, string>> vectorTemp;
        try
        {
            int uangTambah = 0;
            for (int i = 0; i < (int)slotS.size(); i++)
            {
                // cek bangunan
                if (dynamic_cast<Building *>(inventory.getItem(slotS[i])) != NULL)
                {
                    throw CustomException("Tidak bisa menjual bangunan");
                }

                // tambah stock jika barang yang dibeli finite
                toko+(*inventory.getItem(slotS[i]));

                // setGulden
                uangTambah += inventory.getItem(slotS[i])->getPrice();
                setGulden(getGulden() + inventory.getItem(slotS[i])->getPrice());

                vectorTemp.push_back({inventory.getItem(slotS[i]), slotS[i]});

                // remove dari inventory
                inventory.removeItem(slotS[i]);
            }
            // delete temp
            for (auto &obj : vectorTemp)
            {
                delete obj.first;
            }
            isDone = true;
            cout << "Barang Anda berhasil dijual! Uang Anda bertambah " << uangTambah << " gulden!" << endl;
        }
        catch (const GameException &e)
        {
            // Masukkan kembali barang dan uangnya ke inventory
            // dan keluarkan dari vector temp serta shop
            while (!vectorTemp.empty())
            {
                inventory.addItem(vectorTemp[vectorTemp.size() - 1].second, (vectorTemp[vectorTemp.size() - 1].first));
                toko - *vectorTemp[vectorTemp.size() - 1].first;

                setGulden(getGulden() - vectorTemp[vectorTemp.size() - 1].first->getPrice());
                vectorTemp.pop_back();
            }
            e.displayMessage();
        }
    }
}

void Player::printInventory()
{
    printHeader("[Penyimpanan]");
    inventory.printMatrix();
    cout << "\nTotal slot kosong: " << inventory.emptySpace() << "\n";
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
    cout << "\n\n";
}

bool Player::isPlayerWin(int guldenToWin, int weigthToWin)
{
    return gulden >= guldenToWin && weigth >= weigthToWin;
}

vector<string> Player::getInventoryItem()
{
    vector<string> res;
    for (int i = 0; i < inventory.getRow(); i++)
    {
        for (int j = 0; j < inventory.getCol(); j++)
        {
            if (!inventory.isCellEmpty(i, j))
            {
                res.push_back(inventory.getItem(i, j)->getName());
            }
        }
    }
    return res;
}

void Player::addItemToInventory(GameObject *obj)
{
    inventory.addItem(obj);
}