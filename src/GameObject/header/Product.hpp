#ifndef _PRODUCT_HPP_
#define _PRODUCT_HPP_

#include "GameObject.hpp"

class Product: public GameObject {
private:
    string type;
    string origin;
    int addedWeight;

public:
    /**
     * Default constructor
     * Mengisi semua atribut dengan nilai default
     * Memanggil Default Constructor Base Class
     * - type = ""
     * - origin = ""
     * - addedWeight = 0
    */
    Product();
    /**
     * User Defined Constructor 
     * Memanggil User Defined Constructor Base Class
     * @param kodeHuruf_ KodeHuruf sesuai config
     * @param name_ nama sesuai config
     * @param price harga product
     * @param type tipe dari product tepat 3 karakter
     * @param origin asal product
     * @param addedWeight berat tambahan jika dimakan oleh Player atau Animal
    */
    Product(const string& kodeHuruf_, const string& name_, int price_, const string& type_, const string& origin_, int addedWeight_);
    /**
     * Copy Constructor
     * @param other - Product lain yang akan dicopy
    */
    Product(const Product& other);
    /**
     * assignment operator
    */
    Product& operator=(const Product& other);
    
    ~Product();

    /**Selector*/
    string getType() const;
    void setType(const string &type_);
    string getOrigin() const;
    void setOrigin(const string &origin_);
    int getAddedWeight() const;
    void setAddedWeight(int addedWeight_);
};

#endif