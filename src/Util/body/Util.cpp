#include "../header/Util.hpp"

pair<int, int> Util::strToRowCol(string koordinat)
{
    // Cari nilai kolom
    int i = 0;
    int col = 0;
    if (koordinat[i] < 'A' || koordinat[i] > 'Z')
    {
        /**
         * TODO: Throw invalidInput
         */
    }
    else
    {
        while (koordinat[i] >= 'A' && koordinat[i] <= 'Z')
        {
            col *= 26;
            col += koordinat[i] - 'A' + 1;
            i++;
        }
    }

    // Cari nilai baris
    int row = 0;
    for (int j = i; j < (int)koordinat.length(); j++)
    {
        // Cek
        if (koordinat[j] >= '0' && koordinat[j] <= '9')
        {
            row *= 10;
            row += koordinat[j] - '0';
        }
        else
        {
            /**
             * TODO: throw invalidInput
             */
        }
    }
    row--;
    col--;
    return make_pair(row, col);
}

vector<string> Util::parserSlots(string in)
{
    vector<string> hasil;
    string temp = "";
    for (int i = 0; i < (int)in.length(); i++)
    {
        //
        if (in.at(i) == ',')
        {
            hasil.push_back(temp);
            temp = "";
        }
        else if (in.at(i) != ' ')
        {
            temp.push_back(in.at(i));
        }
    }
    hasil.push_back(temp);
    return hasil;
}
int Util::persenPajak(int kkp)
{
    if (kkp <= 6)
    {
        return 5;
    }
    else if (kkp <= 25)
    {
        return 15;
    }
    else if (kkp <= 50)
    {
        return 15;
    }
    else if (kkp <= 75)
    {
        return 25;
    }
    else if (kkp <= 500)
    {
        return 30;
    }
    else
    {
        return 35;
    }
}

string Util::angkaToHuruf(int in)
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

GameObject *Util::callCCtor(GameObject *obj)
{
    if (dynamic_cast<Plant *>(obj) != NULL)
    {
        Plant *item = new Plant(*dynamic_cast<Plant *>(obj));
        return item;
    }
    else if (dynamic_cast<Animal *>(obj) != NULL)
    {
        if (dynamic_cast<Carnivore *>(obj) != NULL)
        {
            Carnivore *item = new Carnivore(*dynamic_cast<Carnivore *>(obj));
            return item;
        }
        else if (dynamic_cast<Herbivore *>(obj) != NULL)
        {
            Herbivore *item = new Herbivore(*dynamic_cast<Herbivore *>(obj));
            return item;
        }
        else if (dynamic_cast<Omnivore *>(obj) != NULL)
        {
            Omnivore *item = new Omnivore(*dynamic_cast<Omnivore *>(obj));
            return item;
        }
    }
    else if (dynamic_cast<Product *>(obj) != NULL)
    {
        Product *item = new Product(*dynamic_cast<Product *>(obj));
        return item;
    }
    else // if (dynamic_cast<Building *>(obj) != NULL)
    {
        Building *item = new Building(*dynamic_cast<Building *>(obj));
        return item;
    }

    return NULL;
}
