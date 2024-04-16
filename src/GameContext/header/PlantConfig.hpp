#ifndef PLANTCONFIG_HPP
#define PLANTCONFIG_HPP

#include <iostream>
#include "Config.hpp"
using namespace std;

class PlantConfig : public Config {
    private:
        string type;
        int duration_to_harvest;

    public:
        /** DEFAULT CONSTRUCTOR
         * Creates a default Plant object as well as the parent Config
        */
        PlantConfig();

        /** USER DEFINED CONSTRUCTOR
         * @param id Assigns id to parent Config
         * @param kode_huruf Assigns kode_huruf to parent Config
         * @param nama Assigns nama to parent Config
         * @param price Assigns price to parent Config
         * @param type Assigns type to object attribute
         * @param duration_to_harvest Assigns duration_to_harvest to object attribute
        */
        PlantConfig(int,string,string,int,string,int);

        // Attribute type getter and setter

        /** TYPE GETTER
         * @return type of object
        */
        string getType() const;

        /** TYPE SETTER
         * @param type Replaces the attribute type with the new one from the parameter
        */
        void setType(string);

        // Attribute duration_to_harvest getter and setter

        /** DURATION_TO_HARVEST GETTER
         * @return weight_to_harvest of object
        */
        int getDurationToHarvest() const;

        /** DURATION_TO_HARVEST SETTER
         * @param duration_to_harvest Replaces the attribute duration_to_harvest with the new one from the parameter
        */
        void setDurationToHarvest(int);

        /** ALL SETTER
         * @param id Assigns id to parent Config
         * @param kode_huruf Assigns kode_huruf to parent Config
         * @param nama Assigns nama to parent Config
         * @param price Assigns price to parent Config
         * @param type Assigns type to object attribute
         * @param duration_to_harvest Assigns duration_to_harvest to object attribute
        */
       void setAll(int,string,string,int,string,int);
};

#endif