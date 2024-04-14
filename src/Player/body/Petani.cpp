#include "../header/Petani.hpp"

Petani::Petani(string username_,
               int invRow, int invCol,
               int lahanRow, int lahanCol)
    : Player::Player(username_, invRow, invCol), lahan(lahanRow, lahanCol)
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

    return kkp * Util::persenPajak(kkp);
}

bool Petani::isPanenableMatrix()
{
    for (int i = 0; i < lahan.getRow(); i++)
    {
        for (int j = 0; j < lahan.getCol(); j++)
        {
            if (lahan.getItem(i, j)->isReadyToHarvest())
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
        /**
         * @TODO: throw EmptyCell
         */
    }
    if (!lahan.getItem(cell)->isReadyToHarvest())
    {
        /**
         * @TODO: throw NotReadyToHarvest
         */
    }
}

void Petani::panenTanaman()
{
    if (isPanenableMatrix())
    {
        /**
         * @TODO: throw NotPanenable
         */
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
    cout << "Nomor tanaman yang ingin dipanen: ";
    int in;
    cin >> in;
    if (in < 0 || in > (int)temp.size())
    {
        /**
         * @TODO: throw InvalidInput
         */
    }

    // mengambil tanaman
    map<string, int>::iterator item = temp.begin();
    advance(item, in - 1);

    // mengambil jumlah panen
    cout << "Berapa petak yang ingin dipanen: ";
    int quantity;
    cin >> quantity;
    cout << endl;
    // cek error
    if (quantity > item->second)
    {
        /**
         * @TODO: throw NotEnoughPetakPanen
         */
    }
    if (quantity > inventory.emptySpace())
    {
        /**
         * @TODO: throw NotEnoughSpace
         */
    }

    // Mengambil tanaman dari lahan
    int j = 1;
    vector<string> vec;
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
            inventory.addItem(new Product(plant->harvest()));
            lahan.removeItem(cell);
            delete plant;

            j++;
            vec.push_back(cell);
        }
        catch (const GameException &e)
        {
            e.displayMessage();
        }
    }
    cout << vec.size() << " petak tanaman " << item->first << " pada petak";
    for (int k = 0; k < (int)vec.size(); k++)
    {
        cout << vec[k];
        if (k != (int)vec.size() - 1)
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
        /**
         * TODO: Throw MatrixFullException
         */
        return;
    }

    if (inventory.isObjectEmpty<Plant *>())
    {
        /**
         * TODO: Throw MatrixEmptyException
         */
        return;
    }

    // pilih dari inventory
    Plant *plant = NULL;
    string inventoryKoor;

    // print inventory
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
                /**
                 * TODO: NotplantException
                 */
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
            cout << plant->getName() << " berhasil ditanam!" << endl
                 << endl;
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
                lahan.getItem(i, j)->setDuration(lahan.getItem(i, j)->getDuration() + 1);
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