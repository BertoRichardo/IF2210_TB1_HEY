#ifndef _PLANT_HPP_
#define _PLANT_HPP_

#include "GameObject.hpp"
#include "Product.hpp"

class Plant: public GameObject {
private:
    string type;
    int harvestDuration;
    int duration;
    Product product;

public:
    /**
     * Default Constructor
     * Memanggil default constructor GameObject
     * product diciptakan dengan default construtor
    */
    Plant();
    /**
     * User defined constructor
     * @param kodeHuruf_ kodeHuruf tanaman
     * @param name_ nama tanaman
     * @param price_ harga tanaman
     * @param type_ tipe tanaman
     * @param harvestDuration_ umur tanaman untuk dipanen
     * @param duration_ umur tanaman saat ini
     * @param product_ product yang akan dihasilkan jika dipanen
    */
   Plant(const string& kodeHuruf_, const string& name_, int price_, const string& type_, int harvestDuration_, int duration_, const Product& product_);
   /**
    * cctor
    * @param other Tanaman lain
   */
    Plant(const Plant& other);
    /**
     * operator assignment
    */
    Plant& operator=(const Plant& other);
    ~Plant();

    /**
     * Selector
    */
    string getType();
    void setType(const string &type_);

    int getHarvestDuration() const;
    void setHarvestDuration(int harvestDuration_);

    int getDuration() const;
    void setDuration(int duration_);

    Product getProduct() const;
    void setProduct(const Product &product_);

    /**
     * Mengecek apakah Plant dapat dipanen 
     * @return duration >= harvestDuration 
    */
    bool isReadyToHarvest();
    /**
     * Memanen tanaman jika tanaman sudah dapat dipanen
     * @return product : Product
    */
    Product harvest();

    /**
     * Menambah usia tanaman sebesar 1
    */
    void grow();

    /**
     * Overloading Operator
     * Tugasnya sama dengan method grow()
     * Menambah usia tanaman sebesar 1
    */
    void operator++(int);

};

#endif