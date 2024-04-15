#include "../header/Petani.hpp"

Petani::Petani(string username_, int weight_,
               int invRow, int invCol,
               int lahanRow, int lahanCol)
    : Player::Player(username_, weight_, invRow, invCol), lahan(lahanRow, lahanCol)
{
}

Petani::~Petani()
{
    lahan.~MatrixContainer();
}

MatrixContainer<Plant *> Petani::getLahan() const
{
    return lahan;
}

string Petani::getType() const
{
    return "PETANI";
}

int Petani::getPajak() const
{
    // inisialisasi
    int wealth = getWealthFromInv() + getWealthFromLahan() + getGulden();

    // KTKP = 13
    int kkp = wealth - 13;

    int pajak = round((float)(((float)kkp * (float)Util::persenPajak(kkp)) / (float)100));
    return pajak;
}

bool Petani::isPanenableMatrix()
{
    for (int i = 0; i < lahan.getRow(); i++)
    {
        for (int j = 0; j < lahan.getCol(); j++)
        {
            if (!lahan.isCellEmpty(i, j) && lahan.getItem(i, j)->isReadyToHarvest())
            {
                return true;
            }
        }
    }
    return false;
}

void Petani::cekPanen(string cell)
{
    if (lahan.isCellEmpty(cell))
    {
        throw CustomException("Cell/petak kosong");
    }
    if (!lahan.getItem(cell)->isReadyToHarvest())
    {
        throw CustomException("Belum siap dipanen");
    }
}

void Petani::panenTanaman()
{
    if (!isPanenableMatrix())
    {
        throw CustomException("Belum ada tanaman siap dipanen");
    }

    // Cetak matrix
    printLahan();

    map<string, int> temp;

    // mapping sementara dari lahan
    for (int i = 0; i < lahan.getRow(); i++)
    {
        for (int j = 0; j < lahan.getCol(); j++)
        {
            if (!lahan.isCellEmpty(i, j) && lahan.getItem(i, j)->isReadyToHarvest())
            {
                cout << "- " << Util::angkaToHuruf(j) << i + 1 << ": " << lahan.getItem(i, j)->getName() << endl;
                temp[lahan.getItem(i, j)->getKodeHuruf()]++;
            }
        }
    }

    // menampilkan tanaman yang bisa dipanen
    cout << endl
         << "Pilih tanaman siap panen yang kamu miliki" << endl;
    map<string, int>::iterator it = temp.begin();
    int i = 1;
    while (it != temp.end())
    {
        cout << i << ". " << it->first << " (" << it->second << " petak siap dipanen)" << endl;
        ++it;
        i++;
    }
    cout << endl;

    // Memilih tanaman dari map yang sudah dibuat
    int in;

    while (cout << "Nomor tanaman yang ingin dipanen: " && !(cin >> in))
    {
        cin.clear();                                         // clear bad input flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard input
        cout << "Input invalid (bukan integer), mohon masukkan input kembali.\n";
    }

    if (in < 0 || in > (int)temp.size())
    {
        throw InputInvalidException();
    }

    // mengambil tanaman
    map<string, int>::iterator item = temp.begin();
    advance(item, in - 1);

    // mengambil jumlah panen
    int quantity;

    while (cout << "Berapa petak yang ingin dipanen: " && !(cin >> quantity))
    {
        cin.clear();                                         // clear bad input flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard input
        cout << "Input invalid (bukan integer), mohon masukkan input kembali.\n";
    }

    cout << endl;
    // cek error
    if (quantity > item->second)
    {
        throw CustomException("Jumlah petak yang ingin dipanen kebanyakan");
    }
    if (quantity > inventory.emptySpace())
    {
        throw CustomException("Penyimpanan tidak cukup untuk menyimpan hasil panen");
    }

    // Mengambil tanaman dari lahan
    int j = 1;
    vector<string> validCell;
    while (j <= quantity)
    {
        try
        {
            cout << "Petak ke-" << j << ": ";
            string cell;
            cin >> cell;

            // validasi cell masukanl;
            cekPanen(cell);

            Plant *plant = lahan.getItem(cell);
            inventory+(new Product(plant->harvest()));
            lahan.removeItem(cell);
            delete plant;

            j++;
            validCell.push_back(cell);
        }
        catch (const GameException &e)
        {
            e.displayMessage();
        }
    }

    // Beri pesan
    cout << validCell.size() << " petak tanaman " << item->first << " pada petak ";
    for (int k = 0; k < (int)validCell.size(); k++)
    {
        cout << validCell[k];
        if (k != (int)validCell.size() - 1)
        {
            cout << ", ";
        }
    }
    cout << " telah dipanen!\n";
}

