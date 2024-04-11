#ifndef GAMECONTEXT_HPP
#define GAMECONTEXT_HPP

#include "AnimalConfig.hpp"
#include "BuildingConfig.hpp"
#include "PlantConfig.hpp"
#include "ProductConfig.hpp"
#include <iostream>
#include <map>
using namespace std;

class GameContext {
        private:
            map<string,AnimalConfig> animals;
            map<string,BuildingConfig> buildings;
            map<string,PlantConfig> plants;
            map<string,ProductConfig> products;

        public:
            /** DEFAULT CONSTRUCTOR
             * Creates an empty game context based on config
            */
            GameContext();

            /** USER DEFINED CONSTRUCTOR
             * Creates a game context object based on user-defined parameters
             * @param animals contains list of config animal settings
             * @param buildings contains list of config building settings
             * @param plants contains list of config plant settings
             * @param products contains list of config product settings
            */
            GameContext(map<string,AnimalConfig>,map<string,BuildingConfig>,map<string,PlantConfig>,map<string,ProductConfig>);

            // Attribute animals getter and setter

            /** ANIMALS GETTER
             * @return list of animals and its name
            */
            map<string,AnimalConfig> getAnimals();

            /** ANIMALS SETTER
             * @param animals Replaces the old animals list with the new one
            */
            void setAnimals(map<string,AnimalConfig>);

            // Attribute buildings getter and setter

            /** BUILDINGS GETTER
             * @return list of buildings and its name
            */
            map<string,BuildingConfig> getBuildings();

            /** BUILDINGS SETTER
             * @param buildings Replaces the old buildings list with the new one
            */
            void setBuildings(map<string,BuildingConfig>);

            // Attribute plants getter and setter

            /** PLANTS GETTER
             * @return list of plants and its name
            */
            map<string,PlantConfig> getPlants();

            /** PLANTS SETTER
             * @param plants Replaces the old plants list with the new one
            */
            void setPlants(map<string,PlantConfig>);

            // Attribute products getter and setter

            /** PRODUCTS GETTER
             * @return list of products and its name
            */
            map<string,ProductConfig> getProducts();

            /** PRODUCTS SETTER
             * @param products Replaces the old products list with the new one
            */
            void setProducts(map<string,ProductConfig>);

            // Config reader

            /** CONFIG READER
             * Read text files of config and fill the component of Game Context based on the files.
            */
            void readConfig();
};

#endif