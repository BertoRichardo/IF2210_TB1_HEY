#include "../header/Util.hpp"

pair<int, int> Util::strToRowCol(string koordinat)
{
    // Cari nilai kolom
    int i = 0;
    int col = 0;
    if (koordinat[i] < 'A' || koordinat[i] > 'Z')
    {
        throw InputInvalidException();
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
            throw InputInvalidException();
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
    string result = "";
    while (in != -1)
    {
        int sisa = in % 26;
        result += (char)('A' + sisa);
        in /= 26;
        in--;
    }
    reverse(result.begin(), result.end());
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

bool Util::customComparator(const pair<int, pair<string, string>> &a, const pair<int, pair<string, string>> &b)
{
    // Priority int dengan urutan menurun
    if (a.first != b.first)
    {
        return a.first > b.first; // urutan menurun
    }

    // Jika int sama, bandingkan string secara naik
    return a.second.first < b.second.first;
}

void Util::clearScreen()
{
    system("clear");
}

void Util::waitScreen(int ms)
{
    this_thread::sleep_for(chrono::milliseconds(ms));
}

void Util::displayStartingScreen()
{
    clearScreen();
    cout << "Initialization begin..." << endl;
    cout << "█▒▒▒▒▒▒▒▒▒ 10%" << endl;
    waitScreen(300);
    clearScreen();

    cout << "Initialization begin..." << endl;
    cout << "██▒▒▒▒▒▒▒▒ 20%" << endl;
    waitScreen(300);
    clearScreen();

    cout << "Initialization begin..." << endl;
    cout << "███▒▒▒▒▒▒▒ 30%" << endl;
    waitScreen(300);
    clearScreen();

    cout << "Initialization begin..." << endl;
    cout << "████▒▒▒▒▒▒ 40%" << endl;
    waitScreen(300);
    clearScreen();

    cout << "Initialization begin..." << endl;
    cout << "█████▒▒▒▒▒ 50%" << endl;
    waitScreen(300);
    clearScreen();

    cout << "Initialization begin..." << endl;
    cout << "██████▒▒▒▒ 60%" << endl;
    waitScreen(300);
    clearScreen();

    cout << "Initialization begin..." << endl;
    cout << "███████▒▒▒ 70%" << endl;
    waitScreen(300);
    clearScreen();

    cout << "Initialization begin..." << endl;
    cout << "████████▒▒ 80%" << endl;
    waitScreen(300);
    clearScreen();

    cout << "Initialization begin..." << endl;
    cout << "█████████▒ 90%" << endl;
    waitScreen(300);
    clearScreen();

    cout << "Initialization begin..." << endl;
    cout << "██████████ 100%" << endl;
    waitScreen(300);
    clearScreen();

    cout << "==========================================================================================================";
    cout << '\n';
    std::cout << "  _    _       _                  ______                                 __     ___   ___          __     \n"
                 " | |  | |     | |                |  ____|                                \\ \\   / / \\ | \\ \\        / /\\    \n"
                 " | |__| | __ _| | __ _           | |__   _ __ ___  _   _ _   _            \\ \\_/ /|  \\| |\\ \\  /\\  / /  \\   \n"
                 " |  __  |/ _` | |/ _` |          |  __| | '_ ` _ \\| | | | | | |            \\   / | . ` | \\ \\/  \\/ / /\\ \\  \n"
                 " | |  | | (_| | | (_| |          | |____| | | | | | |_| | |_| |             | |  | |\\  |  \\  /\\  / ____ \\ \n"
                 " |_|  |_|\\__,_|_|\\__,_|          |______|_| |_| |_|\\__, |\\__,_|             |_|  |_| \\_|   \\/  \\/_/    \\_\\\n"
                 "                         ______                     __/ |        ______                                       \n"
                 "                        |______|                   |___/        |______|                                      \n";
    // cout << " _   __ _____ _     _____ _       ___    _   __ ___________  ___     ___  ___    ___   _   _ " << endl;
    // cout << "| | / /|  ___| |   |  _  | |     / _ \\  | | / /|  ___| ___ \\/ _ \\   |_  |/ _ \\  / _ \\ | \\ | |" << endl;
    // cout << "| |/ / | |__ | |   | | | | |    / /_\\ \\ | |/ / | |__ | |_/ / /_\\ \\    | / /_\\ \\/ /_\\ \\|  \\| |" << endl;
    // cout << "|    \\ |  __|| |   | | | | |    |  _  | |    \\ |  __||    /|  _  |    | |  _  ||  _  || . ` |" << endl;
    // cout << "| |\\  \\| |___| |___\\ \\_/ / |____| | | | | |\\  \\| |___| |\\ \\| | | |/\\__/ / | | || | | || |\\  |" << endl;
    // cout << "\\_| \\_/\\____/\\_____/\\___/\\_____/\\_| |_/ \\_| \\_/\\____/\\_| \\_\\_| |_/\\____/\\_| |_/\\_| |_/\\_| \\_/" << endl;
    // cout << "\n";
    cout << "==========================================================================================================";
    cout << "\n\n";
}

bool Util::containSpace(string s)
{
    for (int i = 0; i < (int)s.size(); i++)
    {
        if (s[i] == ' ')
            return true;
    }
    return false;
}

string Util::rowColToStr(int row, int col)
{
    return angkaToHuruf(col) + to_string(row + 1);
}