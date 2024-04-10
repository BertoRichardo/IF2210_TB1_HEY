#ifndef _ANIMAL_HPP_
#define _ANIMAL_HPP_

#include "GameObject.hpp"
#include "Product.hpp"
#include "../../GameException/header/GameException.hpp"

/** Abstract Class for Animal */
class Animal : public GameObject {
protected:
    string type;
    int harvestWeight;
    int weight;
    Product product;

public:
    /**
     * Default Constructor
     * Menciptakan object animal dengan nilai default
     * Memanggil GameObject()
     * - type = ""
     * - harvestWeight = 0
     * - weight = 0
     * - product = new Product()
    */
    Animal();
    /**
     * User defined Constructor
     * @param kodeHuruf_ kodeHuruf tanaman
     * @param name_ nama tanaman
     * @param price_ harga tanaman
     * @param type_ tipe tanaman
     * @param harvestWeight_ berat tanaman untuk dipanen
     * @param weight_ umur tanaman saat ini
     * @param product_ product yang akan dihasilkan jika dipanen
    */
    Animal(
        const string& kodeHuruf_, 
        const string& name_, 
        int price_, 
        const string& type_, 
        int harvestWeight_, 
        int weight_, 
        const Product& product_
    );

    /**
     * cctor
    */
    Animal(const Animal& other);
    /**
     * assignment operator
    */
    Animal& operator=(const Animal&);

    ~Animal();

    /**
     * Selector
    */
    string getType() const;
    void setType(const string &type_);

    int getHarvestWeight() const;
    void setHarvestWeight(int harvestWeight_);

    int getWeight() const;
    void setWeight(int weight_);

    Product getProduct() const;
    void setProduct(const Product &product_);

    /**
     * Memberi pakan untuk hewan
     * Mengecek jenis product yang dapat dimakan
     * - TODO: implementasikan sesuai dengan jenis hewan
    */
    virtual void feed(const Product& food) = 0;

    /**
     * Memberi pakan
     * Tugas yang sama dengan method feed
     * - TODO: implementasikan fungsi ini sesuai dengan jenis hewan
    */
    virtual void operator+=(const Product& food) = 0;

    /**
     * Memanen hewan
     * @return product : Product
    */
    Product harvest();
};

class Carnivore: public Animal {
public:
    /**
     * Default Constructor
     * hanya memanggil Default Constructor Animal 
    */
    Carnivore();
    /**
     * User defined Constructor, memanggil used defined Constructor Animal
     * @param kodeHuruf_ kodeHuruf tanaman
     * @param name_ nama tanaman
     * @param price_ harga tanaman
     * @param type_ tipe tanaman
     * @param harvestWeight_ berat tanaman untuk dipanen
     * @param weight_ umur tanaman saat ini
     * @param product_ product yang akan dihasilkan jika dipanen
    */
    Carnivore(
        const string& kodeHuruf_, 
        const string& name_, 
        int price_, 
        const string& type_, 
        int harvestWeight_, 
        int weight_, 
        const Product& product_
    );
    /**
     * cctor
    */
    Carnivore(const Carnivore& other);
    /**
     * assignment operator
    */
    Carnivore& operator=(const Carnivore&);

    ~Carnivore();

    /**
     * Memberi makan hewan dengan product Hewan
     * @param food product makanan
     * @throw FeedTypeInvalidException()
    */
    void feed(const Product &food); 

    /**
     * Memberi makan hewan dengan product Animal
     * @param food product makanan
     * @throw FeedTypeInvalidException()
    */
    void operator+=(const Product &food);
};

class Herbivore: public Animal {
public:
    /**
     * Default Constructor
     * hanya memanggil Default Constructor Animal 
    */
    Herbivore();
    /**
     * User defined Constructor, memanggil used defined Constructor Animal
     * @param kodeHuruf_ kodeHuruf tanaman
     * @param name_ nama tanaman
     * @param price_ harga tanaman
     * @param type_ tipe tanaman
     * @param harvestWeight_ berat tanaman untuk dipanen
     * @param weight_ umur tanaman saat ini
     * @param product_ product yang akan dihasilkan jika dipanen
    */
    Herbivore(
        const string& kodeHuruf_, 
        const string& name_, 
        int price_, 
        const string& type_, 
        int harvestWeight_, 
        int weight_, 
        const Product& product_
    );
    /**
     * cctor
    */
    Herbivore(const Carnivore& other);
    /**
     * assignment operator
    */
    Herbivore& operator=(const Carnivore&);

    ~Herbivore();

    /**
     * Memberi makan hewan dengan product Hewan
     * @param food product makanan
     * @throw FeedTypeInvalidException()
    */
    void feed(const Product &food); 

    /**
     * Memberi makan hewan dengan product Animal
     * @param food product makanan
     * @throw FeedTypeInvalidException()
    */
    void operator+=(const Product &food);
};

class Omnivore: public Animal {
public:
    /**
     * Default Constructor
     * hanya memanggil Default Constructor Animal 
    */
    Omnivore();
    /**
     * User defined Constructor, memanggil used defined Constructor Animal
     * @param kodeHuruf_ kodeHuruf tanaman
     * @param name_ nama tanaman
     * @param price_ harga tanaman
     * @param type_ tipe tanaman
     * @param harvestWeight_ berat tanaman untuk dipanen
     * @param weight_ umur tanaman saat ini
     * @param product_ product yang akan dihasilkan jika dipanen
    */
    Omnivore(
        const string& kodeHuruf_, 
        const string& name_, 
        int price_, 
        const string& type_, 
        int harvestWeight_, 
        int weight_, 
        const Product& product_
    );
    /**
     * cctor
    */
    Omnivore(const Carnivore& other);
    /**
     * assignment operator
    */
    Carnivore& operator=(const Carnivore&);

    ~Omnivore();

    /**
     * Memberi makan hewan dengan product Hewan
     * @param food product makanan
     * @throw FeedTypeInvalidException()
    */
    void feed(const Product &food);

    /**
     * Memberi makan hewan dengan product Animal
     * @param food product makanan
     * @throw FeedTypeInvalidException()
    */
    void operator+=(const Product &food);
};

#endif