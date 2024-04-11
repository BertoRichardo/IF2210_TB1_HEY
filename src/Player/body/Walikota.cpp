#include "../header/Walikota.hpp"

Walikota::Walikota(string username_) : Player(username_)
{
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
}

void Walikota::jual()
{
    /**
     *
     */
    
}
