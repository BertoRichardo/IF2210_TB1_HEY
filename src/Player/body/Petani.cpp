#include "../header/Petani.hpp"

Petani::Petani(string username_, int row, int col) : Player::Player(username_)
{
    MatrixContainer<Plant *> lahan(row, col);
}

Petani::~Petani()
{
    lahan.~MatrixContainer();
}

string Player::getType() const
{
    return "PETANI";
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
    lahan.removeItem(cell);
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
    cout << "[Ladang]";
    lahan.printMatrix(true);
    map<string, int> temp;

    // mapping sementara dari lahan
    for (int i = 0; i < lahan.getRow(); i++)
    {
        for (int j = 0; j < lahan.getCol(); j++)
        {
            if (lahan.getItem(i, j)->isReadyToHarvest())
            {
                // Tidak tau perlu atau gak
                // cout << "- " << angkaToHuruf(j) << i << lahan.getItem(i, j)->getName() << endl;
                temp[lahan.getMakanan(i, j)->getKodeHuruf()]++;
            }
        }
    }
    // menampilkan tanaman yang bisa dipanen
    cout << "Pilih tanaman siap panen yang kamu miliki" << endl;
    map<string, int>::iterator it = temp.begin();
    int i = 1;
    while (it != temp.end())
    {
        cout << i << " ." << it->first << " (" << it->second << "petak siap dipanen)" << endl;
        ++it;
        i++;
    }

    // Memilih tanaman dari map yang sudah dibuat
    int in;
    cin >> in;
    if (in < 0 || in > temp.size())
    {
        /**
         * @TODO: throw InvalidInput
         */
    }

    // mengambil tanaman
    map<string, int>::iterator item = temp.begin();
    for (int i = 0; i < in; i++)
    {
        ++item;
    }

    // mengambil jumlah panen
    cout << "Berapa petak yang ingin dipanen: ";
    int quantity;
    cin >> quantity;

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
    while (j <= quantity)
    {
        try
        {
            cout << "Petak ke-" << j << ": ";
            string cell;
            cin >> cell;
            cekPanen(cell);
            j++;
        }
        catch (const GameException &e)
        {
            e.displayMessage();
        }
    }
}

string angkaToHuruf(int in)
{
    int sisa = in % 26;
    int hasil = in / 26;
    char back = 'A' + sisa;
    char front = 'A' + hasil;
    string result = "";
    result.push_back(front);
    result.push_back(back);
    return result;
}

void Petani::tanam()
{
    if (lahan.isMatrixFull())
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

    // pilih dari inventory
    Plant *plant = NULL;
    string inventoryKoor;

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
    bool isDone = false;
    string lahanKoor;
    cout << "Pilih petak tanah yang akan dijadikan kandang\n\n";
    cout << "    ================[ lahan ]==================\n\n";
    lahan.printMatrix(true);
    cout << '\n';

    while (!isDone)
    {
        try
        {
            cout << "Petak tanah: ";
            cin >> lahanKoor;
            cout << '\n';

            lahan.addItem(lahanKoor, plant);
            isDone = true;

            cout << "Cangkul, cangkul, cangkul yang dalam~!" << plant->getName() << " di kandang.\n\n";
            cout << plant->getName() << " berhasil ditanam!";
        }
        catch (const GameException &e)
        {
            e.displayMessage();
        }
    }
}
