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