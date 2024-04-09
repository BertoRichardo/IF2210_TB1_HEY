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
   Plant(const string&, const string&, int, const string&, int, int, const Product&);
   /**
    * cctor
    * @param other Tanaman lain
   */
    Plant(const Plant&);
    /**
     * operator assignment
    */
    Plant& operator=(const Plant&);
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