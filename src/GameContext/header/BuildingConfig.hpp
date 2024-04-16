#ifndef BUILDINGCONFIG_HPP
#define BUILDINGCONFIG_HPP

#include <iostream>
#include <vector>
#include <map>
#include "Config.hpp"
using namespace std;

class BuildingConfig : public Config {
    private:
        vector<pair<string,int>> recipe;

    public:
        /** DEFAULT CONSTRUCTOR
         * Creates a default Building object as well as the parent Config
        */
        BuildingConfig();

        /** USER DEFINED CONSTRUCTOR
         * @param id Assigns id to parent Config
         * @param kode_huruf Assigns kode_huruf to parent Config
         * @param nama Assigns nama to parent Config
         * @param price Assigns price to parent Config
         * @param recipe Assigns recipe to object attribute
        */
        BuildingConfig(int id, string kode_huruf, string nama, int price, vector<pair<string,int>> recipe);

        // Attribute recipe getter and setter

        /** RECIPE GETTER
         * @return list of recipes (containing product name and quantity)
        */
        vector<pair<string,int>> getRecipe() const;

        /** RECIPE SETTER
         * @param recipe Replaces the whole recipe with the new one
        */
        void setRecipe(const vector<pair<string,int>>);

        // Attribute recipe element getter and setter

        /** RECIPE COMP GETTER
         * @param idx Chooses the element based on index
         * @return pair of string and integer in the element index of object
        */
        pair<string,int> getRecipeComp(int) const;

        /** RECIPE COMP SETTER
         * @param element Replaces the element from the recipe with the new one
         * @param idx Chooses which element that will be replaced
        */
        void setRecipeComp(pair<string,int>,int);

        // Attribute product name of recipe element getter and setter

        /** PRODUCT NAME GETTER
         * @param idx Chooses the element based on index and the program will choose the product name
         * @return product name from the element based on parameter
        */
        string getProductName(int) const;

        /** PRODUCT NAME SETTER
         * @param nama Replaces the product name from the recipe with the new one based on index
         * @param idx Chooses the element based on index
        */
        void setProductName(string,int);

        // Attribute quantity of recipe element getter and setter

        /** QUANTITY GETTER
         * @param idx Chooses the element based on index and the program will choose the quantity
         * @return quantity from the element based on parameter
        */
        int getQuantity(int) const;

        /** PRODUCT NAME SETTER
         * @param val Replaces the quantity from the recipe with the new one based on index
         * @param idx Chooses the element based on index
        */
        void setQuantity(int,int);

        /** ALL SETTER
         * @param id Assigns id to parent Config
         * @param kode_huruf Assigns kode_huruf to parent Config
         * @param nama Assigns nama to parent Config
         * @param price Assigns price to parent Config
         * @param recipe Assigns recipe to object attribute
        */
       void setAll(int,string,string,int,vector<pair<string,int>>);
};

#endif