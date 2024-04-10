#ifndef ANIMALCONFIG_HPP
#define ANIMALCONFIG_HPP

#include <iostream>
#include "Config.hpp"
using namespace std;

class AnimalConfig : public Config {
    private:
        string type;
        int weight_to_harvest;
    
    public:
        /** DEFAULT CONSTRUCTOR
         * Creates a default Animal object as well as the parent Config
        */
        AnimalConfig();

        /** USER DEFINED CONSTRUCTOR
         * @param id Assigns id to parent Config
         * @param kode_huruf Assigns kode_huruf to parent Config
         * @param nama Assigns nama to parent Config
         * @param price Assigns price to parent Config
         * @param type Assigns type to object attribute
         * @param weight_to_harvest Assigns weight_to_harvest to object attribute
        */
        AnimalConfig(int id, string kode_huruf, string nama, int price, string type, int weight_to_harvest);

        // Attribute type getter and setter

        /** TYPE GETTER
         * @return type of object
        */
        string getType();

        /** TYPE SETTER
         * @param type Replaces the attribute type with the new one from the parameter
        */
        void setType(string);

        // Attribute weight_to_harvest getter and setter

        /** WEIGHT_TO_HARVEST GETTER
         * @return weight_to_harvest of object
        */
        int getWeightToHarvest();

        /** WEIGHT_TO_HARVEST SETTER
         * @param weight_to_harvest Replaces the attribute weight_to_harvest with the new one from the parameter
        */
        void setWeightToHarvest(int);

        /** ALL SETTER
         * @param id Assigns id to parent Config
         * @param kode_huruf Assigns kode_huruf to parent Config
         * @param nama Assigns nama to parent Config
         * @param price Assigns price to parent Config
         * @param type Assigns type to object attribute
         * @param weight_to_harvest Assigns weight_to_harvest to object attribute
        */
       void setAll(int,string,string,int,string,int);
};

#endif