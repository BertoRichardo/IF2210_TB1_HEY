#include "../header/Peternak.hpp"

Peternak::Peternak(string username_, int row, int col) : Player::Player(username_)
{
    MatrixContainer<Animal *> peternakan(row, col);
    // peternakan = peternakan_;
}

Peternak::~Peternak()
{
    peternakan.~MatrixContainer();
}

string Player::getType() const
{
    return "PETERNAK";
}

void Peternak::kasihMakan()
{
    cout << "Pilih petak kandang yang akan ditinggali" << endl;
    peternakan.printMatrix(true);
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
            inventory.printMatrix(false);

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
    peternakan.removeItem(cell);
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
    peternakan.printMatrix(true);
    map<string, int> temp;

    // mapping sementara dari peternakan
    for (int i = 0; i < peternakan.getRow(); i++)
    {
        for (int j = 0; j < peternakan.getCol(); j++)
        {
            if (peternakan.getItem(i, j)->isReadyToHarvest())
            {
                // Tidak tau perlu atau gak
                // cout << "- " << angkaToHuruf(j) << i << peternakan.getItem(i, j)->getName() << endl;
                temp[peternakan.getMakanan(i, j)->getKodeHuruf()]++;
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
    int in;
    cin >> in;
    if (in < 0 || in > temp.size())
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

    // mengambil jumlah panen
    cout << "Berapa petak yang ingin dipanen: ";
    int q;
    cin >> q;

    // proses dan cek error
    if (q > item->second)
    {
        /**
         * @TODO: throw NotEnoughPetakPanen
         */
    }
    if (q > inventory.emptySpace())
    {
        /**
         * @TODO: throw NotEnoughSpace
         */
    }

    // Mengambil hewan dari peternakan
    int j = 1;
    while (j <= q)
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
    peternakan.printMatrix(true);
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

            cout << "Dengan hati-hati, kamu meletakkan seekor " << animal->getName() << " di kandang.\n\n";
            cout << animal->getName() << " telah menjadi peliharaanmu sekarang!\n";
        }
        catch (const GameException &e)
        {
            e.displayMessage();
        }
    }
}
