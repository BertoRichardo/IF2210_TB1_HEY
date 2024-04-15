#ifndef _ANIMAL_HPP_
#define _ANIMAL_HPP_

#include "GameObject.hpp"
#include "Product.hpp"
#include <vector>
#include "../../GameException/header/GameException.hpp"

/** Abstract Class for Animal */
class Animal : public GameObject
{
protected:
    string type;
    int harvestWeight;
    int weight;
    vector<Product> products;

public:
    /**
     * Default Constructor
     * Menciptakan object animal dengan nilai default
     * Memanggil GameObject()
     * - type = ""
     * - harvestWeight = 0
     * - weight = 0
     * - products = new vector<Product>
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
     * @param products_ product yang akan dihasilkan jika dipanen
     */
    Animal(
        const string &kodeHuruf_,
        const string &name_,
        int price_,
        const string &type_,
        int harvestWeight_,
        int weight_,
        const vector<Product> &products_);

    /**
     * cctor
     */
    Animal(const Animal &other);
    /**
     * assignment operator
     */
    Animal &operator=(const Animal &other);

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

    vector<Product> getProduct() const;
    void setProduct(const vector<Product> &products_);

    /**
     * Memberi pakan untuk hewan
     * Mengecek jenis product yang dapat dimakan
     */
    virtual void feed(const Product &food) = 0;

    /**
     * Memberi pakan
     * Tugas yang sama dengan method feed
     */
    virtual void operator+=(const Product &food) = 0;

    /**
     * Mengecek apakah animal sudah bisa dipanen atau tidak
     * @return weight >= harvestWeight
     */
    bool isReadyToHarvest();
    /**
     * Memanen hewan
     * @return product : Product
     */
    vector<Product> harvest();
};

class Carnivore : public Animal
{
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
        const string &kodeHuruf_,
        const string &name_,
        int price_,
        const string &type_,
        int harvestWeight_,
        int weight_,
        const vector<Product> &products_);
    /**
     * cctor
     */
    Carnivore(const Carnivore &other);
    /**
     * assignment operator
     */
    Carnivore &operator=(const Carnivore &other);

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

class Herbivore : public Animal
{
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
     * @param products_ product yang akan dihasilkan jika dipanen
     */
    Herbivore(
        const string &kodeHuruf_,
        const string &name_,
        int price_,
        const string &type_,
        int harvestWeight_,
        int weight_,
        const vector<Product> &products_);
    /**
     * cctor
     */
    Herbivore(const Herbivore &other);
    /**
     * assignment operator
     */
    Herbivore &operator=(const Herbivore &other);

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

class Omnivore : public Animal
{
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
     * @param products_ product yang akan dihasilkan jika dipanen
     */
    Omnivore(
        const string &kodeHuruf_,
        const string &name_,
        int price_,
        const string &type_,
        int harvestWeight_,
        int weight_,
        const vector<Product> &products_);
    /**
     * cctor
     */
    Omnivore(const Omnivore &other);
    /**
     * assignment operator
     */
    Omnivore &operator=(const Omnivore &other);

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