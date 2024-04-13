#include "../header/Peternak.hpp"

Peternak::Peternak(string username_,
                   int invRow, int invCol,
                   int peternakanRow, int peternakanCol)
    : Player::Player(username_, invRow, invCol), peternakan(peternakanRow, peternakanCol)
{
}

Peternak::~Peternak()
{
    peternakan.~MatrixContainer();
}

string Peternak::getType() const
{
    return "PETERNAK";
}

int Peternak::getPajak() const
{
    // inisialisasi
    int wealth = getWealthFromInv();

    // cari kekayaan dari peternakan
    for (int i = 0; i < peternakan.getRow(); i++)
    {
        for (int j = 0; j < peternakan.getCol(); j++)
        {
            if (!peternakan.isCellEmpty(i, j))
            {
                wealth += peternakan.getItem(i, j)->getPrice();
            }
        }
    }

    // KTKP = 13
    int kkp = wealth - 11;

    return kkp * Util::persenPajak(kkp);
}

MatrixContainer<Animal *> Peternak::getPeternakan() const
{
    return peternakan;
}

void Peternak::kasihMakan()
{
    cout << "Pilih petak kandang yang akan ditinggali" << endl;
    peternakan.printMatrix();
    cout << "Petak kandang:";
    string cell;
    cin >> cell;

    bool valid = false;
    while (!valid)
    {
        // Memilih Kotak untuk diberi makan
        try
        {
            cout << "Kamu memilih " << peternakan.getItem(cell)->getName() << " untuk diberi makan." << endl;
            cout << "Pilih pangan yang akan diberikan:" << endl;
            cout << "[Penyimpanan]:" << endl;
            inventory.printMatrix();

            // setIsDone
            valid = true;
            bool isDone = false;
            while (!isDone)
            {
                // Memilih kotak sumber makanan
                try
                {

                    string makanan;
                    cout << "Slot: ";
                    cin >> makanan;
                    peternakan.getItem(cell)->feed(*dynamic_cast<Product *>(inventory.getMakanan(makanan)));
                    cout << peternakan.getMakanan(cell)->getName() << " sudah diberi makan dan beratnya menjadi " << peternakan.getItem(cell)->getWeight() << endl;

                    // Set isDone
                    isDone = true;
                }
                catch (const GameException &e)
                {
                    e.displayMessage();
                }
            }
        }
        catch (const GameException &e)
        {
            e.displayMessage();
        }
    }
}

bool Peternak::isPanenableMatrix()
{
    for (int i = 0; i < peternakan.getRow(); i++)
    {
        for (int j = 0; j < peternakan.getCol(); j++)
        {
            if (peternakan.getItem(i, j)->isReadyToHarvest())
            {
                return true;
            }
        }
    }
    return false;
}

void Peternak::cekPanen(string cell)
{
    if (peternakan.isCellEmpty(cell))
    {
        /**
         * @TODO: throw EmptyCell
         */
    }
    if (!peternakan.getItem(cell)->isReadyToHarvest())
    {
        /**
         * @TODO: throw NotReadyToHarvest
         */
    }
}

