#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <iostream>
#include <string>
using namespace std;

class Config {
    protected:
        int id;
        string kode_huruf;
        string nama;
        int price;
    
    public:
        /** DEFAULT CONSTRUCTOR
         * Creates a Config object with default attributes
         * - id = 0
         * - kode_huruf = ""
         * - name = ""
         * - price = 0
         */
        Config();

        /** USER DEFINED CONSTRUCTOR
         * Creates a Config object with user-defined attributes
         * @param id Assigns parameter id to attribute id
         * @param kode_huruf Assigns parameter kode_huruf to attribute kode_huruf
         * @param nama Assigns parameter name to attribute name
         * @param price Assigns parameter price to attribute price
         */
        Config(int, string, string, int);

        // Attribute id getter and setter

        /** ID GETTER
         * @return id from the object attribute
        */
        int getID() const;

        /** ID SETTER
         * @param id Replace the attribute id with the new one from the parameter
        */
        void setID(int);

        // Attribute kode_huruf getter and setter

        /** KODE_HURUF GETTER
         * @return kode_huruf from the object attribute
        */
        string getKodeHuruf() const;

        /** KODE_HURUF SETTER
         * @param kode_huruf Replace the attribute kode_huruf with the new one from the parameter
        */
        void setKodeHuruf(string);

        // Attribute name getter and setter

        /** NAMA GETTER
         * @return nama from the object attribute
        */
        string getNama() const;

        /** NAMA SETTER
         * @param nama Replace the attribute nama with the new one from the parameter
        */
        void setNama(string);

        // Attribute price getter and setter

        /** PRICE GETTER
         * @return price value from the object attribute
        */
        int getPrice() const;

        /** PRICE SETTER
         * @param price Replace the attribute price with the new one from the parameter
        */
        void setPrice(int);
};

#endif