void Petani::tanam()
{
    if (lahan.isMatrixFull())
    {
        throw CustomException("Ladang sudah penuh");
    }

    if (inventory.isObjectEmpty<Plant *>())
    {
        throw CustomException("Tidak ada tanaman di penyimpanan");
    }

    // pilih dari inventory
    Plant *plant = NULL;
    string inventoryKoor;

    // print inventory
    cout << "Pilih tanaman dari penyimpanan" << endl
         << endl;
    printInventory();

    while (plant == NULL)
    {
        try
        {
            cout << "Slot: ";
            cin >> inventoryKoor;
            cout << '\n';
            plant = dynamic_cast<Plant *>(inventory.getItem(inventoryKoor));
            if (plant == NULL)
            {
                throw CustomException("Itu bukan tanaman");
            }
            cout << "Kamu memilih: " << plant->getName() << ".\n\n";
            inventory.removeItem(inventoryKoor);
        }
        catch (const GameException &e)
        {
            e.displayMessage();
        }
    }

    // pilih petak lahan
    // cetak lahan
    printLahan();
    bool isDone = false;
    string lahanKoor;

    while (!isDone)
    {
        try
        {
            cout << "Petak tanah: ";
            cin >> lahanKoor;
            cout << '\n';

            lahan.addItem(lahanKoor, plant);
            isDone = true;

            cout << "Cangkul, cangkul, cangkul yang dalam~!" << endl
                 << endl;
            cout << plant->getName() << " berhasil ditanam!" << endl;
        }
        catch (const GameException &e)
        {
            e.displayMessage();
        }
    }
}

void Petani::tambahUmurTanaman()
{
    for (int i = 0; i < lahan.getRow(); i++)
    {
        for (int j = 0; j < lahan.getRow(); j++)
        {
            if (!lahan.isCellEmpty(i, j))
            {
                (*lahan.getItem(i, j))++;
            }
        }
    }
}

void Petani::printLahan()
{
    printHeader("[Lahan]");

    // Cetak matrix
    lahan.printMatrix();
    map<string, string> temp;
    for (int i = 0; i < lahan.getRow(); i++)
    {
        for (int j = 0; j < lahan.getCol(); j++)
        {
            if (!lahan.isCellEmpty(i, j))
            {
                temp[lahan.getItem(i, j)->getKodeHuruf()] = lahan.getItem(i, j)->getName();
            }
        }
    }
    map<string, string>::iterator item = temp.begin();
    for (int i = 0; i < (int)temp.size(); i++)
    {
        cout << item->first << ": " << item->second << endl;
        ++item;
    }
}

int Petani::getWealthFromLahan() const
{
    int wealth = 0;
    for (int i = 0; i < lahan.getRow(); i++)
    {
        for (int j = 0; j < lahan.getCol(); j++)
        {
            if (!lahan.isCellEmpty(i, j))
            {
                wealth += lahan.getItem(i, j)->getPrice();
            }
        }
    }
    return wealth;
}

vector<pair<string, pair<string, string>>> Petani::getLahanPlant()
{
    vector<pair<string, pair<string, string>>> res;
    for (int i = 0; i < lahan.getRow(); i++)
    {
        for (int j = 0; j < lahan.getCol(); j++)
        {
            if (!lahan.isCellEmpty(i, j))
            {
                Plant *plant = lahan.getItem(i, j);
                res.push_back({Util::rowColToStr(i, j), {plant->getName(), to_string(plant->getDuration())}});
            }
        }
    }
    return res;
}