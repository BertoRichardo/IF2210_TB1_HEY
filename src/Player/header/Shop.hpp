#ifndef _SHOP_HPP_
#define _SHOP_HPP_

#include <iostream>
#include <vector>
#include <map>
using namespace std;
#include "../../GameObject/header/Building.hpp"

class Shop
{
private:
    int size;
    vector<pair<GameObject *, int>> content;

public:
    /**
     * Default Constructor
     */
    Shop();

    /**
     * User Defined Constructor
     */
    Shop(int size_, vector<pair<GameObject *, int>> content_);

    /**
     * Default destructor
     */
    ~Shop();

    /**
     * SELECTOR
     */
    int getSize() const;
    void setSize(int);

    /** SHOP ITEM ELEMENTS GETTER
     * @param nama name of the object program wanted to find
     * @return pair of game object and its quantity
     */
    pair<GameObject *, int> getGoods(string) const;

    /** SHOP ITEM ELEMENTS GETTER
     * @param idx index of the object program wanted to find
     * @return pair of game object and its quantity
     */
    pair<GameObject *, int> getGoods(int) const;

    /** SHOP ITEM ELEMENTS SETTER
     * @param element the replacer element
     * @param nama name of the object program wanted to find
     */
    void setGoods(pair<GameObject *, int>, string);

    /** SHOP ITEM ELEMENTS SETTER
     * @param element the replacer element
     * @param idx index of the object program wanted to find
     */
    void setGoods(pair<GameObject *, int>, int);

    /** STOCK GETTER
     * @param nama name of the object program wanted to find
     * @return stock of object
     */
    int getStock(string) const;

    /** STOCK GETTER
     * @param idx index of the object program wanted to find
     * @return stock of object
     */
    int getStock(int) const;

    /** STOCK SETTER
     * @param nama name of the object program wanted to find
     * @param quantity new quantity that w*ll replace the old one
     */
    int setStock(string, int);

    /** STOCK SETTER
     * @param idx index of the object program wanted to find
     * @param quantity new quantity that will replace the old one
     */
    int setStock(int, int);

    /** ADD GOODS
     * @param element new object program that will be added to vector
     */
    void addGoods(pair<GameObject *, int>);
};

#endif