#include "../header/Player.hpp"

Player::Player(string username_)
{
    username = username_;
    MatrixContainer<GameObject *> inventory(10, 10);
    // inventory = inventory_;
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

map<string, int> Player::getInventoryCount()
{
    map<string, int> inventoryCount;
    for (int i = 0; i < inventory.getRow(); i++)
    {
        for (int j = 0; j < inventory.getCol(); j++)
        {
            inventoryCount[inventory.getItem(i, j)->getName()] += 1;
        }
    }
    return inventoryCount;
}

/**
 * - TODO: Tambahkan eat, jual , beli
 */

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
            try
            {
                // Ubah string koordinat menjadi row dan col
                pair<int, int> res = inventory.strToRowCol(koordinat);
                int r = res.first;
                int c = res.second;

                Product *makanan = dynamic_cast<Product *>(inventory.getMakanan(r, c));
                weigth += makanan->getAddedWeight();
                cout << "Dengan lahapnya, kamu memakan hidangan itu" << endl;
                cout << "Alhasil, berat badan kamu naik menjadi " << weigth << endl;
                inventory.removeItem(r, c);
                makanan->~Product();

                // Makanan sudah dimakan
                isDone = true;
            }
            /**
             * TODO: KERJAKAN CATCH
             */
            catch (const GameException &e)
            {
                e.displayMessage();
            }
        }
        /**
         * TODO: implement InputInvalid
         */
        catch (const GameException &e)
        {
        }
    }
}
