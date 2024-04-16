#include "../header/Shop.hpp"
using namespace std;
Shop::Shop() : size(0)
{
}

Shop::Shop(int size_, vector<pair<GameObject *, int>> content_)
{
    size = size_;
    content = content_;
}

Shop::~Shop() {}

int Shop::getSize() const
{
    return size;
}

void Shop::setSize(int size_)
{
    size = size_;
}

pair<GameObject *, int> Shop::getGoods(string nama) const
{
    for (int i = 0; i < (int)content.size(); i++)
    {
        if (nama == content.at(i).first->getName())
        {
            return content.at(i);
        }
    }
    throw CustomException("Barang tidak ada");
}

pair<GameObject *, int> Shop::getGoods(int idx) const
{
    return content[idx];
}

vector<pair<string, string>> Shop::getGoodsItem()
{
    vector<pair<string, string>> res;
    for (int i = 0; i < (int)content.size(); i++)
    {
        Plant *plant = dynamic_cast<Plant *>(getGameObject(i));
        Animal *animal = dynamic_cast<Animal *>(getGameObject(i));

        if (plant == NULL && animal == NULL && content.at(i).second)
        {
            res.push_back({content.at(i).first->getName(), to_string(content.at(i).second)});
        }
    }
    return res;
}

void Shop::setGoods(pair<GameObject *, int> element, string nama)
{
    for (int i = 0; i < (int)content.size(); i++)
    {
        if (nama == content.at(i).first->getName())
        {
            content.at(i) = element;
        }
    }
}

void Shop::setGoods(pair<GameObject *, int> element, int idx)
{
    content[idx] = element;
}

GameObject *Shop::getGameObject(string nama) const
{
    for (int i = 0; i < size; i++)
    {
        if (content[i].first->getName() == nama)
        {
            return content[i].first;
        }
    }
    throw CustomException("Barang tidak ada");
}

GameObject *Shop::getGameObject(int idx) const
{

    return content[idx].first;
}

int Shop::getStock(string nama) const
{
    for (int i = 0; i < size; i++)
    {
        if (content[i].first->getName() == nama)
        {
            return content[i].second;
        }
    }
    throw CustomException("Barang tidak ada");
}

int Shop::getStock(int idx) const
{
    return content[idx].second;
}

void Shop::setStock(string nama, int quantity)
{
    for (int i = 0; i < (int)content.size(); i++)
    {
        if (content[i].first->getName() == nama)
        {
            content[i].second = quantity;
        }
    }
}

void Shop::setStock(int idx, int quantity)
{
    content[idx].second = quantity;
}

void Shop::addGoods(pair<GameObject *, int> goods)
{
    for (int i = 0; i < (int)content.size(); i++)
    {
        if (content[i].first == goods.first)
        {
            setStock(goods.first->getName(), getStock(goods.first->getName()) + goods.second);
            break;
        }
    }
    size++;
    content.push_back(goods);
}

void Shop::operator+(const GameObject &obj)
{
    for (int i = 0; i < size; i++)
    {
        // Avoid add stock for unlimited object
        Plant *plant = dynamic_cast<Plant *>(getGameObject(i));
        Animal *animal = dynamic_cast<Animal *>(getGameObject(i));

        // add for limited object
        if (plant == NULL && animal == NULL && (*getGameObject(i)) == obj)
        {
            content[i].second = getStock(i) + 1;
        }
    }
}

void Shop::operator-(const GameObject &obj)
{
    for (int i = 0; i < size; i++)
    {
        // Avoid substract stock for unlimited object
        Plant *plant = dynamic_cast<Plant *>(getGameObject(i));
        Animal *animal = dynamic_cast<Animal *>(getGameObject(i));

        // substract for limited object
        if (plant == NULL && animal == NULL && *(getGameObject(i)) == obj)
        {
            content[i].second = getStock(i) - 1;
        }
    }
}

void Shop::printToko()
{
    cout << "Selamat datang di toko!!" << endl;
    cout << "Berikut adalah hal yang dapat Anda beli " << endl;

    for (int i = 0; i < size; i++)
    {

        cout << i + 1 << ". " << getGameObject(i)->getName() << " - " << getGameObject(i)->getPrice();

        // Avoid print stock for unlimited object
        Plant *plant = dynamic_cast<Plant *>(getGameObject(i));
        Animal *animal = dynamic_cast<Animal *>(getGameObject(i));

        // Print for limited object
        if (plant == NULL && animal == NULL)
        {
            cout << " (" << getStock(i) << ")" << endl;
        }
        else
        {
            cout << endl;
        }
    }
}

GameObject *Shop::operator[](int idx) const
{
    return getGameObject(idx);
}

GameObject *Shop::operator[](string str) const
{
    return getGameObject(str);
}