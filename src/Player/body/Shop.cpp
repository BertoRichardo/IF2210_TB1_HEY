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
    for (int i = 0; i < content.size(); i++)
    {
        if (nama == content.at(i).first->getName())
        {
            return content.at(i);
        }
    }
}

pair<GameObject *, int> Shop::getGoods(int idx) const
{
    return content[idx];
}

void Shop::setGoods(pair<GameObject *, int> element, string nama)
{
    for (int i = 0; i < content.size(); i++)
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
}

int Shop::getStock(int idx) const
{
    return content[idx].second;
}

int Shop::setStock(string nama, int quantity)
{
    for (int i = 0; i < content.size(); i++)
    {
        if (content[i].first->getName() == nama)
        {
            content[i].second = quantity;
        }
    }
}

int Shop::setStock(int idx, int quantity)
{
    content[idx].second = quantity;
}

void Shop::addGoods(pair<GameObject *, int> goods)
{
    size++;
    content.push_back(goods);
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
            cout << "(" << getStock(i) << ")" << endl;
        }else{
            cout << endl;
        }
    }

}