#ifndef PRODUCTCONFIG_HPP
#define PRODUCTCONFIG_HPP

#include <iostream>
#include "Config.hpp"
using namespace std;

class ProductConfig : public Config {
    private:
        string type;
        string origin;
        int added_weight;

    public:
        /** DEFAULT CONSTRUCTOR
         * Creates a default Product object as well as the parent Config
        */
        ProductConfig();

        /** USER DEFINED CONSTRUCTOR
         * @param id Assigns id to parent Config
         * @param kode_huruf Assigns kode_huruf to parent Config
         * @param nama Assigns nama to parent Config
         * @param price Assigns price to parent Config
         * @param type Assigns type to object attribute
         * @param origin Assigns origin to object attribute
         * @param added_weight Assigns added_weight to object attribute
        */
        ProductConfig(int,string,string,int,string,string,int);

        // Attribute type getter and setter

        /** TYPE GETTER
         * @return type of object
        */
        string getType();

        /** TYPE SETTER
         * @param type Replaces the attribute type with the new one from the parameter
        */
        void setType(string);

        // Attribute origin getter and setter

        /** ORIGIN GETTER
         * @return origin of attribute
        */
        string getOrigin();

        /** ORIGIN SETTER
         * @param origin Replaces the attribute origin with the new one from the parameter
        */
        void setOrigin(string);

        // Attribute added weight getter and setter

        /** ADDED WEIGHT GETTER
         * @return added weight of attribute
        */
        int getAddedWeight();

        /** ADDED WEIGHT SETTER
         * @param added_weight Replaces the attribute added_weight with the new one from the parameter
        */
        void setAddedWeight(int);

        /** ALL SETTER
         * @param id Assigns id to parent Config
         * @param kode_huruf Assigns kode_huruf to parent Config
         * @param nama Assigns nama to parent Config
         * @param price Assigns price to parent Config
         * @param type Assigns type to object attribute
         * @param origin Assigns origin to object attribute
         * @param added_weight Assigns added_weight to object attribute
        */
        void setAll(int,string,string,int,string,string,int);
};

#endif