void Peternak::panenTernak()
{
    if (isPanenableMatrix())
    {
        /**
         * @TODO: throw NotPanenable
         */
    }

    // Cetak matrix
    cout << "[Peternakan]:" << endl;
    peternakan.printMatrix();
    map<string, int> temp;

    // mapping sementara dari peternakan
    for (int i = 0; i < peternakan.getRow(); i++)
    {
        for (int j = 0; j < peternakan.getCol(); j++)
        {
            if (peternakan.getItem(i, j)->isReadyToHarvest())
            {
                cout << "- " << Util::angkaToHuruf(j) << i << ": " << peternakan.getItem(i, j)->getName() << endl;
                temp[peternakan.getItem(i, j)->getKodeHuruf()]++;
            }
        }
    }

    // menampilkan hewan yang bisa dipanen
    cout << "Pilih hewan siap panen yang kamu miliki" << endl;
    map<string, int>::iterator it = temp.begin();
    int i = 1;
    while (it != temp.end())
    {
        cout << i << " ." << it->first << " (" << it->second << "petak siap dipanen)" << endl;
        ++it;
        i++;
    }

    // Memilih hewan dari map yang sudah dibuat
    cout << "Nomor hewan yang ingin dipanen: ";
    int in;
    cin >> in;
    if (in < 0 || in > (int)temp.size())
    {
        /**
         * @TODO: throw InvalidInput
         */
    }

    // mengambil hewan
    map<string, int>::iterator item = temp.begin();
    for (int i = 0; i < in; i++)
    {
        ++item;
    }

    // memeriksa kapasitas inventory
    int jumlahProduct;
    for (int i = 0; i < peternakan.getRow(); i++)
    {
        for (int j = 0; j < peternakan.getCol(); j++)
        {
            if (peternakan.getItem(i, j)->getKodeHuruf() == item->first)
            {
                jumlahProduct = (int)peternakan.getItem(i, j)->getProduct().size();
            }
            break;
        }
    }

    // mengambil jumlah panen
    cout << "Berapa petak yang ingin dipanen: ";
    int quantity;
    cin >> quantity;

    // proses dan cek error
    if (quantity > item->second)
    {
        /**
         * @TODO: throw NotEnoughPetakPanen
         */
    }

    if (quantity * jumlahProduct > inventory.emptySpace())
    {
        /**
         * @TODO: throw NotEnoughSpace
         */
    }

    // cari koordinat available space
    vector<pair<int, int>> avail = inventory.getEmptySpacePoints();
    int row, col;

    // meminta masukan petak dan proses sesuai masukan
    int j = 1;
    while (j <= quantity)
    {
        try
        {
            cout << "Petak ke-" << j << ": ";
            string cell;
            cin >> cell;

            // validasi cell masukan
            cekPanen(cell);

            // Masukkan vector product ke item
            for (int i = 0; i < jumlahProduct; i++)
            {
                row = avail[i + jumlahProduct * (j - 1)].first;
                col = avail[i + jumlahProduct * (j - 1)].second;
                Product prod = peternakan.getItem(cell)->getProduct()[i];
                inventory.addItem(row, col, (&prod));
            };

            // destruct animal dan hilangkan dari peternakan
            peternakan.getItem(cell)->~Animal();
            peternakan.removeItem(cell);

            j++;
        }
        catch (const GameException &e)
        {
            e.displayMessage();
        }
    }
}

void Peternak::letakTernak()
{
    if (peternakan.isMatrixFull())
    {
        /**
         * TODO: Throw MatrixFullException
         */
    }

    if (inventory.isObjectEmpty<Animal *>())
    {
        /**
         * TODO: Throw MatrixEmptyException
         */
    }

    // print inventory
    printInventory();

    // pilih dari inventory
    Animal *animal = NULL;
    string inventoryKoor;

    while (animal == NULL)
    {
        try
        {
            cout << "Slot: ";
            cin >> inventoryKoor;
            cout << '\n';
            animal = dynamic_cast<Animal *>(inventory.getItem(inventoryKoor));
            if (animal == NULL)
            {
                /**
                 * TODO: NotAnimalException
                 */
            }
            cout << "Kamu memilih: " << animal->getName() << ".\n\n";
            inventory.removeItem(inventoryKoor);
        }
        catch (const GameException &e)
        {
            e.displayMessage();
        }
    }

    // pilih petak peternakan
    bool isDone = false;
    string peternakanKoor;
    cout << "Pilih petak tanah yang akan dijadikan kandang\n\n";
    cout << "    ================[ Peternakan ]==================\n\n";
    peternakan.printMatrix();
    cout << '\n';

    // mengambil ternak dari petak tanah
    while (!isDone)
    {
        try
        {
            cout << "Petak tanah: ";
            cin >> peternakanKoor;
            cout << '\n';

            peternakan.addItem(peternakanKoor, animal);
            isDone = true;

            cout << "Dengan hati-hati, kamu meletakkan seekor " << animal->getName() << " di kandang." << endl
                 << endl;
            cout << animal->getName() << " telah menjadi peliharaanmu sekarang!" << endl
                 << endl;
        }
        catch (const GameException &e)
        {
            e.displayMessage();
        }
    }
}

void Peternak::printPeternakan()
{
    printHeader("Peternakan");

    // Cetak matrix
    peternakan.printMatrix();

    // mapping sementara dari peternakan
    for (int i = 0; i < peternakan.getRow(); i++)
    {
        for (int j = 0; j < peternakan.getCol(); j++)
        {
            if (!peternakan.isCellEmpty(i, j) && peternakan.getItem(i, j)->isReadyToHarvest())
            {
                cout << "- " << Util::angkaToHuruf(j) << i << ": " << peternakan.getItem(i, j)->getName() << endl;
            }
        }
    }
}
