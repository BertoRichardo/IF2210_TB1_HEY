#ifndef _BUILDING_HPP_
#define _BUILDING_HPP_

#include "GameObject.hpp"
#include <vector>

class Building: public GameObject {
private:
    vector<pair<string,int>> recipe;

public:
    /**
     * Default Constructor
     * Hanya memanggil Default Constructor GameObject
    */
    Building();
    /**
     * User Defined Constructor 
     * @param kodeHuruf_ kodeHuruf bangunan
     * @param name_ nama bangunan
     * @param price_ harga bangunan
     * @param recipe_ resep bangunan
    */
    Building(const string&, const string&, int, const vector<pair<string, int>> &);
    /**
     * Copy Constructor Bangunan
     * @param other bangunan lain yang akan di-copy
    */
    Building(const Building&);
    /**
     * Melakukan clear pada recipe untuk melepaskan memori 
    */
   /**
    * assignment operator
   */
    Building& operator=(const Building&);
    
    ~Building();

    /**
     * Selector
    */
    vector<pair<string,int>> getRecipe() const;
    void setRecipe(const vector<pair<string,int>> &);
};

#endif