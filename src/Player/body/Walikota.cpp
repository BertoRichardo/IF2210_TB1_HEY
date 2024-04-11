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

void Walikota::buatBangunan()
{
    /**
     * TODO: tampilkan resep
     */

    if (inventory.isMatrixFull())
    {
        throw MatrixPenuhException;
    }

    bool isDone = false;
    while (!isDone)
    {
        try
        {
            string building;
            cin >> building;
            if(!cekBuild(building))
        }
        catch (InputInvalidException e)
        {
            /**
             * TODO: throw
             */
        }
        catch (GuldenInsufficientException e)
        {
            isDone = true;
        }
        catch (MaterialInsufficientException e)
        {
            isDone = true;
        }
    }
}

void Walikota::cekRecipe(map<GameObject *, int> material, int guldenCost)
{
    if (guldenCost > gulden)
    {
        throw GuldenInsufficientException;
    }
    else
    {
        /**
        * TODO: bandingkan material yang ada dengan bahan
        */
        map<string, int> materialCount;
        materialCount = getInventoryCount();
        
    }
}

bool Walikota::map_compare(map const &recipe, map const &current)
{
    // No predicate needed because there is operator== for pairs already.
    return lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(),
                                                  rhs.begin());
}

void Walikota::jual()
{
    /**
     *
     */
}
