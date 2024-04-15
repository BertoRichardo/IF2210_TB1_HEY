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
    int wealth = getWealthFromInv() + getWealthFromPeternakan() + getGulden();

    // KTKP = 11
    int kkp = wealth - 11;
    int pajak = round((float)(((float)kkp * (float)Util::persenPajak(kkp)) / (float)100));
    return pajak;
}

MatrixContainer<Animal *> Peternak::getPeternakan() const
{
    return peternakan;
}

void Peternak::kasihMakan()
{
    // cek jika peternakan kosong
    if (peternakan.isMatrixEmpty())
    {
        /**
         * @todo: throw peternakanEmpty
         */
    }

    // cukup beri pesan
    if (inventory.isFoodEmpty())
    {
        cout << "Tidak ada makanan pada inventory" << '\n';
        return;
    }

    string cell;

    cout << "Pilih petak kandang yang akan ditinggali" << endl;
    printPeternakan();

    Animal *animal = NULL;
    string farmCoordinate;

    while (animal == NULL)
    {
        try
        {
            cout << endl;
            cout << "Petak kandang: ";
            cin >> farmCoordinate;
            cout << '\n';

            animal = peternakan.getItem(farmCoordinate);
            cout << "Kamu memilih " << animal->getName() << " untuk diberi makan.\n";
        }
        catch (const GameException &e)
        {
            e.displayMessage();
        }
    }

    // //Cek makanan
    // if (animal->getType() == "OMNIVORE")
    // {

    // }
    // else if (animal->getType() == "CARNIVORE")
    // {
    // }
    // else // animal->getType() == "HERBIVORE"
    // {

    // }

    cout << "Pilih pangan yang akan diberikan:\n\n";
    printInventory();
    cout << '\n';

    Product *product = NULL;
    string invCoordinate;
    while (product == NULL)
    {
        try
        {
            cout << "Slot: ";
            cin >> invCoordinate;
            cout << '\n';

            product = dynamic_cast<Product *>(inventory.getItem(invCoordinate));
        }
        catch (const GameException &e)
        {
            e.displayMessage();
        }
    }

    animal->feed(*(product));
    inventory.removeItem(invCoordinate);
    product->~Product();
    cout << animal->getName() << " sudah diberi makan dan beratnya menjadi" << animal->getWeight() << endl;
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
    printPeternakan();
    map<pair<string, int>, int> temp;

    // mapping sementara dari peternakan
    for (int i = 0; i < peternakan.getRow(); i++)
    {
        for (int j = 0; j < peternakan.getCol(); j++)
        {
            if (!peternakan.isCellEmpty(i, j) && peternakan.getItem(i, j)->isReadyToHarvest())
            {
                temp[{peternakan.getItem(i, j)->getKodeHuruf(), (int)peternakan.getItem(i, j)->getProduct().size()}]++;
            }
        }
    }

    // menampilkan hewan yang bisa dipanen
    cout << endl
         << "Pilih hewan siap panen yang kamu miliki" << endl
         << endl;

    map<pair<string, int>, int>::iterator it = temp.begin();
    int i = 1;
    while (it != temp.end())
    {
        cout << i++ << ". " << it->first.first << " (" << it->second << " petak siap dipanen)" << endl;
        ++it;
    }

    // Memilih hewan dari map yang sudah dibuat
    cout << "Nomor hewan yang ingin dipanen: ";
    int in;
    cin >> in;
    if (in < 0 || in > (int)temp.size())
    {
        throw InputInvalidException();
    }

    // mengambil hewan
    map<pair<string, int>, int>::iterator item = temp.begin();
    advance(item, in - 1);

    // memeriksa kapasitas inventory
    int jumlahProduct = item->first.second;

    // mengambil jumlah panen
    cout << "Berapa petak yang ingin dipanen: ";
    int quantity;
    cin >> quantity;
    cout << endl;

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

    // meminta masukan petak dan proses sesuai masukan
    vector<string> validCell;
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

            // lolos dari validasi, bisa dieksekusi
            validCell.push_back(cell);

            // Instansiasi animal dan remove dari peternakan
            Animal *animal = peternakan.getItem(cell);
            peternakan.removeItem(cell);

            // masukkan product ke inventory
            vector<Product> products = animal->harvest();
            for (auto product : products)
            {
                inventory.addItem(new Product(product));
                cout << product.getKodeHuruf() << endl;
                cout << endl;
                cout << endl;
                cout << endl;
                printInventory();
                cout << endl;
                cout << endl;
                cout << endl;
            }

            delete animal;

            j++;
        }
        catch (const GameException &e)
        {
            e.displayMessage();
        }
    }

    // Beri pesan
    cout << quantity << " petak hewan " << item->first.first << " pada petak ";
    for (int i = 0; i < (int)validCell.size(); i++)
    {
        cout << validCell[i];
        if (i != (int)validCell.size() - 1)
        {
            cout << ", ";
        }
    }
    cout << " telah dipanen!" << endl;
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
    cout << "Pilih hewan dari penyimpanan: " << endl;
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
    printPeternakan();
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
    printHeader("[Peternakan]");

    // Cetak matrix
    peternakan.printMatrix();

    // mapping sementara dari peternakan
    for (int i = 0; i < peternakan.getRow(); i++)
    {
        for (int j = 0; j < peternakan.getCol(); j++)
        {
            if (!peternakan.isCellEmpty(i, j) && peternakan.getItem(i, j)->isReadyToHarvest())
            {
                cout << "- " << Util::angkaToHuruf(j) << i + 1 << ": " << peternakan.getItem(i, j)->getName() << endl;
            }
        }
    }
}

int Peternak::getWealthFromPeternakan() const
{
    int wealth = 0;
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
    return wealth;
}